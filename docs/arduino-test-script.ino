const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    recvWithEndMarker();
    showNewData();
}

void recvWithEndMarker()
{
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    while (Serial.available() > 0 && newData == false)
    {
        rc = Serial.read();

        if (rc != endMarker)
        {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars)
            {
                ndx = numChars - 1;
            }
        }
        else
        {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData()
{
    if (newData == true)
    {
        // Serial.print("rec : ");
        // Serial.println(receivedChars);
        if (strcmp(receivedChars, "handshake\n") == 0)
        {
            Serial.println("FancyMorning");
        }

        Serial.print("FancyMorning");
        newData = false;
    }
}