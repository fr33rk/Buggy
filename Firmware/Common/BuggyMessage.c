#include <pic18.h>

#include <string.h>
#include "BuggyMemory.h"
#include "BuggyMessage.h"
#include "MessageFIFOBuffer.h"

/**
 * Store a received message in memory for later processing.
 * @param message
 */
void ReceiveMessage(const uint8_t *message)
{
    memcpy (BuggyMemory.LastMessage.AsBuffer, message, BUGGY_MESSAGE_SIZE);
    BuggyMemory.pLastMessage = &BuggyMemory.LastMessage;    
}

void InitMessage(BuggyMessage *pMessage, uint8_t command, uint16_t taskId)
{
    memset(pMessage, 0, sizeof(BuggyMessage));
    pMessage->Command = command;
    pMessage->TaskId = taskId;
}

/**
 * Create a version answer message.
 * @param pMessage, pointer to the message that is populated.
 * @param taskId, the task id.
 */
void CreateVersionMessage(BuggyMessage *pMessage, uint16_t taskId)
{
    InitMessage(pMessage, cmdVersion, taskId);
    pMessage->DataSize = 3;
    
    pMessage->Data[0] = 0;//MAJOR;
    pMessage->Data[1] = 1;//MINOR;
    pMessage->Data[2] = 0;//BUILD;
}

void CreateResetDoneMessage(BuggyMessage *pMessage)
{
    pMessage->Command = cmdResetDone;
    pMessage->DataSize = 0;
}

/**
 * Create a sensor result message.
 * @param pMessage, pointer to the message that is populated.
 * @param sensor, the sensor that is requested.
 * @param value, the read-out of the sensor.
 * @param taskId, the task id.
 */
void CreateSensorResultMessage(BuggyMessage *pMessage, AnalogSensor sensor, uint16_t value, uint16_t taskId)
{
    InitMessage(pMessage, cmdSensorResult, taskId);
    pMessage->DataSize = 3;

    pMessage->Data[0] = sensor;
    pMessage->Data[1] = HIGH_BYTE(value);
    pMessage->Data[2] = LOW_BYTE(value);
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
