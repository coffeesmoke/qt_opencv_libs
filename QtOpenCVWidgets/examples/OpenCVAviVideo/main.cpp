#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QString>
#include <stdio.h>

int main()
{
  cvNamedWindow ("Example2", CV_WINDOW_AUTOSIZE );
  QString path = QString::fromLatin1 ("/home/developer/Видео/IceAge3.avi");
  printf("path = %s\n", path.toStdString ().c_str ());
  CvCapture* capture = cvCreateFileCapture (path.toStdString ().c_str ());
  IplImage* frame; // Здесь будет кадр

  while(1) {
    frame = cvQueryFrame( capture ); // Читаем кадр из файла
    if( !frame ) break; // Если кадров больше нет - выходим
    cvShowImage ("Example2", frame ); // Выводим кадр
    char c = (char)cvWaitKey (33); // Ждем 33мс
    if( c == 27 ) break; // Если нажали Esc - выходим
  }
  cvReleaseCapture( &capture ); // Закрываем файл
  cvDestroyWindow( "Example2" );
  return (0);
}

