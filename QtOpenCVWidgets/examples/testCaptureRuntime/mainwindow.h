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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../runtime/capture/QtOpenCVCapture/cqtopencvcaptureobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  protected:
    void changeEvent(QEvent *e);

  private Q_SLOTS:
    void slot_Errno(int, const QString& );
    void slot_GetCapture(const CvCapture*);
    void slot_GetImage(const IplImage*);
    void slot_ActiveChanged( bool );

    void on_p_radioButton_URL_toggled(bool checked);
    void on_p_radioButton_Number_toggled(bool checked);
    void on_p_spinBox_Number_valueChanged(int arg1);
    void on_p_spinBox_TOut_valueChanged(int arg1);
    void on_p_checkBox_Recap_toggled(bool checked);
    void on_p_lineEdit_returnPressed();
    void on_p_lineEdit_textChanged(const QString &arg1);
    void on_p_pushButton_On_toggled(bool checked);
    void on_p_pushButton_Activate_toggled(bool checked);
    void on_p_pushButton_Test_toggled(bool checked);

  private:
    Ui::MainWindow *ui;
    CQtOpenCVCaptureObject* p_capture;
    CvCapture* p_c;
    IplImage* p_i;
    QString s_tmp;
};

#endif // MAINWINDOW_H
