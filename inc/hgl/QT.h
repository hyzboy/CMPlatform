#ifndef HGL_QT_INCLUDE
#define HGL_QT_INCLUDE

#include<hgl/type/QTString.h>
#include<QObject>

#define QTConnect(obj,event,class_pointer,slot_func)    QObject::connect(obj,SIGNAL(event()),class_pointer,SLOT(slot_func()))

#endif//HGL_QT_INCLUDE

