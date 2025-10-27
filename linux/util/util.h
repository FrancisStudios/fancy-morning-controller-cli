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
#include "../lib/serialib.h"
#include <unistd.h>
#include <ncurses.h>

namespace FancyUtil
{
    void printBanner(bool isCanonical = true);
    void printNoSerialPortSelectedWording();
    void printFetchSerialError();
    void printFetchSerialSuccess();
    void printHandshakeFailed();
    void printHandshakeSuccess();
    void printSerialPortInserted(char *portID);
    void printMenu();
    bool testSerialConnection(serialib serial, char *_serialPortIdentifier);
    int selectFromMenu();
    int defauldBaud();
    const char *serialDevicePrefix();
    const char *handshakeSign();
    const char *handshakeResponse();
};

#endif