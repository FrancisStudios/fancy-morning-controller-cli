/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * This is an open source project, feel free to use
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "headless.h"

const char *HEADLESS_PREFIX = "[Fancy Morning] ";

using namespace std::chrono;
using namespace std::this_thread;

serialib serial;

namespace FancyHeadless
{
    void dispatch(char *serialPortId, char *arg)
    {

        printf("%s Starting in headless mode...\n", HEADLESS_PREFIX);
        headlessConnectionTest(serialPortId);

        /* SUCCESS / FAIL */
        printf("%s Attempting handshake...\n", HEADLESS_PREFIX);
        /* ATTEMPT 1,2,3 */
        /* SUCCESS / FAIL */
        printf("%s Sending [%s] to Fancy Morning Controller Device on [%s]\n", HEADLESS_PREFIX, arg, serialPortId);
        /* SUCCESS / FAIL */

        // printf("headless mode \n");
        // printf("arg: %s", arg);

        // if (strcmp(arg, "hello\n"))
        //     printf("yes, hello \n");
    }

    void headlessConnectionTest(char *serialPortId)
    {
        int connectionAttempt = 1;
        char _serialError = 0xff;

        printf("%s Trying to communicate with serial port on [%s] \n",
               HEADLESS_PREFIX,
               serialPortId);

        while (connectionAttempt < 4)
        {
            _serialError = serial.openDevice(
                serialPortId,
                FancyUtil::defauldBaud());

            printf("%s Connection attempt #%i to %s\n",
                   HEADLESS_PREFIX,
                   connectionAttempt,
                   serialPortId);

            if (_serialError == 1)
                break;

            sleep_for(milliseconds(1000));

            connectionAttempt++;
        }

        if (connectionAttempt == 4 && _serialError != 1)
            printf("%s Failed to connect to [%s]\n",
                   HEADLESS_PREFIX,
                   serialPortId);

        if (_serialError == 1)
            printf("%s Succesfully connected to [%s]\n",
                   HEADLESS_PREFIX,
                   serialPortId);
    }
}
