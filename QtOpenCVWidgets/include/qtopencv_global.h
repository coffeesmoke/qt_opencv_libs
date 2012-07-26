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


#ifndef QTOPENCV_GLOBAL_H
#define QTOPENCV_GLOBAL_H

#include <QtCore/QtGlobal>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

/*----------------------------------------------------------------------------*/
#if defined(QTOPENCV_LIB_EXPORT)
#  define QTOPENCV_DECLARE_EXPORT Q_DECL_EXPORT
#else
#  define QTOPENCV_DECLARE_EXPORT Q_DECL_IMPORT
#endif

/*----------------------------------------------------------------------------*/
#define TITLE_FRAME         QString::fromUtf8("Свойства устройства видеозахвата")
#define TITLE_GROUP_BOX     QString::fromUtf8("Устройство видеозахвата")
#define TITLE_RADIO_URL     QString::fromUtf8("Файл или URL")
#define TITLE_RADIO_NUM     QString::fromUtf8("Камера")
#define TITLE_TIMEOUT       QString::fromUtf8("Интервал опроса:")
#define TITLE_TIMEOUT_EXT   QString::fromUtf8("(мс)")
#define TITLE_RECAPTURE     QString::fromUtf8("Перезахват по таймауту")
#define TITLE_CAMERA_NUMBER QString::fromUtf8("Номер вебкамеры:")
#define TITLE_CAMERA_PATH   QString::fromUtf8("Путь к источнику видео:")
#define TITLE_BUTTON_TEST   QString::fromUtf8("Проверка")
/*----------------------------------------------------------------------------*/
#define DEFAULT_QWERY_FRAME_INTERVAL 0

/*----------------------------------------------------------------------------*/
#define ERR_NONE 0

#define ERR_CREATE_CAPTURE -1000
#define ERR_CREATE_CAPTURE_MSG QString::fromUtf8("Ошибка инициализации устройства видеозахвата.")

#define ERR_RELEASE_CAPTURE -1010
#define ERR_RELEASE_CAPTURE_MSG QString::fromUtf8("Ошибка освобождения памяти устройством видеозахвата.")

#define ERR_CREATE_IMAGE -1100
#define ERR_CREATE_IMAGE_MSG QString::fromUtf8("Ошибка копирования изображения из выборки.")
#define ERR_RELEASE_IMAGE -1110
#define ERR_RELEASE_IMAGE_MSG QString::fromUtf8("Ошибка освобождения памяти изображением.")
#define ERR_QWERY_IMAGE -1120
#define ERR_QWERY_IMAGE_MSG QString::fromUtf8("Ошибка запроса очередного фрейма из устройства видеозахвата.")

#define ERR_RESTART -1200
#define ERR_RESTART_MSG QString::fromUtf8("Ошибка перезапуска таймаута опроса устройства видеозахвата.")

QT_END_NAMESPACE

QT_END_HEADER

#endif // QTOPENCV_GLOBAL_H
