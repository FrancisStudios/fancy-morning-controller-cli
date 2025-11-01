/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * This is an open source project, feel free to use
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "headless.h"

const char *HEADLESS_PREFIX = "[Fancy Morning] ";

namespace FancyHeadless
{
    void dispatch(char *serialPortId, char *arg)
    {

        /* THE FLOW SHOULD BE SMTH LIKE THIS:*/

        printf("%s Starting in headless mode...\n", HEADLESS_PREFIX);
        printf("%s Trying to communicate with serial port on [%s] \n", HEADLESS_PREFIX, serialPortId);
        /* ATTEMPT 1,2,3 */
        /* SUCCESS / FAIL */
        printf("%s Attempting handshake...", HEADLESS_PREFIX);
        /* ATTEMPT 1,2,3 */
        /* SUCCESS / FAIL */
        printf("%s Sending [%s] to Fancy Morning Controller Device on [%s]", HEADLESS_PREFIX, arg, serialPortId);
        /* SUCCESS / FAIL */




        
        // printf("headless mode \n");
        // printf("arg: %s", arg);

        // if (strcmp(arg, "hello\n"))
        //     printf("yes, hello \n");
    }
}