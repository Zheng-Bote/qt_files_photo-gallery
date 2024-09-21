#pragma once

#include <QDebug>
#include <QDirIterator>

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
