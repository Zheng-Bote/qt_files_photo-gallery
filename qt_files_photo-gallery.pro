QT = core
QT += sql
CONFIG += c++20 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Includes/rz_inifile.cpp \
        Includes/rz_readdir.cpp \
        Includes/rz_pg_db.cpp \
        main.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Includes/cxxopts.hpp \
    Includes/rz_inifile.h \
    Includes/rz_readdir.h \
    Includes/rz_pg_db.h
