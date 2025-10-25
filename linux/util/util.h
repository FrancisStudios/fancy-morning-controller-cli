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
    void printHandshakeFailed();
    void printHandshakeSuccess();
    int defauldBaud();
    const char *serialDevicePrefix();
    const char *handshakeSign();
    const char *handshakeResponse();
};

#endif