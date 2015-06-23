TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = system_pro

QMAKE_CXXFLAGS += -static  #×èÖ¹Á´½Ó¹²Ïí¿â
QMAKE_CXXFLAGS += -Wshadow #¸²¸Ç¼ì²â

INCLUDEPATH = \
    ../inc/  \


SOURCES += \
    ../src/auto_test.c \
    ../src/darray.c \
    ../src/dlist.c \
    ../src/lcontainer_darray.c \
    ../src/lcontainer_dlist.c \
    ../src/locker_pthread.c \
    ../src/locker_pthread_nest.c \
    ../src/main.c \
    ../src/philosopher.c \
    ../src/pthread_test.c \
    ../src/queue.c \
    ../src/rw_locker.c \
    ../src/PolynomialFitting.c

HEADERS += \
    ../inc/darray.h \
    ../inc/dlist.h \
    ../inc/lcontainer.h \
    ../inc/lcontainer_darray.h \
    ../inc/lcontainer_dlist.h \
    ../inc/locker.h \
    ../inc/locker_pthread.h \
    ../inc/locker_pthread_nest.h \
    ../inc/queue.h \
    ../inc/rw_locker.h \
    ../inc/test.h \
    ../inc/typesdef.h \
    ../inc/PolynomialFitting.h

unix:  SOURCES += \../src/socket.c

