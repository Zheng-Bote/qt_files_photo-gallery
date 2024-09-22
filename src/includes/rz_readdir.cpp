#include "rz_readdir.h"

ReadDir::ReadDir()
{
    QDir path = QDir::currentPath();
    ReadDir::path = path.path();
}

ReadDir::ReadDir(QString &dir)
{
    ReadDir::path = dir;
}

ReadDir::~ReadDir() {}

void ReadDir::searchFiles()
{
    QDirIterator picsFileIt(ReadDir::path, {"*.jpg", "*.jpeg", "*.png", "*.bmp"}, QDir::Files);

    while (picsFileIt.hasNext()) {
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

    while (picsFileIt.hasNext()) {
        QFile f(picsFileIt.next());
        ReadDir::fileInfo(f);
    }
}

void ReadDir::fileInfo(QFile &f)
{
    // path/to/file
    std::cout << "# " << f.fileName().toUtf8().toStdString() << std::endl;

    // filename
    QFileInfo fileInfo(f.fileName());
    std::cout << "## " << fileInfo.completeBaseName().toStdString() << " " << f.size() / 1024
              << "Kb" << std::endl;

    // file extension
    std::cout << "## " << fileInfo.completeSuffix().toStdString() << std::endl;

    // only dir
    QDir d = QFileInfo(f).absoluteDir();
    std::cout << "### " << d.absolutePath().toStdString() << std::endl;

    // cutted dir
    /*      QString fPath = d.absolutePath();
        fPath.remove(replacePath);
        std::cout << "#### " << fPath.toStdString() << std::endl;
        */
}
