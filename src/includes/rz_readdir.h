#pragma once

#include <QDirIterator>

#include "plog/Log.h"
#include <iostream>

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
