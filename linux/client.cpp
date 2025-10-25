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

            char _s_Error = serial.openDevice(
                _serialPortIdentifier,
                FancyUtil::defauldBaud());

            if (_s_Error != 1)
            {
                FancyUtil::printFetchSerialError();
                strcpy(_serialPortIdentifier, FancyUtil::serialDevicePrefix());
            }
            else
            {

                char buffer[15] = "";
                strcpy(buffer, FancyUtil::handshakeSign());

                /* Write Fancy Morning Handshake To Serial */
                serial.writeString(buffer);

                /* Read Response Into Buffer */
                serial.readString(buffer, '\n', 50, 2000);

                if (strcmp(buffer, FancyUtil::handshakeResponse()) == 0)
                {
                    FancyUtil::printFetchSerialSuccess();
                    FancyUtil::printHandshakeSuccess();
                    isSerialDeviceConfirmed = true;
                }
                else
                {
                    FancyUtil::printFetchSerialSuccess();
                    FancyUtil::printHandshakeFailed();
                    strcpy(_serialPortIdentifier, FancyUtil::serialDevicePrefix());
                }
            }
        }
    }
    else
    {
        /* If tty Device Is Passed As An Arg */
        const char *serialPortIdInput = argv[1];
        strcpy(_serialPortIdentifier, serialPortIdInput);
    
        FancyUtil::printBanner();
        FancyUtil::printSerialPortInserted(_serialPortIdentifier);
    }

    serial.closeDevice();

    return 0;
}