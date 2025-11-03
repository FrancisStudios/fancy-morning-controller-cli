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
    void printStartingHeadlessMode(const char *HEADLESS_PREFIX);
    void printAttemptingHeadlessHandshake(const char *HEADLESS_PREFIX);
    void printHeadlessHandshakeSuccess(const char *HEADLESS_PREFIX);
    void printHeadlessHandshakeFailed(const char *HEADLESS_PREFIX);
    void printNoSerialPortSelectedWording();
    void printFetchSerialError();
    void printFetchSerialSuccess();
    void printHandshakeFailed();
    void printHandshakeSuccess();
    void printSerialPortInserted(char *portID);
    void printMenu();
    void printManagementHeader(bool isProgramming);
    void printControlsHeader(bool isProgramming);
    void printUIElements();
    void managementUI(bool isProgramming, char *tty_portname);
    bool testSerialConnection(serialib serial, char *_serialPortIdentifier);
    int selectFromMenu();
    int defauldBaud();
    const char *pwmSignature();
    const char *serialDevicePrefix();
    const char *handshakeSign();
    const char *handshakeResponse();
};

#endif