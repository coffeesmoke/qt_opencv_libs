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


#ifndef CQTOPENCVCAPTUREOBJECT_H
#define CQTOPENCVCAPTUREOBJECT_H

#include "../../../include/qtopencv_global.h"
#include <opencv2/opencv.hpp>

#include <QObject>
#include <QScopedPointer>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

/*----------------------------------------------------------------------------*/
/**
  \internal
  \class CQtOpenCVCaptureObjectPrivate
  \brief Класс скрытого для стороннего разработчика объявлений свойст и реализаций
  механизмов работы с устройством видеозахвата типа CvCapture библиотеки OpenCV.
*/
class CQtOpenCVCaptureObjectPrivate;

/*----------------------------------------------------------------------------*/
/**
  \class CQtOpenCVCaptureObject
  \brief Класс Работы с устройством видеозахвата типа CvCapture библиотеки OpenCV.
*/
class
    #if defined(QTOPENCV_LIB_EXPORT)
    QTOPENCV_DECLARE_EXPORT
    #else
    Q_DECL_EXPORT
    #endif
CQtOpenCVCaptureObject : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("brief",    "OpenCV Capture class.")
    Q_CLASSINFO("author",   "Vladimir N. Litvinenko")
    Q_CLASSINFO("URL",      "http://www.codepaint.ru")
    Q_CLASSINFO("email",    "litvinenko.vladimir@gmail.com")
    Q_CLASSINFO("created",  "21-JUN-2012")
    Q_CLASSINFO("edited",   "06-JUL-2012")

  public:
    explicit
    CQtOpenCVCaptureObject ( QObject *parent = 0 );
    virtual
    ~CQtOpenCVCaptureObject ();

    CvCapture*  getCapture () const;
    QString     getPath () const;
    int         getNumber () const;
    int         getTimeoutInterval () const;
    IplImage*   getImage () const;
    int         getFrameCount () const;

    bool        isInternal () const;
    bool        isExternal () const;
    bool        isActive () const;
    bool        isRecap () const;

  signals:

    /**
      \fn [SIGNAL] void CQtOpenCVCaptureObject::signal_Errno ( int errno, const QString& errmsg );
      \brief Сигнал оповещения о возникновении ошибочной ситуации.
      \param errno - номер ошибки
      \param errmsg - строка сообщения
    */
    void  signal_Errno ( int, const QString& );

    /**
      \fn [SIGNAL] void CQtOpenCVCaptureObject::signal_CaptureChanged ()
      \brief Сигнал оповещения об изменении устройства видеозахвата
    */
    void  signal_CaptureChanged ();

    /**
      \fn [SIGNAL] void CQtOpenCVCaptureObject::signal_CaptureChanged ( const CvCapture* value )
      \brief Сигнал оповещения об изменении устройства видеозахвата
      \param value - указател на новое устройство видеозахвата типа CvCapture
                     библиотеки OpenCV
    */
    void  signal_CaptureChanged ( const CvCapture* );

    /**
      \fn [SIGNAL] void CQtOpenCVCaptureObject::signal_ImageChanged ( const IplImage* value )
      \brief Сигнал оповещения об изменении указателя на изображение типа IplImage
             библиотеки OpenCV.
      \param value - новый указатель на изображение типа IplImage библиотеки OpenCV.
    */
    void  signal_ImageChanged ( const IplImage* );

    /**
      \fn [SIGNAL] void CQtOpenCVCaptureObject::signal_TimeoutChanged ()
      \brief Сигнал оповещения об изменении таймаута запроса изображения
    */
    void  signal_TimeoutChanged ();

    /**
      \fn [SIGNAL] void CQtOpenCVCaptureObject::signal_TimeoutChanged ( int value )
      \brief Сигнал оповещения об изменении таймаута запроса изображения
      \param value - новое значение таймаута запроса изображения
    */
    void  signal_TimeoutChanged ( int );

    /**
      \fn [SIGNAL] void CQtOpenCVCaptureObject::signal_ActiveChanged ( bool value )
      \brief Сигнал оповещения смены статуса активности запроса изображения от
      устройства видеозахвата по тайм-ауту.
      \param value - новое значение активности процесса запроса. Значение true
                     говорит о выполнении, а false - об останове процесса запроса
                     по тайм-ауту.
    */
    void  signal_ActiveChanged ( bool );

  public slots:
    void  slot_SetNumber ( int );
    void  slot_SetPath ( const QString& );
    void  slot_SetAsInternal ( bool );
    void  slot_SetTimeout ( int );
    void  slot_captureOn ( bool );
    void  slot_Activate (bool);
    void  slot_SetRecap (bool);

  protected:
    virtual
    void timerEvent(QTimerEvent *event);

  private:
    Q_DISABLE_COPY(CQtOpenCVCaptureObject)
    Q_DECLARE_PRIVATE(CQtOpenCVCaptureObject)

    QScopedPointer<CQtOpenCVCaptureObjectPrivate> d_ptr;
};
/*----------------------------------------------------------------------------*/

QT_END_NAMESPACE

QT_END_HEADER

#endif // CQTOPENCVCAPTUREOBJECT_H
