#include "rz_do_thread.h"

DoThread::DoThread() {}

void DoThread::run()
{
    QPluginLoader pLoader(pluginFile);
    if (!pLoader.load()) {
        qDebug() << "Error: " << pLoader.fileName() << " Error: " << pLoader.errorString();
        //return;
    }

    //qDebug() << "Loaded: " << pLoader.fileName();

    Plugin *pPlugin = qobject_cast<Plugin *>(pLoader.instance());
    if (pPlugin) {
        //qInfo() << "Plugin loaded: " << pPlugin->getVersion();
        pPlugin->doRun(inFile, outFile);
    }
}

void DoThread::setPluginFile(const QString &plugin_file)
{
    pluginFile = plugin_file;
}

void DoThread::setInFile(const QString &in_File)
{
    inFile = in_File;
}

void DoThread::setOutFile(const QString &out_file)
{
    outFile = out_file;
}
