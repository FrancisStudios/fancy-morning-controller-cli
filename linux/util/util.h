#ifndef UTIL_H
#define UTIL_H

#pragma once
#include <stdio.h>

namespace FancyUtil
{
    void printBanner();
    void printNoSerialPortSelectedWording();
    void printFetchSerialError();
    void printFetchSerialSuccess();
    int defauldBaud();
    const char* serialDevicePrefix();
};

#endif