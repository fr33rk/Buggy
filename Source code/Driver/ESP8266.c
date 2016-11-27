#include "ESP8266.h"
#include <string.h>
#include <stdlib.h>
#include "Uart.h"
#include "LEDs.h"
#include "Counters.h"

// Add global variables here.
extern MessageFIFOBuffer UartInMessageBuffer;

// Add local variables here.
typedef enum INITIALIZE_ESP_STATE
{
    Idle,
    Start,
    WaitOnStartUpDelayDone,
    CheckingIfOperational,
    WaitOnCheckingIfOperational,
    GettingIp,
    WaitOnGettingIp,
    WaitOnReceivedAllIpData,
    EnablingMultipleConnections,
    WaitOnEnablingMultipleConnections,
    EnablingServer,
    WaitOnEnablingServer,
    Finalize
} enmInitializeEspState;

enmInitializeEspState mEspInitializationState;

static MessageFIFOElement mReceivedData;
static MessageFIFOElement *mpReceivedData;
static uint8_t mIpAddress;

// Add function prototypes here.
void SaveIpAddress(char * ipAddress);

/**
* The state machine when the module is in measure mode.
* @return True when STM busy, otherwise false.
*/
bool InitializeEspStateMachine()
{
#ifdef SIMULATED
    MessageFIFOElement element;
#endif    
    
    TrySend();
    
    if (UartInMessageBuffer.HasDataAvailable(&UartInMessageBuffer))
    {
        mReceivedData = UartInMessageBuffer.GetNext(&UartInMessageBuffer);
        mpReceivedData = &mReceivedData;
    }
    
    switch (mEspInitializationState)
    {
        case Idle:
            return false;
        case Start:
            // Start timer.
            mEspInitializationState = WaitOnStartUpDelayDone;
#ifdef SIMULATED
            SetTimer(0, 1);
#else
            SetTimer(0, 5000);
#endif            
            return true;
        case WaitOnStartUpDelayDone:
            if (IsTimerExpired(0))
            {
                ResetTimer(0);
                EnableUart();
                mEspInitializationState = CheckingIfOperational;
            }
            return true;
        case CheckingIfOperational:
            UartSendString("AT");
            mEspInitializationState = WaitOnCheckingIfOperational;
            SetLedState(2, ContinuesOn);
            
#ifdef SIMULATED
            strcpy(element.data, "OK");
            UartInMessageBuffer.Add(&UartInMessageBuffer, &element);            
#endif            
                        
            return true;
        case WaitOnCheckingIfOperational:
            if ((mpReceivedData != NULL) && (strncmp(mpReceivedData->data, "OK", 2) == 0))
            {               
                mpReceivedData = NULL;
                mEspInitializationState = GettingIp;                
            }
            return true;
        case GettingIp:
            UartSendString("AT+CIFSR");
            SetLedState(3, ContinuesOn);
            mEspInitializationState = WaitOnGettingIp;
            
#ifdef SIMULATED
            strcpy(element.data, "+CIFSR:STAIP,\"192.168.5.19\"");
            UartInMessageBuffer.Add(&UartInMessageBuffer, &element);            
            strcpy(element.data, "OK");
            UartInMessageBuffer.Add(&UartInMessageBuffer, &element);            
#endif                  
            
            return true;
        case WaitOnGettingIp:
            if ((mpReceivedData != NULL) && (strncmp(mpReceivedData->data, "+CIFSR:STAIP", 12) == 0))
            {               
                SaveIpAddress(mpReceivedData->data);
                mpReceivedData = NULL;
                mEspInitializationState = WaitOnReceivedAllIpData;                
            }
            return true;
        case WaitOnReceivedAllIpData:
            if ((mpReceivedData != NULL) && (strncmp(mpReceivedData->data, "OK", 2) == 0))
            {               
                mpReceivedData = NULL;
                mEspInitializationState = EnablingMultipleConnections;                
            }
            return true;
        case EnablingMultipleConnections:
            UartSendString("AT+CIPMUX=1");
            SetLedState(4, ContinuesOn);
            mEspInitializationState = WaitOnEnablingMultipleConnections;            
            
#ifdef SIMULATED
            strcpy(element.data, "OK");
            UartInMessageBuffer.Add(&UartInMessageBuffer, &element);            
#endif      
            
            return true;
        case WaitOnEnablingMultipleConnections:
            if ((mpReceivedData != NULL) && (strncmp(mpReceivedData->data, "OK", 2) == 0))
            {               
                mpReceivedData = NULL;
                mEspInitializationState = EnablingServer;                
            }
            return true;            
        case EnablingServer:
            UartSendString("AT+CIPSERVER=1,6090");
            SetLedState(5, ContinuesOn);
            mEspInitializationState = WaitOnEnablingServer; 
            
#ifdef SIMULATED
            strcpy(element.data, "OK");
            UartInMessageBuffer.Add(&UartInMessageBuffer, &element);            
#endif              
            
            return true;
        case WaitOnEnablingServer:
            if ((mpReceivedData != NULL) && (strncmp(mpReceivedData->data, "OK", 2) == 0))
            {               
                mpReceivedData = NULL;
                mEspInitializationState = Finalize;                
            }
            return true;
        
        case Finalize:   
            SetLedState(2, ContinuesOff);
            SetLedState(3, ContinuesOff);
            SetLedState(4, ContinuesOff);
            SetLedState(5, ContinuesOff);            
            mEspInitializationState = Idle;
            return false;
        default:
            return false;    
    }
}

void InitInitializeEspStateMachine()
{
    mpReceivedData = NULL;
    mEspInitializationState = Idle;
    mIpAddress = 0;
}
//
bool StartInitializeEspStateMachine()
{
    if(mEspInitializationState == Idle)
    {
        mEspInitializationState = Start;
        return true;
    }
    //Busy
    return false;
}

void SaveIpAddress(char * ipAddress)
{
    bool done = false;
    uint8_t dotCount = 0;
    char rawAddress[3];
    char current;
    uint8_t rawAddressIndex = 0;
    
    memset(rawAddress, 0, 3);
    
    for (int i = 12; !done && (i < MAX_MESSAGE_SIZE); i++)
    {
        current = ipAddress[i];
        
        if (current == '.')
        {
            dotCount++;
        }
        else if (dotCount == 3)
        {
            if (current == '"')
            {
                mIpAddress = atoi(rawAddress);
                done = true;
            }
            else
            {
                rawAddress[rawAddressIndex++] = current;
            }
        }
                
    }
}