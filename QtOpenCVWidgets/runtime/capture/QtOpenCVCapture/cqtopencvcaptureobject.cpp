/*
Copyright (c) 2012, Vladimir N. Litvinenko
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "cqtopencvcaptureobject.h"
#include <QTimerEvent>
#include <QTextCodec>

/**
  \def STRICT_CAMERA_NUMBER
  \brief Макрос приведения номера вебкамеры к корретному значению
  \param value - порядковый номер вебкамеры на компьютере
*/
#define STRICT_CAMERA_NUMBER(value) \
  ((value) > 0 ? (value) : CV_CAP_ANY)

/*----------------------------------------------------------------------------*/
class CQtOpenCVCaptureObjectPrivate
{
    Q_DECLARE_PUBLIC(CQtOpenCVCaptureObject)
  public:
    CQtOpenCVCaptureObjectPrivate ( CQtOpenCVCaptureObject* owner );
    virtual
    ~CQtOpenCVCaptureObjectPrivate ();

    void init ();
    void release ();

    void free_capture ();
    void alloc_capture ();

    void free_image ();
    void alloc_image ();

    int  frame_count () const;
    bool is_recap () const;
    void recap( bool );

    void set_camera_number ( int );
    void set_camera_file ( const QString& );
    void set_as_internal ( bool );

    void captureOn ( bool );

    void set_timer_interval ( int );
    void start ();
    void stop ();
    bool isActive () const;

    IplImage* getOpenCVImage () const;

    CQtOpenCVCaptureObject* q_ptr;

    CvCapture*  p_capture; ///< указатель на устройство видеозахвата
    IplImage*   p_image; ///< указатель на текущий фидеофрейм (не копия!) устройства видеозахвата
    QString     f_path; ///< URL сетевой видеокамеры или путь и файл видеоролика
    int         f_camera_num; ///< номер встроенной видеокамеры
    bool        f_internal; ///< признак использования встроенной видеокамеры
    int         f_errno; ///< номер кода ошибки
    bool        f_recap; ///< признак переинициализации устройства при количестве фреймов меньше двух

    int         f_timerUID; ///< UID таймера класса QObject
    int         f_timerInterval; ///< интервал тайм-аута срабатывания таймера
};

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn inline void CQtOpenCVCaptureObjectPrivate::init ()
  \brief Установка свойств класса в начальное значение.
