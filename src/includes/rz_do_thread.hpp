#pragma once

#include <QCoreApplication>
#include <QObject>

#include <QPluginLoader>
#include <QRunnable>
#include <QThread>

#include "rz_photo-gallery_plugins.hpp"

class DoThread : public QRunnable
{
public:
    DoThread();
    ~DoThread();

    void run() override;

    void setPluginFile(const QString &pluginFile);
    void setInFile(const QString &inFile);
    void setOutFile(const QString &outFile);

private:
    QString pluginFile, inFile, outFile;
};
