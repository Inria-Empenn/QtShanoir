#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>
#include "demo.h"
 


#ifdef WIN32
#   ifdef GUI
#       define GUI_EXPORT __declspec(dllexport)
#   else
#       define GUI_EXPORT __declspec(dllimport)
#   endif
#else
#  define GUI_EXPORT
#endif


extern "C"
{
    GUI_EXPORT Demo* createShanoirMainwidget();
}


#endif