*/
inline void
CQtOpenCVCaptureObjectPrivate::init ()
{
  f_errno = 0,

  p_capture = NULL,
  p_image = NULL,

  f_camera_num = CV_CAP_ANY,
  f_internal = true,
  f_recap = false;

  f_path.clear ();

  f_timerUID = 0,  f_timerInterval = DEFAULT_QWERY_FRAME_INTERVAL;
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn inline void CQtOpenCVCaptureObjectPrivate::release ()
  \brief
*/
inline void
CQtOpenCVCaptureObjectPrivate::release ()
{
  free_capture ();
  init ();
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn
  \brief
*/
inline void
CQtOpenCVCaptureObjectPrivate::free_capture ()
{
  f_errno = ERR_NONE; // код ошибки сброшен

  // останов механизма запроса изображения по тайм-ауту
  stop ();

  free_image ();

  if(p_capture) {
    // освобождение устройства захвата методом библиотеки OpenCV
    try {
      cvReleaseCapture(&p_capture);
    }catch(...) {
      // не сработало... Сообщим об этом в ЦК КПСС
      f_errno = ERR_RELEASE_CAPTURE;
      emit q_ptr->signal_Errno (f_errno, ERR_RELEASE_CAPTURE_MSG);
      //... возможна утечка памяти: мы не видим "внутренностей" cvReleaseCapture
    }
  }
  p_capture = NULL; // обязательно!
  emit q_ptr->signal_CaptureChanged ();
  emit q_ptr->signal_CaptureChanged (p_capture);

}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn CQtOpenCVCaptureObjectPrivate::CQtOpenCVCaptureObjectPrivate ( CQtOpenCVCaptureObject* owner )
  \brief Конструктор.\n
  \param owner - указатель на объект главного класса типа \a CQtOpenCVCaptureObject.
  Проверка указателя на объект главного класса и инициализация значений
*/
CQtOpenCVCaptureObjectPrivate::CQtOpenCVCaptureObjectPrivate ( CQtOpenCVCaptureObject* owner )
  : q_ptr(owner)
{
  Q_ASSERT(q_ptr);
  init ();
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn CQtOpenCVCaptureObjectPrivate::~CQtOpenCVCaptureObjectPrivate ()
  \brief Деструктор\n
  Всё очистить, память освободить.
*/
CQtOpenCVCaptureObjectPrivate::~CQtOpenCVCaptureObjectPrivate ()
{
  release ();
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn inline bool CQtOpenCVCaptureObjectPrivate::isActive ()
  \brief Проверка активности механизма получения указателя на изображение из
  устройства видеозахвата \a p_capture по тайм-ауту.\n
  \attention Если макрос TIMER_ON не объявлен при сборке проекта, то возвращаемое
  значение -- всегда "логическая ложь".
*/
inline bool
CQtOpenCVCaptureObjectPrivate::isActive () const
{
  return (f_timerUID > 0);
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] int CQtOpenCVCaptureObjectPrivate::frame_count ()
  \brief Метод представления количества фреймов в устройстве захвата.
  \return Возвращает количество фреймов в устройстве захвата, используя методы
  библиотеки OpenCV.
*/
inline int
CQtOpenCVCaptureObjectPrivate::frame_count () const
{
  return (
        p_capture != NULL ?
          (int)cvGetCaptureProperty (p_capture, CV_CAP_PROP_FRAME_COUNT) :
          0
  );
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] bool CQtOpenCVCaptureObjectPrivate::is_recap ()
  \brief Метод представления условия переинициализации устройства захвата по тайм-ауту.
  \return Возвращает значение true, если таймер предоставления изображения
  каждый раз переинициализирует устройство видеозахвата перед получением нового
  фрейма.
  \n
  Переинициализация может быть необходима при обращении к сетевой видеокамере,
  например, через веб-интерфейс встроенного в камеру сервера, когда последний
  может транслировать видео только покадрово.
*/
inline bool
CQtOpenCVCaptureObjectPrivate::is_recap () const
{
  return (f_recap);
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] void CQtOpenCVCaptureObjectPrivate::recap( bool value )
  \brief Метод установки условия переинициализации устройства захвата по тайм-ауту.
  \param value - признак переинициализации (значение true) устройства видеозахвата
  по тайм-ауту получения изображения.
*/
inline void
CQtOpenCVCaptureObjectPrivate::recap( bool value )
{
  if(f_recap != value) {
    bool b_active = isActive ();

    stop ();
      f_recap = value;
    if(b_active) start ();
  }
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn void CQtOpenCVCaptureObjectPrivate::alloc_capture ()
  \brief Метод распределения памяти для нового устройства \a p_capture видеозахвата.
*/
void
CQtOpenCVCaptureObjectPrivate::alloc_capture ()
{
//  free_capture (); // освободить ресурсы предыдущего устройсва

  if(/*(f_errno != ERR_NONE) || */(p_capture != NULL)) return;

  f_errno = ERR_NONE;
  bool b_active = isActive ();
  stop ();

  try {
    if(f_internal) {
      // встроенная видеокамера
      p_capture = cvCreateCameraCapture(f_camera_num);
    } else {
      // внешняя (сетевая) видеокамера или видеоролик
      if(!f_path.isNull ())
        if(!f_path.isEmpty ()) {
          // путь или сетевой адрес указаны
          p_capture = cvCreateFileCapture(f_path.toStdString ().c_str ());
        }
    }
  }catch(...) {
    // что-то пошло не так... Нужели "съели" всю память? Не-е-ет. Скорее, номер
    // или путь содержат неверные значения!
    f_errno = ERR_CREATE_CAPTURE;
    emit q_ptr->signal_Errno (f_errno, ERR_CREATE_CAPTURE_MSG);
    free_capture ();// на непредвиденную ошибку
  }

  if(p_capture) {
    // сообщение о состоянии указателя на устройство видеозахвата
    emit q_ptr->signal_CaptureChanged ();

    if(b_active) start ();
  } else {
  }

  emit q_ptr->signal_CaptureChanged (p_capture);
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] void CQtOpenCVCaptureObjectPrivate::free_image ()
  \brief Метод освобождения ресурсов свойства \a p_image класса указателя на изображение.
  \n
  \attention Функция cvReleaseImage не используется, т.к. значение свойства
  CQtOpenCVCaptureObjectPrivate::p_image формируется вызовом метода cvQueryFrame
  библиотеки OpenCV. Для работы с изображением используйте копию указателя на фрейм
  вызовом функции cvCloneImage библиотеки OpenCV.
  \n
  См. \a alloc_image
*/
inline void
CQtOpenCVCaptureObjectPrivate::free_image ()
{
  p_image = NULL;
  emit q_ptr->signal_ImageChanged (NULL);
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn void CQtOpenCVCaptureObjectPrivate::alloc_image ()
  \brief Метод извлечения очередного изображения из устройства видеозахвата.
*/
void
CQtOpenCVCaptureObjectPrivate::alloc_image ()
{
  f_errno = ERR_NONE;
  if(p_capture) {
    p_image = cvQueryFrame( p_capture );

    if(p_image == NULL) {
      f_errno = ERR_CREATE_IMAGE;
      emit q_ptr->signal_Errno (f_errno, ERR_CREATE_IMAGE_MSG);
    }

    emit q_ptr->signal_ImageChanged ( p_image );
  }
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] void CQtOpenCVCaptureObjectPrivate::captureOn ( bool value )
  \brief Метод начальной инициализации устройства видеозахвата и перезапуска
  запроса на текущее изображение по тайм-ауту.
  \n
  \param value -- признак включения (значение true) и отключения (значение false)
  устройства видеозахвата
  \n
  \warning При отключённой возможности запроса на текущее изображение по тайм-ауту,
  но при отсутствии указателя на устройство видеозахвата, просто, создаёт его.
  \n
  См. \a alloc_capture, \a free_capture, \a captureOn
*/
inline void
CQtOpenCVCaptureObjectPrivate::captureOn ( bool value )
{
  if(value) alloc_capture ();
  else      free_capture ();
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn void CQtOpenCVCaptureObjectPrivate::set_camera_number ( int value )
  \brief Метод установки номера вебкамеры компьютера.
  \param value - значение номера вебкамеры
*/
void
CQtOpenCVCaptureObjectPrivate::set_camera_number ( int value )
{
  if(f_camera_num != value )   {
    if(f_internal) {
      bool b_exist = p_capture != NULL;
      captureOn (false);
        f_camera_num = STRICT_CAMERA_NUMBER(value);
      if(b_exist) captureOn (true);
    }
  }
}


/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn void CQtOpenCVCaptureObjectPrivate::set_camera_file ( const QString& value )
  \brief Метод установки пути к сетевой камере или видеоролику.
  \param value - путь к сетевой камере или видеоролику.
*/
void
CQtOpenCVCaptureObjectPrivate::set_camera_file ( const QString& value )
{
  if(f_path != value) {
    if(!f_internal) {
      bool b_exist = p_capture != NULL;
      captureOn (false);
      f_path = value;
      if(b_exist) captureOn (true);
    }
  }
}
/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn void CQtOpenCVCaptureObjectPrivate::set_as_internal ( bool value )
  \brief Метод определения устройства видеозахвата как вебкамера или сетевое устройство/видеоролик
  \param value -  значение true направляет устройство захвата на работу со
                  встроенной видеокамерой с номером значения \a f_camera_num
                  свойства класса, а значение false -- на работу с сетевой
                  камерой или видеороликом, расположенным по адресу значения
                  \a f_path свойства класса.
*/
void
CQtOpenCVCaptureObjectPrivate::set_as_internal ( bool value )
{
  if(f_internal != value) {
    bool b_exist = p_capture != NULL;
    captureOn (false);
      f_internal = value;
    if(b_exist) captureOn (true);
  }
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] void CQtOpenCVCaptureObjectPrivate::set_timer_interval ( int value )
  \brief Метод установки интервала тайм-аута запроса текущего изображения от
         устройства видеозахвата.
  \param value -  значение тайм-аута в миллисекундах.
*/
inline void
CQtOpenCVCaptureObjectPrivate::set_timer_interval ( int value )
{
  if(value != f_timerInterval) {
    bool b_active = isActive ();
    stop ();
      f_timerInterval = value > -1 ? value : DEFAULT_QWERY_FRAME_INTERVAL;
      emit q_ptr->signal_TimeoutChanged ();
      emit q_ptr->signal_TimeoutChanged (f_timerInterval);
    if(b_active) start ();
  }
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] void CQtOpenCVCaptureObjectPrivate::start ()
  \brief Метод запуска извлечения копий фреймов (указателей на изображение) из
  устройства \a p_capture видеозахвата по тайм-ауту.
*/
inline void
CQtOpenCVCaptureObjectPrivate::start ()
{
  if(f_timerInterval > 0 && (!isActive ())) {
    f_timerUID = q_ptr->startTimer (f_timerInterval);
    emit q_ptr->signal_ActiveChanged (isActive ());
  }
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] void CQtOpenCVCaptureObjectPrivate::stop ()
  \brief Метод останова извлечения копий фреймов (указателей на изображение) из
  устройства \a p_capture видеозахвата по тайм-ауту.
*/
inline void
CQtOpenCVCaptureObjectPrivate::stop ()
{
  if(isActive ()) {
    q_ptr->killTimer (f_timerUID);
    emit q_ptr->signal_ActiveChanged ((bool)(f_timerUID = 0));
  }
}

/*----------------------------------------------------------------------------*/
/**
  \internal
  \fn [inline] IplImage* CQtOpenCVCaptureObjectPrivate::getOpenCVImage ()
  \brief Метод доступа к изображению копии текущего фрейма устройства видеозахвата
  \return Указатель на переменную типа \a IplImage библиотеки OpenCV
*/
inline IplImage*
CQtOpenCVCaptureObjectPrivate::getOpenCVImage () const
{
  return p_image ? cvCloneImage (p_image) : NULL;
}

/*----------------------------------------------------------------------------*/
/* CQtOpenCVCaptureObject */
/*----------------------------------------------------------------------------*/
/**
  \fn CQtOpenCVCaptureObject::CQtOpenCVCaptureObject( QObject *parent )
  \brief Конструктор класса.
  \param parent - родительский объект типа QObject или его наследник.
*/
CQtOpenCVCaptureObject::CQtOpenCVCaptureObject( QObject *parent ) :
  QObject(parent)
, d_ptr(new CQtOpenCVCaptureObjectPrivate(this))
{
}

/*----------------------------------------------------------------------------*/
/**
  \fn CQtOpenCVCaptureObject::~CQtOpenCVCaptureObject()
  \brief Деструктор класса.
*/
CQtOpenCVCaptureObject::~CQtOpenCVCaptureObject()
{
  d_func ()->stop ();
  d_func ()->captureOn (false);
}

/*----------------------------------------------------------------------------*/
/**
  \fn bool CQtOpenCVCaptureObject::isActive ()
  \brief Проверка активности механизма получения указателя на изображение из
  устройства видеозахвата по тайм-ауту.
  \n
  \attention Если макрос TIMER_ON не объявлен при сборке проекта, то возвращаемое
  значение -- всегда "логическая ложь".
*/
bool
CQtOpenCVCaptureObject::isActive () const
{
  return (d_func ()->isActive ());
}

/*----------------------------------------------------------------------------*/
/**
  \fn bool CQtOpenCVCaptureObject::isRecap ()
  \brief Метод представления условия переинициализации устройства захвата по тайм-ауту.
  \return Возвращает значение true, если таймер предоставления изображения
  каждый раз переинициализирует устройство видеозахвата перед получением нового
  фрейма.
  \n
  Переинициализация может быть необходима при обращении к сетевой видеокамере,
  например, через веб-интерфейс встроенного в камеру сервера, когда последний
  может транслировать видео только покадрово.
*/
bool
CQtOpenCVCaptureObject::isRecap () const
{
  return (d_func ()->is_recap ());
}

/*----------------------------------------------------------------------------*/
/**
  \fn CvCapture* CQtOpenCVCaptureObject::getCapture () [const]
  \brief Метод получения указателя на свойство класса устройства видеозахвата.
  \return Указатель на объект устройства видеозахвата типа CvCapture библиотеки OpenCV.
*/
CvCapture*
CQtOpenCVCaptureObject::getCapture () const
{
  return (d_func ()->p_capture);
}

/*----------------------------------------------------------------------------*/
/**
  \fn bool CQtOpenCVCaptureObject::isInternal () [const]
  \brief Метод показывает, используется ли внутренняя вебкамера или идёт
  трансляция из сетевого устройства или видеоролика.
  \return Возвращает значение true, если устройство видеозахвата настроено на
  одну из внутренних видеокамер компьютера. Если трансляция ведётся из сетевого
  устройства или видеоролика, то метод возвращаент значение false.
  \n
  См. \a isExternal, \a getCameraNumber
*/
bool
CQtOpenCVCaptureObject::isInternal () const
{
  return (d_func ()->f_internal);
}

/*----------------------------------------------------------------------------*/
/**
  \fn
  \brief Метод показывает, используется ли трансляция из сетевого устройства
  или видеоролика или работает внутренняя вебкамера.
  \return Если трансляция ведётся из сетевого устройства или видеоролика, то
  метод возвращаент значение true. Возвращает значение false, если устройство
  видеозахвата настроено на одну из внутренних видеокамер компьютера.
  \n
  Метод введён для удобства пользователя и является противоположностью
  метода \a isInternal.
  \attention Размещено в файле реализации класса, а не inline, т.к. возможно использование
  как PROPERTY( ... READ isExternal ...)
  См. \a isInternal, \a getPath
*/
bool
CQtOpenCVCaptureObject::isExternal () const
{
  return (!isInternal ());
}

/*----------------------------------------------------------------------------*/
/**
  \fn QString CQtOpenCVCaptureObject::getPath () [const]
  \brief Метод длаёт доступ к пути сетевого видеоустройства или файлу видеоролика.
  \return Возвращает значения типа QString пути сетевого видеоустройства или
  файла видеоролика.
  \n
  См. \a getCameraNumber, \a isExternal
*/
QString
CQtOpenCVCaptureObject::getPath () const
{
  return (d_func ()->f_path);
}

/*----------------------------------------------------------------------------*/
/**
  \fn int CQtOpenCVCaptureObject::getNumber () [const]
  \brief Метод показывает номер встроенной видеокамеры, на которую сориентированно
  устройство видеозахвата.
  \return Возвращает значение номера встроенной видеокамеры.
  \n
  См. \a getPath, \a isInternal
*/
int
CQtOpenCVCaptureObject::getNumber () const
{
  return (d_func ()->f_camera_num);
}

/*----------------------------------------------------------------------------*/
/**
  \fn int CQtOpenCVCaptureObject::getTimeoutInterval () [const]
  \brief Метод получения значения интервала тайм-аута опроса текущего изображения
  из устройства видеозахвата.
  \return Возвращает значение интервала тайм-аута опроса текущего изображения из
  устройства видеозахвата.
*/
int
CQtOpenCVCaptureObject::getTimeoutInterval () const
{
  return (d_func ()->f_timerInterval);
}

/*----------------------------------------------------------------------------*/
/**
  \fn IplImage*
  \brief Метод доступа к изображению копии текущего фрейма устройства видеозахвата
  \return Указатель на переменную типа \a IplImage библиотеки OpenCV
*/
IplImage*
CQtOpenCVCaptureObject::getImage () const
{
  return (d_func ()->getOpenCVImage ());
}

/*----------------------------------------------------------------------------*/
/**
  \fn int CQtOpenCVCaptureObject::getFrameCount ()
  \brief Метод представления количества фреймов в устройстве захвата.
  \return Возвращает количество фреймов в устройстве захвата, используя методы
  библиотеки OpenCV.
*/
int
CQtOpenCVCaptureObject::getFrameCount () const
{
  return (d_func ()->frame_count ());
}

/*----------------------------------------------------------------------------*/
/**
  \fn [SLOT] void CQtOpenCVCaptureObject::slot_SetAsInternal ( bool value )
  \brief Слот определения устройства видеозахвата как вебкамера или сетевое
  устройство/видеоролик.
  \param value -  значение true направляет устройство захвата на работу со
                  встроенной видеокамерой с номером значения \a f_camera_num
                  свойства класса, а значение false -- на работу с сетевой
                  камерой или видеороликом, расположенным по адресу значения
                  \a f_path свойства класса.
*/
void
CQtOpenCVCaptureObject::slot_SetAsInternal ( bool value )
{
  d_func ()->set_as_internal (value);
}

/*----------------------------------------------------------------------------*/
/**
  \fn [SLOT] void CQtOpenCVCaptureObject::slot_SetNumber ( int value )
  \brief Слот установки номера вебкамеры компьютера.
  \param value - значение номера вебкамеры
*/
void
CQtOpenCVCaptureObject::slot_SetNumber ( int value )
{
  d_func ()->set_camera_number (value);
}

/*----------------------------------------------------------------------------*/
/**
  \fn [SLOT] void CQtOpenCVCaptureObject::slot_SetPath ( const QString& value )
  \brief Слот установки пути к сетевой камере или видеоролику.
  \param value - путь к сетевой камере или видеоролику.
*/
void
CQtOpenCVCaptureObject::slot_SetPath ( const QString& value )
{
  d_func ()->set_camera_file (QString(value.toUtf8 ()));
}

/*----------------------------------------------------------------------------*/
/**
  \fn [SLOT] void CQtOpenCVCaptureObject::slot_SetTimeout ( int value )
  \brief Слот установки тайм-аута опроса устройства видеозахвата на получение текущего изображения.
  \param value -- значение тайм-аута.
*/
void
CQtOpenCVCaptureObject::slot_SetTimeout ( int value )
{
  d_func ()->set_timer_interval (value);
}

/*----------------------------------------------------------------------------*/
/**
  \fn [SLOT] void CQtOpenCVCaptureObject::slot_captureOn ( bool value )
  \brief Слот начальной инициализации устройства видеозахвата и перезапуска
  запроса на текущее изображение по тайм-ауту.
  \param value -- признак включения (значение true) и отключения (значение false) устройства видеозахвата
  \n
  \warning При отключённой возможности запроса на текущее изображение по тайм-ауту,
  но при отсутствии указателя на устройство видеозахвата, просто, создаёт его.
  \n
*/
void
CQtOpenCVCaptureObject::slot_captureOn ( bool value )
{
  d_func ()->captureOn ( value );
}

/*----------------------------------------------------------------------------*/
/**
  \fn [virtual] void CQtOpenCVCaptureObject::timerEvent(QTimerEvent *event)
  \brief Переопределённый для QObject виртуальный обработчик события таймера.
*/
void
CQtOpenCVCaptureObject::timerEvent(QTimerEvent *event)
{
  if(// если...
     (event->timerId () == d_func ()->f_timerUID)// ... нужное событие ...
     && // ... и ...
     (isActive ()) // ... таймер включен ...
     && // ... и ...
     (d_func ()->p_capture != NULL) // ... устройство определено ...
  )
  {
    d_func ()->f_errno = ERR_NONE;
    d_func ()->stop ();
    try {
      if(d_func ()->is_recap () /*&& (d_func ()->frame_count () < 1)*/) {
        d_func ()->free_capture ();
        d_func ()->alloc_capture ();
      }

      if(d_func ()->p_capture) {
        d_func ()->alloc_image ();
        if(d_func ()->f_errno != ERR_CREATE_CAPTURE)
          d_func ()->start ();
      }

    } catch(...) {
      d_func ()->f_errno = ERR_RESTART;
      emit signal_Errno (d_func ()->f_errno, ERR_RESTART_MSG);
    }
  }
}

/*----------------------------------------------------------------------------*/
/**
  \fn [SLOT] void CQtOpenCVCaptureObject::slot_Activate (bool value)
  \brief Слот управления таймером извлечения фреймов из устройства видеозахвата.
  \param value -- признак запуска (true) или останова (false) таймера.
  Слот работает при наличии макроса TIMER_ON.
*/
void
CQtOpenCVCaptureObject::slot_Activate (bool value)
{
  if(value) d_func ()->start ();
  else      d_func ()->stop ();
}

/*----------------------------------------------------------------------------*/
/**
  \fn void CQtOpenCVCaptureObject::slot_SetRecap( bool value )
  \brief Метод установки условия переинициализации устройства захвата по тайм-ауту.
  \param value - признак переинициализации (значение true) устройства видеозахвата
  по тайм-ауту получения изображения.
*/
void
CQtOpenCVCaptureObject::slot_SetRecap ( bool value )
{
  d_func ()->recap (value);
}

/*----------------------------------------------------------------------------*/
