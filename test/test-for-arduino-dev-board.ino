#define RECEIVE_LN 0x20
#define BAUDRATE 9600
#define CTRL_PIN 11
#define HANDSHAKE "handshake"
#define PWM_SIGNAL "pp"
#define ACKNOWLEDGE_SIGNAL "ack"
#define STRING_TERMINATOR '\0'
#define END_MARKER '\n'

bool endReception = false;
bool PWMSignalOn = false;

char receivedCharPtr[RECEIVE_LN];

void setup()
{
    Serial.begin(BAUDRATE);
    pinMode(OUTPUT, CTRL_PIN);
    analogWrite(CTRL_PIN, 0x00);
}

void loop()
{
    receiveWithEndMarker();
    dataProcessing();
}

void receiveWithEndMarker()
{
    static byte ndx = 0;
    char _receivedChar;

    while (Serial.available() > 0x00 && endReception == false)
    {
        _receivedChar = Serial.read();

        if (_receivedChar != END_MARKER)
        {
            receivedCharPtr[ndx] = _receivedChar;
            ndx++;

            if (ndx >= RECEIVE_LN)
            {
                ndx = RECEIVE_LN - 1;
            }
        }
        else
        {
            receivedCharPtr[ndx] = STRING_TERMINATOR;
            ndx = 0;
            endReception = true;
        }
    }
}

void dataProcessing()
{
    if (endReception)
    {
        if (strcmp(receivedCharPtr, HANDSHAKE) == 0)
        {
            Serial.println("FancyMorning");
        }

        if (PWMSignalOn)
        {
            analogWrite(atoi(receivedCharPtr), CTRL_PIN);
            Serial.println(ACKNOWLEDGE_SIGNAL);
            PWMSignalOn = false;
        }

        if (strcmp(receivedCharPtr, PWM_SIGNAL) == 0)
        {
            PWMSignalOn = true;
        }

        endReception = false;
    }
}