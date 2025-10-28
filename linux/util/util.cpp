/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * This is an open source project, feel free to use
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "util.h"

const int DEFAULT_BAUDRATE = 9600;
constexpr const char SERIAL_DEVICE_PREFIX[6] = "/dev/";
constexpr const char HANDSHAKE_SIGN[11] = "handshake\n";
constexpr const char HANDSHAKE_RESPONSE[14] = "FancyMorning";

const char *Fancy[] = {
    " _______                         ",
    "|    ___|.---.-.-----.----.--.--.",
    "|    ___||  _  |     |  __|  |  |",
    "|___|    |___._|__|__|____|___  |",
    "                          |_____|"};
const char *Morning[] = {
    " _______                    __              ",
    "|   |   |.-----.----.-----.|__|.-----.-----.",
    "|       ||  _  |   _|     ||  ||     |  _  |",
    "|__|_|__||_____|__| |__|__||__||__|__|___  |",
    "                                     |_____|"};
const char *Control[] = {
    "                      ",
    " ______ __         __ ",
    "|      |  |_.----.|  |",
    "|   ---|   _|   _||  |",
    "|______|____|__|  |__|"};
const char *Programming[] = {
    " ______                   ",
    "|   __ \\.----.-----.-----.",
    "|    __/|   _|  _  |  _  |",
    "|___|   |__| |_____|___  |",
    "                   |_____|"};

namespace FancyUtil
{
    int defauldBaud()
    {
        return DEFAULT_BAUDRATE;
    }

    const char *serialDevicePrefix()
    {
        return SERIAL_DEVICE_PREFIX;
    }

    const char *handshakeSign()
    {
        return HANDSHAKE_SIGN;
    }

    const char *handshakeResponse()
    {
        return HANDSHAKE_RESPONSE;
    }

    bool testSerialConnection(serialib serial, char *_serialPortIdentifier)
    {
        char _s_Error = serial.openDevice(
            _serialPortIdentifier,
            defauldBaud());

        if (_s_Error != 1)
        {
            printFetchSerialError();
            strcpy(_serialPortIdentifier, serialDevicePrefix());
        }
        else
        {

            char buffer[15] = "";
            strcpy(buffer, handshakeSign());

            /* Write Fancy Morning Handshake To Serial */
            serial.writeString(buffer);

            /* Read Response Into Buffer */
            serial.readString(buffer, '\n', 50, 2000);

            if (strcmp(buffer, handshakeResponse()) == 0)
            {
                printFetchSerialSuccess();
                printHandshakeSuccess();
                return true;
            }
            else
            {
                printFetchSerialSuccess();
                printHandshakeFailed();
                strcpy(_serialPortIdentifier, serialDevicePrefix());
            }
        }

        return false;
    }

    int selectFromMenu()
    {
        const bool notCanonical = false;

        initscr();
        cbreak();
        noecho();

        printBanner(notCanonical);
        printMenu();

        int ch = 0;
        bool isValidOptionSelected = false;

        while (!isValidOptionSelected)
        {
            refresh();
            ch = getch();

            if (49 <= ch && ch <= 51)
                isValidOptionSelected = true;
        }
        endwin();
        return ch;
    }

    void managementUI(bool isProgramming)
    {
        bool exit = false;
        initscr();
        cbreak();
        noecho();

        printManagementHeader(isProgramming);
        printControlsHeader(isProgramming);

        while (!exit)
        {
            refresh();
            int ch = getch();

            printw("Mennyomva %i\n", ch);
        }

        endwin();
    }

    void printSerialPortInserted(char *portID)
    {
        printf("Serial port inserted via args:\e[0;95m%s\e[0m\n", portID);
    }

    void printBanner(bool isCanonical)
    {
        /* I know I could've made it nicer - no code repeats - shut up! :P XD */
        switch (isCanonical)
        {
        case true:
            printf("\e[1;36m _______                          _______                    __              \n");
            printf("\e[1;36m|    ___|.---.-.-----.----.--.--.|   |   |.-----.----.-----.|__|.-----.-----.\n");
            printf("\e[0;35m|    ___||  _  |     |  __|  |  ||       ||  _  |   _|     ||  ||     |  _  |\n");
            printf("\e[1;95m|___|    |___._|__|__|____|___  ||__|_|__||_____|__| |__|__||__||__|__|___  |\n");
            printf("\e[1;34m                          |_____|                                     |_____|\n");
            printf("developed by Francis Studios | github.com/francisstudios\e[0m\n\n");
            break;
        case false:
            printw(" _______                          _______                    __              \n");
            printw("|    ___|.---.-.-----.----.--.--.|   |   |.-----.----.-----.|__|.-----.-----.\n");
            printw("|    ___||  _  |     |  __|  |  ||       ||  _  |   _|     ||  ||     |  _  |\n");
            printw("|___|    |___._|__|__|____|___  ||__|_|__||_____|__| |__|__||__||__|__|___  |\n");
            printw("                          |_____|                                     |_____|\n");
            printw("developed by Francis Studios | github.com/francisstudios\n\n");
            break;
        }
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

    void printHandshakeFailed()
    {
        printf("\e[0;31m [X] Handshake signature failed \e[0m \n");
    }

    void printHandshakeSuccess()
    {
        printf("\e[0;32m [√] Handshake was successful, device connected\e[0m \n");
    }

    void printMenu()
    {
        printw("Choose from the following options (press a number)...\n");
        printw("\n\n- [1] Program device (for standalone operation)\n");
        printw("- [2] Control device from CLI\n");
        printw("- [3] Manual page (to learn about scripting)\n\n");
    }

    void printManagementHeader(bool isProgramming)
    {
        clear();
        for (int i = 0; i <= 4; i++)
        {
            printw(
                "%s%s\n",
                Fancy[i],
                isProgramming
                    ? Programming[i]
                    : Control[i]);
        }
    }

    void printControlsHeader(bool isProgramming)
    {
        const char *EXIT = "[E]xit";
        const char *PROGRAM = "[P]rogram";
        const char *START = "[S]tart";
        const char *TIME = "[T]ime";
        const char *POINTS = "[D]atapoints";
        const char *NEXT = "[N]ext";

        printw("%s   %s   %s", EXIT, START, NEXT);
    }
}