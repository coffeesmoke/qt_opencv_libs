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


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  p_capture(new CQtOpenCVCaptureObject(this)),
  p_c(NULL),
  p_i(NULL)
{
  s_tmp.clear ();

  ui->setupUi(this);

  ui->p_label_ErrMsg->setText (QString::fromUtf8 ("отсутствует."));

  p_capture->slot_captureOn (false);
  p_capture->slot_Activate (false);
  ui->p_radioButton_Number->setChecked (true);

  on_p_radioButton_Number_toggled (true);

  cvNamedWindow("Image");

  connect (p_capture, SIGNAL(signal_ImageChanged(const IplImage*)), this, SLOT(slot_GetImage(const IplImage*)) );
  connect (p_capture, SIGNAL(signal_CaptureChanged(const CvCapture*)), this, SLOT(slot_GetCapture(const CvCapture*)) );
  connect (p_capture, SIGNAL(signal_ActiveChanged(bool)), this, SLOT(slot_ActiveChanged(bool)) );
  connect (p_capture, SIGNAL(signal_Errno(int,QString)), this, SLOT(slot_Errno(int,QString)) );
}

MainWindow::~MainWindow()
{
  cvDestroyAllWindows ();
  p_capture->slot_captureOn (false);
  delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void
MainWindow::slot_ActiveChanged( bool value )
{
  ui->p_pushButton_Activate->setChecked (value);
}

void MainWindow::slot_GetCapture(const CvCapture* value)
{
  ui->p_pushButton_On->setChecked (value != NULL);
  if(value == NULL) {
    ui->p_label_CaptureAddr->setText("NULL");
  } else {
    int i = *((int*)(&value));
    ui->p_label_CaptureAddr->setText(QString("0x") + QString::number (i, 16)+QString("h"));
  }
}

void MainWindow::slot_GetImage(const IplImage* value)
{
  if(value == NULL) {
    ui->p_label_ImageAddr->setText("NULL");
  } else {
    int i = *((int*)(&value));
    ui->p_label_ImageAddr->setText(QString("0x") + QString::number (i, 16)+QString("h"));
    cvShowImage("Image", value);
  }
}

void
MainWindow::slot_Errno(int errno, const QString& errmsg)
{
  if(errmsg.isEmpty ())
    ui->p_label_ErrMsg->setText ("");
  else
    ui->p_label_ErrMsg->setText (QString::fromUtf8 ("Номер= ")+QString::number (errno)+ " ("+errmsg+")");
}

void MainWindow::on_p_radioButton_URL_toggled(bool checked)
{
  ui->p_label_PathNum->setText (QString::fromUtf8 ("Файл или URL:"));
  ui->p_lineEdit->setVisible (checked);
  ui->p_spinBox_Number->setVisible (!checked);
  p_capture->slot_SetAsInternal (!checked);
}

void MainWindow::on_p_radioButton_Number_toggled(bool checked)
{
  ui->p_label_PathNum->setText (QString::fromUtf8 ("Номер вебкамеры:"));
  ui->p_lineEdit->setVisible (!checked);
  ui->p_spinBox_Number->setVisible (checked);
  p_capture->slot_SetAsInternal (checked);
}

void MainWindow::on_p_spinBox_Number_valueChanged(int arg1)
{
  p_capture->slot_SetNumber (arg1);
}

void MainWindow::on_p_spinBox_TOut_valueChanged(int arg1)
{
  p_capture->slot_SetTimeout (arg1);
}

void MainWindow::on_p_checkBox_Recap_toggled(bool checked)
{
  slot_Errno (0,"");
  p_capture->slot_SetRecap (checked);
}

void MainWindow::on_p_lineEdit_returnPressed()
{
  p_capture->slot_SetPath (s_tmp);
}

void MainWindow::on_p_lineEdit_textChanged(const QString &arg1)
{
  s_tmp = arg1;
}

void MainWindow::on_p_pushButton_On_toggled(bool checked)
{
  slot_Errno (0,"");
  p_capture->slot_captureOn (checked);
}

void MainWindow::on_p_pushButton_Activate_toggled(bool checked)
{
  slot_Errno (0,"");
  p_capture->slot_Activate (checked);
}

void MainWindow::on_p_pushButton_Test_toggled(bool checked)
{
  slot_Errno (0,"");
  ui->p_pushButton_On->setChecked (checked);
  ui->p_pushButton_Activate->setChecked (checked);
}
