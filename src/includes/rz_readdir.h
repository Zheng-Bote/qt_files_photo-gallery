#pragma once

#include <QDirIterator>

#include <iostream>
#include <plog/Log.h>

class ReadDir
{
public:
    ReadDir();
    ReadDir(QString &dir);
    ~ReadDir();

    void Test();

    void searchFiles();
    void searchFilesRekursive();

    void fileInfo(QFile &f);

private:
    QString path{};
};
