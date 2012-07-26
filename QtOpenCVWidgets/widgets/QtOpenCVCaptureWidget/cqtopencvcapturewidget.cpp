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


#include "cqtopencvcapturewidget.h"
#include "../../../include/qtopencv_global.h"

#include <QtGui/QFrame>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QPushButton>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QCheckBox>

/*----------------------------------------------------------------------------*/
class CQtOpenCVCaptureWidgetPrivate
{
    Q_DECLARE_PUBLIC(CQtOpenCVCaptureWidget)

  public:

    CQtOpenCVCaptureWidgetPrivate (CQtOpenCVCaptureWidget* owner);
    virtual
    ~CQtOpenCVCaptureWidgetPrivate ();

    void setupUi ( QWidget* parent = 0 );
    void retranslateUi();
    void deleteUi ();

    void setupConnections ();

    CQtOpenCVCaptureWidget* q_ptr;
    CQtOpenCVCaptureObject* q_obj;
    QString                 f_path_tmp;

    QFrame*         p_Frame;
    QGridLayout*    p_gridLayout_Frame;
    QGroupBox*      p_groupBox_Capture;
    QGridLayout*    p_gridLayout_GBox;
    QHBoxLayout*    p_horLayout_Radio;
    QRadioButton*   p_radioButton_URL;
    QRadioButton*   p_radioButton_Number;
    QHBoxLayout*    p_horLayout_PathNum;
    QLabel*         p_label_PathNum;
    QSpinBox*       p_spinBox_Number;
    QLineEdit*      p_lineEdit;
    QHBoxLayout*    p_horLayout_TOut;
    QLabel*         p_label_TOut;
    QSpinBox*       p_spinBox_TOut;
    QLabel*         p_label_ms;
    QSpacerItem*    p_horizontalSpacer;
    QHBoxLayout*    p_horLayout_Buttons;
    QCheckBox*      p_checkBox_Recap;
    QPushButton*    p_pushButton_Test;

    QString f_NumberTitle, f_PathTitle;

