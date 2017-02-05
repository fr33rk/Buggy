#include <string.h>
#include <pic18.h>

#include "Types.h"
#include "Counters.h"
#include "ESP8266.h"
#include "Uart.h"
#include "DigitalSensors.h"
#include "AnalogSensors.h"
#include "LEDs.h"

#include "MessageFIFOBuffer.h"
#include "BuggyMessage.h"
#include "BuggyMemory.h"

// Add global variables here.
extern bool Button1Clicked;
extern MessageFIFOBuffer UartInMessageBuffer;

// Add local variables here.
typedef enum _OPERATIONAL_STATE
{
    Idle,
    WaitingOnConnection,
    ReportingVersion,
    ReportingResetReason,
    Start,
    SendingMessage,
    Finalize,
} enmOperationalState;

static enmOperationalState mCurrentState;

// Add function prototypes here.
void static ProcessCommand();
void ProcessVersionRequest();
void ProcessSensorRequest();

/**
* The state machine when the module is in measure mode.
* @return True when STM busy, otherwise false.
*/
bool OperationalStateMachine(void)
{
    static bool isShowingIp = false;
    BuggyMessage message;
    
    if (Button1Clicked)
    {
        Button1Clicked = false;
        isShowingIp ? ClearByteValueInLed() : SetByteValueInLed(GetIpAddress());
        isShowingIp = !isShowingIp;        
    }
    
    MessageFIFOElement element;
    
    if (BuggyMemory.pLastMessage != NULL)
    {
        ProcessCommand();
    }
    
    switch(mCurrentState)
    {
        case Idle:
            return false;
        case WaitingOnConnection:
            if (IsConnected())
            {
                mCurrentState = ReportingVersion;
            }
            return true;
            
        case ReportingVersion:
            CreateVersionMessage(&message, 0);
            SendBuffer(message.AsBuffer, BUGGY_MESSAGE_SIZE);
            mCurrentState = ReportingResetReason;
            return true;
            
        case ReportingResetReason:
            CreateResetDoneMessage(&message);
            SendBuffer(message.AsBuffer, BUGGY_MESSAGE_SIZE);
            mCurrentState = Start;
            return true;
            
        case Start:
#ifdef SIMULATED
            SetTimer(0, 1);
#else
            SetTimer(0, 200);            
#endif            
            mCurrentState = SendingMessage;
            return true;
        case SendingMessage:
           
            if (IsTimerExpired(0))
            {      
                /*
                BuggyMessage message;
                CreateVersionMessage(&message);
                SendBuffer(message.AsBuffer, 12);
                
                
                uint16_t sensorVal = GetLastReading(DistanceLeft);
                uint8_t testBuffer[8];
                testBuffer[0] = HIGH_BYTE(sensorVal);
                testBuffer[1] = LOW_BYTE(sensorVal);

                sensorVal = GetLastReading(DistanceFront);
                testBuffer[2] = HIGH_BYTE(sensorVal);
                testBuffer[3] = LOW_BYTE(sensorVal);
                
                sensorVal = GetLastReading(DistanceRight);
                testBuffer[4] = HIGH_BYTE(sensorVal);
                testBuffer[5] = LOW_BYTE(sensorVal);
                
                sensorVal = GetLastReading(Light);
                testBuffer[6] = HIGH_BYTE(sensorVal);
                testBuffer[7] = LOW_BYTE(sensorVal);

                SendBuffer(testBuffer, 8);*/

#ifdef SIMULATED                
                strcpy(element.data, "+IPD,0,12:0C0200040100");
                UartInMessageBuffer.Add(&UartInMessageBuffer, &element);
#else
                if (BuggyMemory.SendSensorUpdates)
                {
                    if (BuggyMemory.SensorSelected == AllSensors)
                    {
                        CreateAllSensorResultMessage(&message,
                                BuggyMemory.SendSensorUpdatesTaskId);
                    }
                    else
                    {
                        CreateSensorResultMessage(&message, 
                                BuggyMemory.SensorSelected, 
                                GetLastReading(BuggyMemory.SensorSelected),
                                BuggyMemory.SendSensorUpdatesTaskId);
                    }
                    SendBuffer(message.AsBuffer, BUGGY_MESSAGE_SIZE);                
                }
#endif
                
                ResetTimer(0);
                mCurrentState = Start;
            }
            return true;
        case Finalize:
            mCurrentState = Idle;
            return false;
        default:
            mCurrentState = Idle;
            return false;
    }
}

/**
 * Initialize the operational state machine.
 */
void InitOperationalStateMachine(void)
{
    mCurrentState = Idle;
}

/**
 * Start the operational state machine.
 * @return 
 */
bool StartOperationalStateMachine()
{
    if(mCurrentState == Idle)
    {
        mCurrentState = WaitingOnConnection;
        return true;
    }
    //Busy
    return false;
}

void static ProcessCommand()
{
    switch (BuggyMemory.pLastMessage->Command)
    {
        case cmdVersionReq:
            ProcessVersionRequest();
            break;
        case cmdSensorReq:
            ProcessSensorRequest();
            break;
        case cmdReset:
            Reset();
            break;
    }
    
    BuggyMemory.pLastMessage = NULL;
}

void ProcessVersionRequest()
{
    if ((BuggyMemory.pLastMessage->RTR) 
        && (BuggyMemory.pLastMessage->DataSize == 0))
    {
        BuggyMessage message;
        CreateVersionMessage(&message, BuggyMemory.pLastMessage->TaskId);
        SendBuffer(message.AsBuffer, BUGGY_MESSAGE_SIZE);                
    }
}
void ProcessSensorRequest()
{
    // 0 : Sensor
    // 1 : Continues (true/false)
    
    if ((!BuggyMemory.pLastMessage->RTR) 
        && (BuggyMemory.pLastMessage->DataSize == 2))
    {
        BuggyMemory.SensorSelected = BuggyMemory.pLastMessage->Data[0];
        BuggyMemory.SendSensorUpdates = BuggyMemory.pLastMessage->Data[1];
        
        if (BuggyMemory.SendSensorUpdates)
        {
            BuggyMemory.SendSensorUpdatesTaskId = BuggyMemory.pLastMessage->TaskId;
        }   
        else
        {
            BuggyMessage message;
            if (BuggyMemory.SensorSelected == AllSensors)
            {
                CreateAllSensorResultMessage(&message,
                        BuggyMemory.SendSensorUpdatesTaskId);
            }
            else
            {
                CreateSensorResultMessage(&message, 
                        BuggyMemory.SensorSelected, 
                        GetLastReading(BuggyMemory.SensorSelected),
                        BuggyMemory.SendSensorUpdatesTaskId);
            }
            SendBuffer(message.AsBuffer, BUGGY_MESSAGE_SIZE);
        }
    }    
}
