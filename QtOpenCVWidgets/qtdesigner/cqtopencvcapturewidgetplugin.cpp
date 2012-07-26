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


#include "../widgets/QtOpenCVCaptureWidget/cqtopencvcapturewidget.h"
#include "cqtopencvcapturewidgetplugin.h"

#include <QtCore/QtPlugin>

CQtOpenCVCaptureWidgetPlugin::CQtOpenCVCaptureWidgetPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void CQtOpenCVCaptureWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool CQtOpenCVCaptureWidgetPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *CQtOpenCVCaptureWidgetPlugin::createWidget(QWidget *parent)
{
  return new CQtOpenCVCaptureWidget(parent);
}

QString CQtOpenCVCaptureWidgetPlugin::name() const
{
  return QLatin1String("CQtOpenCVCaptureWidget");
}

QString CQtOpenCVCaptureWidgetPlugin::group() const
{
  return QLatin1String("QtOpenCV Group");
}

QIcon CQtOpenCVCaptureWidgetPlugin::icon() const
{
  return QIcon(QLatin1String(":/QtOpenCVLogo.png"));
}

QString CQtOpenCVCaptureWidgetPlugin::toolTip() const
{
  return QLatin1String("Qt-OpenCV Widgets");
}

QString CQtOpenCVCaptureWidgetPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool CQtOpenCVCaptureWidgetPlugin::isContainer() const
{
  return false;
}

QString CQtOpenCVCaptureWidgetPlugin::domXml() const
{
  return QLatin1String("\
  <widget class=\"CQtOpenCVCaptureWidget\" name=\"cQtOpenCVCaptureWidget\">\n \
    <property name=\"geometry\">\n \
     <rect>\n \
       <x>0</x>\n \
       <y>0</y>\n \
       <width>550</width>\n \
       <height>195</height>\n \
      </rect>\n \
    </property>\n \
  </widget>\n"
                       );
}

QString CQtOpenCVCaptureWidgetPlugin::includeFile() const
{
  return QLatin1String("cqtopencvcapturewidget.h");
}

