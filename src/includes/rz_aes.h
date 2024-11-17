#pragma once

#include <QCoreApplication>
#include <QCryptographicHash>
#include "qaesencryption.h"

#include "rz_datetime.hpp"

class AesEnc
{
public:
    AesEnc();
    ~AesEnc();

private:
    DateTime datetime;

    struct date_time
    {
        QString humanUTC;
        QString stringUTC;
        QString timeUTC;
        QString timeUtcOffset;
        QString timeZAbbreviation;
        QString localTime;
        QString UTCcurrent;
    };
    date_time dt;
};
