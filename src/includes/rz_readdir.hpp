/**
 * @file rz_rz_readdir.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple lib for folders and files
 * @details simple class for directories
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#pragma once

#include <QDirIterator>

#include "plog/Log.h"
#include <print>

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
