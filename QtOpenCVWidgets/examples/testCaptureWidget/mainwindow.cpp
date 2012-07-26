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
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  cvNamedWindow ("Image", CV_WINDOW_NORMAL);

  connect (ui->cQtOpenCVCaptureWidget, SIGNAL(signal_CaptureChanged(const CvCapture*)),this,SLOT(slot_GetCapture(const CvCapture*)));
  connect (ui->cQtOpenCVCaptureWidget, SIGNAL(signal_ImageChanged(const IplImage*)),this,SLOT(slot_GetImage(const IplImage*)));
  connect (ui->cQtOpenCVCaptureWidget, SIGNAL(signal_Errno(int,QString)), this, SLOT(slot_Errno(int,QString)));
}

MainWindow::~MainWindow()
{
  ui->cQtOpenCVCaptureWidget->slot_captureOn (false);
  delete ui;
  cvDestroyAllWindows ();
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

void MainWindow::slot_GetCapture(const CvCapture* value)
{
  int i = *((int*)(&value));
  ui->label_CaptureAddr->setText(QString("0x") + QString::number (i, 16)+QString("h"));
}

void MainWindow::slot_GetImage(const IplImage* value)
{
  int i = *((int*)(&value));
  ui->label_ImageAddr->setText(QString("0x") + QString::number (i, 16)+QString("h"));
  if(value) cvShowImage ("Image", value);
}

void
MainWindow::slot_Errno(int errno, const QString& errmsg)
{
//  printf("Errno %d: %s\n", errno, QString(errmsg.toLocal8Bit ()).toStdString ().c_str ());
}

