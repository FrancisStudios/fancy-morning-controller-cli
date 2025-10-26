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

int main(int argc, char *argv[])
{
    serialib serial;
    bool isSerialDeviceConfirmed = false;
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

    FancyUtil::selectFromMenu();

    serial.closeDevice();

    return 0;
}