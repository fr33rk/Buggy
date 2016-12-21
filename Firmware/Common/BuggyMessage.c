#include <pic18.h>

#include "BuggyMemory.h"
#include "BuggyMessage.h"
#include "Version.h"
#include "AnalogSensors.h"

void CreateVersionMessage(BuggyMessage *pMessage)
{
    pMessage->Command = cmdVersion;
    pMessage->DataSize = 3;
    
    pMessage->Data[0] = MAJOR;
    pMessage->Data[1] = MINOR;
    pMessage->Data[2] = BUILD;
}

void CreateResetDoneMessage(BuggyMessage *pMessage)
{
    pMessage->Command = cmdResetDone;
    pMessage->DataSize = 0;
}

void CreateSensorResultMessage(BuggyMessage *pMessage, AnalogSensor sensor, uint16_t value)
{
    pMessage->Command = cmdSensorResult;
    pMessage->DataSize = 3;
    
    pMessage->Data[0] = sensor;
    pMessage->Data[1] = HIGH_BYTE(sensor);
    pMessage->Data[2] = LOW_BYTE(sensor);            
}

void CreateAllSensorResultMessage(BuggyMessage *pMessage)
{
    uint16_t sensorVal;
    
    pMessage->Command = cmdSensorResult;
    
    sensorVal = GetLastReading(DistanceLeft);
    pMessage->Data[0] = HIGH_BYTE(sensorVal);
    pMessage->Data[1] = LOW_BYTE(sensorVal);

    sensorVal = GetLastReading(DistanceFront);
    pMessage->Data[2] = HIGH_BYTE(sensorVal);
    pMessage->Data[3] = LOW_BYTE(sensorVal);

    sensorVal = GetLastReading(DistanceRight);
    pMessage->Data[4] = HIGH_BYTE(sensorVal);
    pMessage->Data[5] = LOW_BYTE(sensorVal);

    sensorVal = GetLastReading(Light);
    pMessage->Data[6] = HIGH_BYTE(sensorVal);
    pMessage->Data[7] = LOW_BYTE(sensorVal);

    sensorVal = GetLastReading(Microphone);
    pMessage->Data[8] = HIGH_BYTE(sensorVal);
    pMessage->Data[9] = LOW_BYTE(sensorVal);
    
    // Line sensors
    pMessage->Data[10] = PORTBbits.RB0 & PORTBbits.RB1; 
}

void CreateSteerMotorDoneMessage(BuggyMessage *pMessage)
{
    pMessage->Command = cmdSteerMotorDone;
    pMessage->DataSize = 0;
}

void CreateSendErrorMessage(BuggyMessage *pMessage, ErrorCode errorCode)
{
    pMessage->Command = cmdSendError;
    pMessage->DataSize = 1;
    pMessage->Data[0] = errorCode;
}
