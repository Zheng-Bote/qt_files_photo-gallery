#include "rz_aes.h"

AesEnc::AesEnc()
{
    datetime.setDateTime();
    QString utcTime = datetime.getHumanUTC();
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

    QDateTime UTC(QDateTime::currentDateTimeUtc());
    dt.humanUTC = UTC.toString("yyyy-MM-dd HH:mm:ss");

    qDebug() << "dt: " << dt.humanUTC.toStdString() << "\n";

    QString inputStr("TopSecret");
    QString key("00110010 00100000 01101000 01101111 01110100 00100000 00110100 00100000 01011001 "
                "01110101");
    QString iv(dt.humanUTC);

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey, hashIV);
    QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);

    QString decodedString = QString(encryption.removePadding(decodeText));

    qDebug() << encodeText << "\n";
    qDebug() << decodeText << "\n";
    qDebug() << decodedString << "\n";
}

AesEnc::~AesEnc() {}
