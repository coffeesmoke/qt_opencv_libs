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


#ifndef CQTOPENCVCAPTUREWIDGET_H
#define CQTOPENCVCAPTUREWIDGET_H

#include "../../runtime/capture/QtOpenCVCapture/cqtopencvcaptureobject.h"

#include <QtDesigner/QDesignerExportWidget>
#include <QtGui/QWidget>
#include <QScopedPointer>

/*----------------------------------------------------------------------------*/
class CQtOpenCVCaptureWidgetPrivate;
/*----------------------------------------------------------------------------*/
class
    #if defined(QDESIGNER_EXPORT_WIDGETS)
      QDESIGNER_WIDGET_EXPORT
    #else
      Q_DECL_EXPORT
    #endif
CQtOpenCVCaptureWidget :
    public QWidget
{
    Q_OBJECT

    Q_CLASSINFO("brief", "OpenCV Capture Widget class.")
    Q_CLASSINFO("author", "Vladimir N. Litvinenko")
    Q_CLASSINFO("email", "litvinenko.vladimir@gmail.com")
    Q_CLASSINFO("created", "21-JUN-2012")
    Q_CLASSINFO("last modified", "21-JUN-2012")

    Q_PROPERTY(
        bool      visible
        READ      isVisible
        WRITE     slot_setVisible
               )
    Q_PROPERTY(
        bool      internal
        READ      isInternal
        WRITE     slot_SetAsInternal
               )
    Q_PROPERTY(
        QString   path
        READ      getPath
        WRITE     slot_SetPath
               )
    Q_PROPERTY(
        int       number
        READ      getNumber
        WRITE     slot_SetNumber
               )
    Q_PROPERTY(
        int       numberMax
        READ      getNumberMax
        WRITE     slot_SetNumberMax
               )
    Q_PROPERTY(
        int       timeout
        READ      getTimeoutInterval
        WRITE     slot_SetTimeout
               )
    Q_PROPERTY(
        int       timeoutMax
        READ      getTimeoutMax
        WRITE     slot_SetTimeoutMax
               )
    Q_PROPERTY(
        int       timeoutStep
        READ      getTimeoutStep
        WRITE     slot_SetTimeoutStep
               )
    Q_PROPERTY(
        bool      recapture
        READ      isRecap
        WRITE     slot_SetRecap
               )
    Q_PROPERTY(
        QString   FrameTitle
        READ      getFrameTitle
        WRITE     slot_setFrameTitle
               )
    Q_PROPERTY(
        QString   GroupBoxTitle
        READ      getGroupBoxTitle
        WRITE     slot_setGroupBoxTitle
               )
    Q_PROPERTY(
        QString   RadioNumberTitle
        READ      getRadioNumberTitle
        WRITE     slot_setRadioNumberTitle
               )
    Q_PROPERTY(
        QString   RadioPathTitle
        READ      getRadioPathTitle
        WRITE     slot_setRadioPathTitle
               )
    Q_PROPERTY(
        QString   PathTitle
        READ      getPathTitle
        WRITE     slot_setPathTitle
               )
    Q_PROPERTY(
        QString   NumberTitle
        READ      getNumberTitle
        WRITE     slot_setNumberTitle
               )
    Q_PROPERTY(
        QString   TimeOutTitle
        READ      getTimeOutTitle
        WRITE     slot_setTimeOutTitle
               )
    Q_PROPERTY(
        QString   TimeOutExtTitle
        READ      getTimeOutExtTitle
        WRITE     slot_setTimeOutExtTitle
               )
    Q_PROPERTY(
        QString   RecaptureTitle
        READ      getRecaptureTitle
        WRITE     slot_setRecaptureTitle
               )
  public:
    explicit
    CQtOpenCVCaptureWidget(QWidget *parent = 0);
    virtual
    ~CQtOpenCVCaptureWidget();

    CQtOpenCVCaptureObject* asRuntime () const;

    CvCapture*  getCapture () const;
    QString     getPath () const;
    int         getNumber () const;
    int         getTimeoutInterval () const;
    int         getNumberMax () const;
    int         getTimeoutMax () const;
    int         getTimeoutStep () const;
    IplImage*   getImage () const;
    int         getFrameCount () const;

    bool        isInternal () const;
    bool        isExternal () const;
    bool        isActive () const;
    bool        isRecap () const;

    //собственные методы доступа
    bool        isVisible () const;
    QString     getFrameTitle () const;
    QString     getGroupBoxTitle () const;
    QString     getRadioNumberTitle () const;
    QString     getRadioPathTitle () const;
    QString     getPathTitle () const;
    QString     getNumberTitle () const;
    QString     getTimeOutTitle () const;
    QString     getTimeOutExtTitle () const;
    QString     getRecaptureTitle () const;

  signals:
    void  signal_Errno ( int, const QString& );
    void  signal_CaptureChanged ();
    void  signal_CaptureChanged ( const CvCapture* );
    void  signal_ImageChanged ( const IplImage* );
    void  signal_TimeoutChanged ();
    void  signal_TimeoutChanged ( int );
    void  signal_ActiveChanged ( bool );

  private slots:
    void  slot_PathComplete ();
    void  slot_SetPath ( const QString& );

  public slots:
    void  slot_SetNumber ( int );
    void  slot_SetAsInternal ( bool );
    void  slot_SetAsExternal ( bool );
    void  slot_SetTimeout ( int );
    void  slot_captureOn ( bool );
    void  slot_Activate (bool);
    void  slot_SetRecap (bool);
    void  slot_Test (bool);

    //собственные слоты
    void  slot_setVisible( bool );
    void  slot_setFrameTitle( const QString& );
    void  slot_setGroupBoxTitle( const QString& );
    void  slot_setRadioNumberTitle( const QString& );
    void  slot_setRadioPathTitle( const QString& );
    void  slot_setPathTitle( const QString& );
    void  slot_setNumberTitle( const QString& );
    void  slot_setTimeOutTitle( const QString& );
    void  slot_setTimeOutExtTitle( const QString& );
    void  slot_setRecaptureTitle( const QString& );
    void  slot_SetNumberMax ( int );
    void  slot_SetTimeoutMax ( int );
    void  slot_SetTimeoutStep ( int );

  private slots:
//    void  slot_ShowImage ( const IplImage* );
  private:
    void close ();
    Q_DISABLE_COPY(CQtOpenCVCaptureWidget)
    Q_DECLARE_PRIVATE(CQtOpenCVCaptureWidget)

    QScopedPointer<CQtOpenCVCaptureWidgetPrivate> d_ptr;
};

/*----------------------------------------------------------------------------*/

#endif // CQTOPENCVCAPTUREWIDGET_H
