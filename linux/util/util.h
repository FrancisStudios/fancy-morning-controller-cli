/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * This is an open source project, feel free to use
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

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
    void printSerialPortInserted(char *portID);
    int defauldBaud();
    const char *serialDevicePrefix();
    const char *handshakeSign();
    const char *handshakeResponse();
};

#endif