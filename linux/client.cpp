// Serial library
#include "./lib/serialib.h"
#include "./util/util.h"
#include <unistd.h>
#include <stdio.h>

#if defined(__linux__) || defined(__APPLE__)
#define SERIAL_PORT "/dev/ttyUSB0"
#endif

int main(int argc, char *argv[])
{
    serialib serial;

    if (argc <= 1)
    {
        FancyUtil::printBanner();
    }

    char errorOpening = serial.openDevice("/dev/ttyUSB0", 9600);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1)
    {
        printf("Error while opening serial\n");
        return errorOpening;
    }

    printf("Successful connection to %s\n", SERIAL_PORT);

    // Create the string
    char buffer[15] = "hello\n";

    // Write the string on the serial device
    serial.writeString(buffer);
    printf("String sent: %s", buffer);

    // Read the string
    serial.readString(buffer, '\n', 14, 2000);
    printf("String read: %s\n", buffer);

    // Close the serial device
    serial.closeDevice();

    return 0;
}