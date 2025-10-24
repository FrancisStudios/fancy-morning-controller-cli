// Serial library
#include "./lib/serialib.h"
#include "./util/util.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    serialib serial;
    bool isSerialDeviceConfirmed = false;
    char ttyDeviceId[32];
    char _serialPortIdentifier[50] = "/dev/";

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
            }
            else
            {
                isSerialDeviceConfirmed = true;

                // Create the string
                char buffer[15] = "handshake\n";

                // Write the string on the serial device
                serial.writeString(buffer);

                FancyUtil::printFetchSerialSuccess();
            }
        }
    }

    printf("Successful connection to %s\n", "/dev/ttyUSB0");

    char buffer[50];
    // // Create the string
    // char buffer[15] = "hello\n";

    // // Write the string on the serial device
    // serial.writeString(buffer);
    // printf("String sent: %s", buffer);

    // Read the string
    serial.readString(buffer, '\n', 50, 2000);
    printf("String read: %s\n", buffer);

    // Close the serial device
    serial.closeDevice();

    return 0;
}