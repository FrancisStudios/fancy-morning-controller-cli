/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * This is an open source project, feel free to use
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#include "headless.h"

#define NO_ERRORS 0
#define ERROR 1
#define CRITICAL_ERROR -1

const char *HEADLESS_PREFIX = "[Fancy Morning] ";

using namespace std::chrono;
using namespace std::this_thread;

serialib serial;

namespace FancyHeadless
{
    void dispatch(char *serialPortId, char *arg)
    {

        FancyUtil::printStartingHeadlessMode(HEADLESS_PREFIX);

        bool connectionTestsPass = headlessConnectionTest(serialPortId) == NO_ERRORS && headlessHandshakeTest(serialPortId) == NO_ERRORS;

        if (connectionTestsPass)
        {
            int PWM_DC = validateInput(arg);

            if (sendPWM(PWM_DC))
            {
                // TODO: sent and acknowledged
                printf("successful");
            } else {
                printf("failed");
            }

            // printf("%s Sending [%i] to Fancy Morning Controller Device on [%s]\n",
            //        HEADLESS_PREFIX,
            //        PWM_DC, 
            //        serialPortId);
            // TODO: this 
        }
    }

    int headlessConnectionTest(char *serialPortId)
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

        return _serialError == 1 ? 0 : 1;
    }

    int headlessHandshakeTest(char *serialPortId)
    {
        int errorState = ERROR;
        char serialBuffer[15] = "";

        strcpy(serialBuffer,
               FancyUtil::handshakeSign());

        FancyUtil::printAttemptingHeadlessHandshake(HEADLESS_PREFIX);

        serial.writeString(serialBuffer);
        serial.readString(serialBuffer, '\n', 15, 2000); // TODO: should have 3 attempts

        int handshakeResponseCorrect =
            strcmp(serialBuffer, FancyUtil::handshakeResponse()) == NO_ERRORS
                ? NO_ERRORS
                : ERROR;

        if (handshakeResponseCorrect == NO_ERRORS)
        {
            FancyUtil::printHeadlessHandshakeSuccess(HEADLESS_PREFIX);
            errorState = NO_ERRORS;
        }
        else
        {
            FancyUtil::printHeadlessHandshakeFailed(HEADLESS_PREFIX);
            errorState = ERROR;
        }

        return errorState;
    }

    int validateInput(char *arg)
    {

        int inputPWMValue = 0;

        try
        {
            inputPWMValue = atoi(arg);
        }
        catch (std::exception const &e)
        {
            return CRITICAL_ERROR;
        }

        bool validationCriteria = (0x00 <= inputPWMValue) && (inputPWMValue <= 0xff);

        return validationCriteria
                   ? inputPWMValue
                   : ERROR;
    }

    bool sendPWM(int pwm)
    {
        char serialBuffer[15] = "";

        std::string pwmAsString = std::to_string(pwm);
        const char *pwmCharPtr = pwmAsString.c_str();

        serial.writeString(FancyUtil::pwmSignature());
        serial.writeString(pwmCharPtr);

        serial.readString(serialBuffer, '\n', 15, 2000);

        return strcmp(serialBuffer, FancyUtil::acknowledgeSignature()) == NO_ERRORS;
    }
}
