/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * This is an open source project, feel free to use
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "./lib/serialib.h"
#include "./util/util.h"
#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{

    using namespace std::this_thread;
    using namespace std::chrono;

    serialib serial;
    bool isSerialDeviceConfirmed = false;
    bool isProgramming = true;
    bool isControlMenu = !isProgramming;
    char ttyDeviceId[32];
    char _serialPortIdentifier[50] = "";
    strcpy(_serialPortIdentifier, FancyUtil::serialDevicePrefix());

    if (argc <= 1)
    {
        FancyUtil::printBanner();
        FancyUtil::printNoSerialPortSelectedWording();

        while (!isSerialDeviceConfirmed)
        {
            printf("\e[0;35m/dev/\e[0;32m");
            scanf("%31s", ttyDeviceId);
            printf("\e[0m ");

            strcat(_serialPortIdentifier, ttyDeviceId);

            isSerialDeviceConfirmed =
                FancyUtil::testSerialConnection(serial, _serialPortIdentifier);
        }
    }
    else
    {
        /* If tty Device Is Passed As An Arg */
        const char *serialPortIdInput = argv[1];
        strcpy(_serialPortIdentifier, serialPortIdInput);

        FancyUtil::printBanner();
        FancyUtil::printSerialPortInserted(_serialPortIdentifier);

        FancyUtil::testSerialConnection(serial, _serialPortIdentifier);
    }

    sleep_for(milliseconds(1000));

    switch (FancyUtil::selectFromMenu())
    {
    case 49:
        FancyUtil::managementUI(isProgramming);
        break;

    case 50:
        FancyUtil::managementUI(isControlMenu);
        break;

    case 51:
        break;

    default:
        /* TODO: maybe some error handling */
        break;
    }

    serial.closeDevice();

    return 0;
}