    QString f_title;
};

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidgetPrivate::setupUi ( QWidget* parent )
{
  p_Frame = new QFrame(parent);
  Q_ASSERT(p_Frame);
  p_Frame->setObjectName(QString::fromUtf8("p_Frame"));
  p_Frame->resize(550, 195);
  p_Frame->setMinimumSize(QSize(550, 195));
//  p_Frame->setMaximumSize(QSize(550, 195));
  p_Frame->setFrameShape(QFrame::StyledPanel);
  p_Frame->setFrameShadow(QFrame::Raised);

  p_gridLayout_Frame = new QGridLayout(p_Frame);
  Q_ASSERT(p_gridLayout_Frame);
  p_gridLayout_Frame->setObjectName(QString::fromUtf8("p_gridLayout_Frame"));

  p_groupBox_Capture = new QGroupBox(p_Frame);
  Q_ASSERT(p_groupBox_Capture);
  p_groupBox_Capture->setObjectName(QString::fromUtf8("p_groupBox_Capture"));

  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(p_groupBox_Capture->sizePolicy().hasHeightForWidth());
  p_groupBox_Capture->setSizePolicy(sizePolicy);
//  p_groupBox_Capture->setMinimumSize(QSize(540, 190));
//  p_groupBox_Capture->setMaximumSize(QSize(540, 185));
  p_groupBox_Capture->setFlat(true);

  p_gridLayout_GBox = new QGridLayout(p_groupBox_Capture);
  Q_ASSERT(p_gridLayout_GBox);
  p_gridLayout_GBox->setSpacing(1);
  p_gridLayout_GBox->setContentsMargins(3, 3, 3, 3);
  p_gridLayout_GBox->setObjectName(QString::fromUtf8("p_gridLayout_GBox"));

  p_horLayout_Radio = new QHBoxLayout();
  Q_ASSERT(p_horLayout_Radio);
  p_horLayout_Radio->setSpacing(1);
  p_horLayout_Radio->setObjectName(QString::fromUtf8("p_horLayout_Radio"));

  p_radioButton_URL = new QRadioButton(p_groupBox_Capture);
  Q_ASSERT(p_radioButton_URL);
  p_radioButton_URL->setObjectName(QString::fromUtf8("p_radioButton_URL"));
  p_horLayout_Radio->addWidget(p_radioButton_URL);

  p_radioButton_Number = new QRadioButton(p_groupBox_Capture);
  Q_ASSERT(p_radioButton_Number);
  p_radioButton_Number->setObjectName(QString::fromUtf8("p_radioButton_Number"));
  p_radioButton_Number->setChecked(true);
  p_horLayout_Radio->addWidget(p_radioButton_Number);
  p_gridLayout_GBox->addLayout(p_horLayout_Radio, 0, 0, 1, 1);

  p_horLayout_PathNum = new QHBoxLayout();
  Q_ASSERT(p_horLayout_PathNum);
  p_horLayout_PathNum->setSpacing(3);
  p_horLayout_PathNum->setObjectName(QString::fromUtf8("p_horLayout_PathNum"));

  p_label_PathNum = new QLabel(p_groupBox_Capture);
  Q_ASSERT(p_label_PathNum);
  p_label_PathNum->setObjectName(QString::fromUtf8("p_label_PathNum"));
  QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(p_label_PathNum->sizePolicy().hasHeightForWidth());
  p_label_PathNum->setSizePolicy(sizePolicy1);
  p_label_PathNum->setMinimumSize(QSize(150, 0));
  p_label_PathNum->setLayoutDirection(Qt::LeftToRight);
  p_label_PathNum->setFrameShape(QFrame::NoFrame);
  p_label_PathNum->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
  p_horLayout_PathNum->addWidget(p_label_PathNum);

  p_spinBox_Number = new QSpinBox(p_groupBox_Capture);
  Q_ASSERT(p_spinBox_Number);
  p_spinBox_Number->setObjectName(QString::fromUtf8("p_spinBox_Number"));
  sizePolicy.setHeightForWidth(p_spinBox_Number->sizePolicy().hasHeightForWidth());
  p_spinBox_Number->setSizePolicy(sizePolicy);
  p_spinBox_Number->setMinimum(0);
  p_spinBox_Number->setMaximum(999999);
  p_horLayout_PathNum->addWidget(p_spinBox_Number);

  p_lineEdit = new QLineEdit(p_groupBox_Capture);
  Q_ASSERT(p_lineEdit);
  p_lineEdit->setObjectName(QString::fromUtf8("p_lineEdit"));
  p_lineEdit->setEnabled(true);
  p_horLayout_PathNum->addWidget(p_lineEdit);
  p_gridLayout_GBox->addLayout(p_horLayout_PathNum, 1, 0, 1, 1);

  p_horLayout_TOut = new QHBoxLayout();
  Q_ASSERT(p_horLayout_TOut);
  p_horLayout_TOut->setSpacing(3);
  p_horLayout_TOut->setObjectName(QString::fromUtf8("p_horLayout_TOut"));

  p_label_TOut = new QLabel(p_groupBox_Capture);
  Q_ASSERT(p_label_TOut);
  p_label_TOut->setObjectName(QString::fromUtf8("p_label_TOut"));
  sizePolicy1.setHeightForWidth(p_label_TOut->sizePolicy().hasHeightForWidth());
  p_label_TOut->setSizePolicy(sizePolicy1);
  p_label_TOut->setMinimumSize(QSize(150, 0));
  p_horLayout_TOut->addWidget(p_label_TOut);

  p_spinBox_TOut = new QSpinBox(p_groupBox_Capture);
  Q_ASSERT(p_spinBox_TOut);
  p_spinBox_TOut->setObjectName(QString::fromUtf8("p_spinBox_TOut"));
  sizePolicy.setHeightForWidth(p_spinBox_TOut->sizePolicy().hasHeightForWidth());
  p_spinBox_TOut->setSizePolicy(sizePolicy);
  p_spinBox_TOut->setMinimum(0);
  p_spinBox_TOut->setMaximum(999999);
  p_horLayout_TOut->addWidget(p_spinBox_TOut);

  p_label_ms = new QLabel(p_groupBox_Capture);
  Q_ASSERT(p_label_ms);
  p_label_ms->setObjectName(QString::fromUtf8("p_label_ms"));
  sizePolicy1.setHeightForWidth(p_label_ms->sizePolicy().hasHeightForWidth());
  p_label_ms->setSizePolicy(sizePolicy1);
  p_horLayout_TOut->addWidget(p_label_ms);

  p_horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);
  Q_ASSERT(p_horizontalSpacer);
  p_horLayout_TOut->addItem(p_horizontalSpacer);
  p_gridLayout_GBox->addLayout(p_horLayout_TOut, 2, 0, 1, 1);

  p_horLayout_Buttons = new QHBoxLayout();
  Q_ASSERT(p_horLayout_Buttons);
  p_horLayout_Buttons->setSpacing(3);
  p_horLayout_Buttons->setObjectName(QString::fromUtf8("p_horLayout_Buttons"));

  p_checkBox_Recap = new QCheckBox(p_groupBox_Capture);
  Q_ASSERT(p_checkBox_Recap);
  p_checkBox_Recap->setObjectName(QString::fromUtf8("p_checkBox_Recap"));
  sizePolicy.setHeightForWidth(p_checkBox_Recap->sizePolicy().hasHeightForWidth());
  p_checkBox_Recap->setSizePolicy(sizePolicy);
  p_horLayout_Buttons->addWidget(p_checkBox_Recap);

  p_pushButton_Test = new QPushButton(p_groupBox_Capture);
  Q_ASSERT(p_pushButton_Test);
  p_pushButton_Test->setObjectName(QString::fromUtf8("p_pushButton_Test"));
  p_pushButton_Test->setCheckable(true);
  p_pushButton_Test->setChecked(false);

  p_horLayout_Buttons->addWidget(p_pushButton_Test);
  p_gridLayout_GBox->addLayout(p_horLayout_Buttons, 3, 0, 1, 1);
  p_gridLayout_Frame->addWidget(p_groupBox_Capture, 0, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
  p_label_PathNum->setBuddy(p_lineEdit);
#endif // QT_NO_SHORTCUT

  retranslateUi();

  QMetaObject::connectSlotsByName(p_Frame);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidgetPrivate::retranslateUi()
{
    p_Frame->setWindowTitle(TITLE_FRAME);
    p_groupBox_Capture->setTitle(TITLE_GROUP_BOX);
    p_radioButton_URL->setText(TITLE_RADIO_URL);
    p_radioButton_Number->setText(TITLE_RADIO_NUM);
    p_label_PathNum->setText(f_NumberTitle);
    p_label_TOut->setText(TITLE_TIMEOUT);
    p_label_ms->setText(TITLE_TIMEOUT_EXT);
    p_checkBox_Recap->setText(TITLE_RECAPTURE);
    p_pushButton_Test->setText(TITLE_BUTTON_TEST);
} // retranslateUi

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidgetPrivate::setupConnections ()
{
  // перенаправление сигналов runtime-объекта на выход виджета
  q_obj->connect (q_obj, SIGNAL(signal_Errno(int,QString)), q_ptr, SIGNAL(signal_Errno(int,QString)));
  q_obj->connect (q_obj, SIGNAL(signal_CaptureChanged()), q_ptr, SIGNAL(signal_CaptureChanged()));
  q_obj->connect (q_obj, SIGNAL(signal_CaptureChanged(const CvCapture*)), q_ptr, SIGNAL(signal_CaptureChanged(const CvCapture*)));
  q_obj->connect (q_obj, SIGNAL(signal_ImageChanged(const IplImage*)), q_ptr, SIGNAL(signal_ImageChanged(const IplImage*)));
  q_obj->connect (q_obj, SIGNAL(signal_TimeoutChanged()), q_ptr, SIGNAL(signal_TimeoutChanged()));
  q_obj->connect (q_obj, SIGNAL(signal_TimeoutChanged(int)), q_ptr, SIGNAL(signal_TimeoutChanged(int)));
  q_obj->connect (q_obj, SIGNAL(signal_ActiveChanged(bool)), q_ptr, SIGNAL(signal_ActiveChanged(bool)));

  // установка обработки переключения устройств получения видеоинформации
  q_ptr->connect (p_radioButton_Number,SIGNAL(toggled(bool)), q_ptr, SLOT(slot_SetAsInternal(bool)));
  q_ptr->connect (p_radioButton_URL, SIGNAL(toggled(bool)), q_ptr, SLOT(slot_SetAsExternal(bool)));

  // обработка редактирования и ввода строки пути устроцства видеозахвата
  q_ptr->connect (p_lineEdit, SIGNAL(textChanged(QString)), q_ptr, SLOT(slot_SetPath(QString)));
  q_ptr->connect (p_lineEdit, SIGNAL(returnPressed()), q_ptr, SLOT(slot_PathComplete()));

  // установка обработки изменения номера встроенной вебкамеры
  q_ptr->connect (p_spinBox_Number, SIGNAL(valueChanged(int)), q_ptr, SLOT(slot_SetNumber(int)));

  // установка обработки изменения тайм-аута опроса устройства
  q_ptr->connect (p_spinBox_TOut, SIGNAL(valueChanged(int)), q_ptr, SLOT(slot_SetTimeout(int)));

  // установка обработки изменения включения реинициализации устройства видеозахвата в каждом тайм-ауте
  q_ptr->connect (p_checkBox_Recap, SIGNAL(toggled(bool)), q_ptr, SLOT(slot_SetRecap(bool)));

  // установка обработки сигнала к тестированию
  q_ptr->connect (p_pushButton_Test, SIGNAL(toggled(bool)),  q_ptr, SLOT(slot_Test(bool)));

//  q_ptr->connect (q_ptr, SIGNAL(signal_ImageChanged(const IplImage*)), q_ptr, SLOT(slot_ShowImage(const IplImage*)));
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidgetPrivate::deleteUi ()
{
  if(!(p_Frame->parent ())) delete p_Frame;
}

/*----------------------------------------------------------------------------*/
CQtOpenCVCaptureWidgetPrivate::CQtOpenCVCaptureWidgetPrivate (CQtOpenCVCaptureWidget* owner)
  : q_ptr(owner)
{
  Q_ASSERT(q_ptr);
  q_obj = new CQtOpenCVCaptureObject(q_ptr);
  Q_ASSERT(q_obj);

  f_path_tmp.clear ();
  f_title = "IplImage test.";

  f_NumberTitle = TITLE_CAMERA_NUMBER;
  f_PathTitle   = TITLE_CAMERA_PATH;


  setupUi (q_ptr);
  retranslateUi ();

  setupConnections ();

  p_radioButton_Number->setChecked (true);
}

/*----------------------------------------------------------------------------*/
CQtOpenCVCaptureWidgetPrivate::~CQtOpenCVCaptureWidgetPrivate ()
{
  if(!(q_obj->parent ()))
    delete q_obj;

  deleteUi ();
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
CQtOpenCVCaptureWidget::CQtOpenCVCaptureWidget(QWidget *parent)
  : QWidget(parent)
  , d_ptr(new CQtOpenCVCaptureWidgetPrivate(this))
{
  slot_SetAsInternal (true);
}

CQtOpenCVCaptureWidget::~CQtOpenCVCaptureWidget()
{
  close ();
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::close ()
{
  slot_Test(false);
  QWidget::close ();
}

/*----------------------------------------------------------------------------*/
CQtOpenCVCaptureObject*
CQtOpenCVCaptureWidget::asRuntime () const
{
  return (d_func ()->q_obj);
}

/*----------------------------------------------------------------------------*/
CvCapture*
CQtOpenCVCaptureWidget::getCapture () const
{
  return (asRuntime ()->getCapture ());
}
/*----------------------------------------------------------------------------*/
bool
CQtOpenCVCaptureWidget::isInternal () const
{
  return (asRuntime ()->isInternal ());
}
/*----------------------------------------------------------------------------*/
bool
CQtOpenCVCaptureWidget::isExternal () const
{
  return (asRuntime ()->isExternal ());
}
/*----------------------------------------------------------------------------*/
bool
CQtOpenCVCaptureWidget::isActive () const
{
  return (asRuntime ()->isActive ());
}
/*----------------------------------------------------------------------------*/
bool
CQtOpenCVCaptureWidget::isRecap () const
{
  return (asRuntime ()->isRecap ());
}
/*----------------------------------------------------------------------------*/
QString
CQtOpenCVCaptureWidget::getPath () const
{
  return (asRuntime ()->getPath ());
}
/*----------------------------------------------------------------------------*/
int
CQtOpenCVCaptureWidget::getNumber () const
{
  return (asRuntime ()->getNumber ());
}
/*----------------------------------------------------------------------------*/
int
CQtOpenCVCaptureWidget::getTimeoutInterval () const
{
  return (asRuntime ()->getTimeoutInterval ());
}
/*----------------------------------------------------------------------------*/
IplImage*
CQtOpenCVCaptureWidget::getImage () const
{
  return (asRuntime ()->getImage ());
}
/*----------------------------------------------------------------------------*/
int
CQtOpenCVCaptureWidget::getFrameCount () const
{
  return (asRuntime ()->getFrameCount ());
}
/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_SetNumber ( int value )
{
  asRuntime ()->slot_SetNumber (value);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_SetTimeout ( int value )
{
  asRuntime ()->slot_SetTimeout (value);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_SetAsInternal ( bool value )
{
  d_func ()->p_lineEdit->setVisible (!value);
  d_func ()->p_spinBox_Number->setVisible (value);
  d_func ()->p_label_PathNum->setText (value ? d_func ()->f_NumberTitle : d_func ()->f_PathTitle);
  if(d_func ()->p_pushButton_Test->isChecked ())
    d_func ()->p_pushButton_Test->setChecked (false);
  asRuntime ()->slot_SetAsInternal (value);

}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_SetAsExternal ( bool value )
{
  d_func ()->p_lineEdit->setVisible (value);
  d_func ()->p_spinBox_Number->setVisible (!value);
  d_func ()->p_label_PathNum->setText (value ? d_func ()->f_PathTitle : d_func ()->f_NumberTitle);
  if(d_func ()->p_pushButton_Test->isChecked ())
    d_func ()->p_pushButton_Test->setChecked (false);
  asRuntime ()->slot_SetAsInternal (!value);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_captureOn ( bool value )
{
  asRuntime ()->slot_captureOn (value);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_Activate (bool value)
{
  asRuntime ()->slot_Activate(value);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_SetRecap (bool value)
{
  asRuntime ()->slot_SetRecap(value);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_PathComplete ()
{
  asRuntime ()->slot_SetPath (d_func ()->f_path_tmp);
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_SetPath ( const QString& value )
{
  d_func ()->f_path_tmp = value;
}

/*----------------------------------------------------------------------------*/
void
CQtOpenCVCaptureWidget::slot_Test ( bool value )
{
  slot_captureOn (value);
  slot_Activate (value);
/*
  if(value)   cvNamedWindow (d_func ()->f_title.toStdString ().c_str (),CV_WINDOW_NORMAL);
  else        cvDestroyAllWindows ();
*/
}

/*----------------------------------------------------------------------------*/
//собственные методы доступа и слоты
int
CQtOpenCVCaptureWidget::getNumberMax () const
{ return d_func ()->p_spinBox_Number->maximum (); }

int
CQtOpenCVCaptureWidget::getTimeoutMax () const
{ return d_func ()->p_spinBox_TOut->maximum (); }

int
CQtOpenCVCaptureWidget::getTimeoutStep () const
{ return d_func ()->p_spinBox_TOut->singleStep (); }

QString
CQtOpenCVCaptureWidget::getFrameTitle () const
{ return d_func ()->p_Frame->windowTitle (); }

QString
CQtOpenCVCaptureWidget::getGroupBoxTitle () const
{ return d_func ()->p_groupBox_Capture->title (); }

QString
CQtOpenCVCaptureWidget::getRadioNumberTitle () const
{ return d_func ()->p_radioButton_Number->text (); }

QString
CQtOpenCVCaptureWidget::getRadioPathTitle () const
{ return d_func ()->p_radioButton_URL->text (); }

QString
CQtOpenCVCaptureWidget::getPathTitle () const
{ return d_func ()->f_PathTitle; }

QString
CQtOpenCVCaptureWidget::getNumberTitle () const
{ return d_func ()->f_NumberTitle; }

QString
CQtOpenCVCaptureWidget::getTimeOutTitle () const
{ return d_func ()->p_label_TOut->text (); }

QString
CQtOpenCVCaptureWidget::getTimeOutExtTitle () const
{ return d_func ()->p_label_ms->text (); }

QString
CQtOpenCVCaptureWidget::getRecaptureTitle () const
{ return d_func ()->p_checkBox_Recap->text (); }

bool
CQtOpenCVCaptureWidget::isVisible () const
{ return d_func ()->p_Frame->isVisible (); }

void
CQtOpenCVCaptureWidget::slot_setFrameTitle( const QString& value )
{ d_func ()->p_Frame->setWindowTitle (value); }

void
CQtOpenCVCaptureWidget::slot_setGroupBoxTitle( const QString& value )
{ d_func ()->p_groupBox_Capture->setTitle (value); }

void
CQtOpenCVCaptureWidget::slot_setRadioNumberTitle( const QString& value )
{ d_func ()->p_radioButton_Number->setText (value); }

void
CQtOpenCVCaptureWidget::slot_setRadioPathTitle( const QString& value )
{ d_func ()->p_radioButton_URL->setText (value); }

void
CQtOpenCVCaptureWidget::slot_setPathTitle( const QString& value )
{
  d_func ()->f_PathTitle = value;
  if(d_func ()->q_obj->isExternal ())
    d_func ()->p_label_PathNum->setText (d_func ()->f_PathTitle);
}

void
CQtOpenCVCaptureWidget::slot_setNumberTitle( const QString& value )
{
  d_func ()->f_NumberTitle = value;
  if(d_func ()->q_obj->isInternal ())
    d_func ()->p_label_PathNum->setText (d_func ()->f_NumberTitle);
}

void
CQtOpenCVCaptureWidget::slot_setTimeOutTitle ( const QString& value )
{ d_func ()->p_label_TOut->setText (value); }

void
CQtOpenCVCaptureWidget::slot_setTimeOutExtTitle ( const QString& value )
{ d_func ()->p_label_ms->setText (value); }

void
CQtOpenCVCaptureWidget::slot_setRecaptureTitle ( const QString& value )
{ d_func ()->p_checkBox_Recap->setText (value); }

void
CQtOpenCVCaptureWidget::slot_setVisible( bool value )
{ d_func ()->p_Frame->setVisible (value); }

void
CQtOpenCVCaptureWidget::slot_SetNumberMax ( int value )
{ d_func ()->p_spinBox_Number->setMaximum (value < 0 ? 0 : value ); }

void
CQtOpenCVCaptureWidget::slot_SetTimeoutMax ( int value )
{ d_func ()->p_spinBox_TOut->setMaximum (value < 0 ? 0 : value ); }

void
CQtOpenCVCaptureWidget::slot_SetTimeoutStep ( int value )
{ d_func ()->p_spinBox_TOut->setSingleStep (value < 1 ? 1 : value ); }

/*----------------------------------------------------------------------------*/
/*
void
CQtOpenCVCaptureWidget::slot_ShowImage ( const IplImage* value )
{
  if(value)
    cvShowImage (d_func ()->f_title.toStdString ().c_str (), value);
}
*/

/*----------------------------------------------------------------------------*/

