#include "util.h"

const int DEFAULT_BAUDRATE = 9600;
constexpr const char SERIAL_DEVICE_PREFIX[6] = "/dev/";

namespace FancyUtil
{
    int defauldBaud()
    {
        return DEFAULT_BAUDRATE;
    }

    const char* serialDevicePrefix()
    {
        return SERIAL_DEVICE_PREFIX;
    }

    void printBanner()
    {
        printf("\e[1;36m _______                          _______                    __              \n");
        printf("\e[1;36m|    ___|.---.-.-----.----.--.--.|   |   |.-----.----.-----.|__|.-----.-----.\n");
        printf("\e[0;35m|    ___||  _  |     |  __|  |  ||       ||  _  |   _|     ||  ||     |  _  |\n");
        printf("\e[1;95m|___|    |___._|__|__|____|___  ||__|_|__||_____|__| |__|__||__||__|__|___  |\n");
        printf("\e[1;34m                          |_____|                                     |_____|\n");
        printf("by Francis Studios | github.com/francisstudios\e[0m\n\n");
    }

    void printNoSerialPortSelectedWording()
    {
        printf("\e[0;31mNo serial port\e[0m was specified as an argument - please enter the serial port\n");
        printf("identifier where your \e[0;95mFancy Morning Led Controller\e[0m device is connected\n");
        printf("we are looking for something like /dev/tty*** on linux\n\n");
    }

    void printFetchSerialError()
    {
        printf("\n\e[0;31m [X] Can not connect to this serial port \e[0m \n");
        printf(" Check privileges and port availability\n\n");
    }

    void printFetchSerialSuccess()
    {
        printf("\n\e[0;32m [√] Serial device connected successfully \e[0m \n");
    }

};