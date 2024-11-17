#pragma once

#include <QDebug>
#include <QMap>
#include <QString>

class Plugin
{
public:
    //virtual ~Plugin() = 0;

    virtual QString getNameShort() = 0;
    virtual QString getNameLong() = 0;
    virtual QString getVersion() = 0;
    virtual void doRun(const QString inFile, const QString outFile);
};

Q_DECLARE_INTERFACE(Plugin, "net.hase-zheng.photo_gallery_plugins");
