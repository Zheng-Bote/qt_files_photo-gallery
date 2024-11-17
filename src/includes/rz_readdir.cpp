/**
 * @file rz_readdir.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief simple lib for folders and files
 * @details simple class for directories
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#include "rz_readdir.hpp"

ReadDir::ReadDir()
{
    QDir qdir_path = QDir::currentPath();
    ReadDir::path = qdir_path.path();
}

ReadDir::ReadDir(QString &dir)
{
    ReadDir::path = dir;
}

ReadDir::~ReadDir() {}

void ReadDir::searchFiles()
{
    QDirIterator picsFileIt(ReadDir::path, {"*.jpg", "*.jpeg", "*.png", "*.bmp"}, QDir::Files);

    while (picsFileIt.hasNext())
    {
        QFile f(picsFileIt.next());
        ReadDir::fileInfo(f);
    }
}

void ReadDir::searchFilesRekursive()
{
    // PLOG_FATAL << "This is a FATAL message from readdir";
    QDirIterator picsFileIt(ReadDir::path,
                            {"*.jpg", "*.jpeg", "*.png", "*.bmp"},
                            QDir::Files,
                            QDirIterator::Subdirectories);

    while (picsFileIt.hasNext())
    {
        QFile f(picsFileIt.next());
        ReadDir::fileInfo(f);
    }
}

void ReadDir::fileInfo(QFile &f)
{
    // path/to/file
    std::println("# {}", f.fileName().toUtf8().toStdString());

    // filename
    QFileInfo fileInfo(f.fileName());
    std::println("## {} {}Kb", fileInfo.completeBaseName().toStdString(), f.size() / 1024);

    // file extension
    std::println("## {}", fileInfo.completeSuffix().toStdString());

    // only dir
    QDir d = QFileInfo(f).absoluteDir();
    std::println("### {}", d.absolutePath().toStdString());

    // cutted dir
    /*      QString fPath = d.absolutePath();
        fPath.remove(replacePath);
        std::cout << "#### " << fPath.toStdString() << std::endl;
        */
}
