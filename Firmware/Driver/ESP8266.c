#include "ESP8266.h"
#include <string.h>
#include <stdlib.h>
#include "Uart.h"
#include "LEDs.h"
#include "Counters.h"
#include "BuggyMemory.h"

#define MAX_CONNECTIONS 5

// Add global variables here.
extern MessageFIFOBuffer UartInMessageBuffer;
OnReceivedData ReceivedDataHandler;

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
    DecideToReset,
    Resetting,
    Finalize
} enmInitializeEspState;

typedef enum OPERATIONAL_ESP_STATE
{
    OperationalIdle,
    Parallel,
    MessageReceived,
    SavingChannel,
    ClearingChannel,
    ReceivingData,
    RequestingSend,
    WaitOnRequestGranted,
    SendingMessage,
    WaitingOnSendDone,
} enmOperationalEspState;

static enmInitializeEspState mEspInitializationState;
static enmOperationalEspState mCurrentOperationalMainState;
static enmOperationalEspState mCurrentOperationalSendState;

static MessageFIFOElement mReceivedData;
static MessageFIFOElement *mpReceivedData;
static uint8_t mIpAddress;
static bool mTriedReset;
static char mOutMessage[MAX_MESSAGE_SIZE];
static char *mpOutMessage = NULL;
static char mRequestToSendMessage[] = "AT+CIPSEND=x,xx";
static uint8_t mConnections;
static uint8_t mConnectionIndex;

const char *cMsgOk = "OK";

// Add function prototypes here.
void SaveIpAddress(char * ipAddress);
bool RequestSend();

void InitOperationalEdpStateMachine();
void StartOperationalEspStateMachine();
void ProcessReceivedMessage(const char *message);
void ProcessIncommingCommand(const char *message);

/**
* The state machine when the module is in measure mode.
* @return True when STM busy, otherwise false.
*/
bool InitializeEspStateMachine()
{
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
            // Clear the transmit buffer.
            EnableUartTx();            
            SendMessage("Dummy");
            
            // Start timer.
            SetTimer(0, 5000);
            
            mEspInitializationState = WaitOnStartUpDelayDone;
            return true;
        case WaitOnStartUpDelayDone:
            if (IsTimerExpired(0))
            {
                ResetTimer(0);
                EnableUartRx();
                mEspInitializationState = CheckingIfOperational;
            }
            return true;
        case CheckingIfOperational:
            UartSendString("AT");
            mEspInitializationState = WaitOnCheckingIfOperational;
            SetLedState(2, ContinuesOn);
            return true;
        case WaitOnCheckingIfOperational:
            if ((mpReceivedData != NULL) && (strncmp(mpReceivedData->data, cMsgOk, 2) == 0))
            {               
                mpReceivedData = NULL;
                mEspInitializationState = GettingIp;                
            }
            return true;
        case GettingIp:
            UartSendString("AT+CIFSR");
            SetLedState(3, ContinuesOn);
            mEspInitializationState = WaitOnGettingIp;
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
            if ((mpReceivedData != NULL) && (strncmp(mpReceivedData->data, cMsgOk, 2) == 0))
            {               
                mpReceivedData = NULL;
                mEspInitializationState = EnablingMultipleConnections;                
            }
            return true;
        case EnablingMultipleConnections:
            UartSendString("AT+CIPMUX=1");
            SetLedState(4, ContinuesOn);
            mEspInitializationState = WaitOnEnablingMultipleConnections;            
            return true;
        case WaitOnEnablingMultipleConnections:
            if (mpReceivedData != NULL)                     
            {               
                if (strncmp(mpReceivedData->data, cMsgOk, 2) == 0)
                {
                    mpReceivedData = NULL;
                    mEspInitializationState = EnablingServer;                
                }
                else if (strncmp(mpReceivedData->data, "ERROR", 5) == 0)
                {
                    mEspInitializationState = DecideToReset;
                } 
            }
            return true;            
        case EnablingServer:
            UartSendString("AT+CIPSERVER=1,6090");
            SetLedState(5, ContinuesOn);
            mEspInitializationState = WaitOnEnablingServer; 
            return true;
        case WaitOnEnablingServer:
            if (mpReceivedData != NULL) 
            {               
                if (strncmp(mpReceivedData->data, cMsgOk, 2) == 0)
                {
                    mEspInitializationState = Finalize;
                }
                else if (strncmp(mpReceivedData->data, "ERROR", 5) == 0)
                {
                    mEspInitializationState = DecideToReset;
                }
                mpReceivedData = NULL;
            }
            return true;
        
        case DecideToReset:
            if (!mTriedReset)
            {
                mEspInitializationState = Resetting;
            }
            else
            {
                mEspInitializationState = Finalize;
            }     
            return true;
        case Resetting:
            mTriedReset = true;
            UartSendString("AT+RST");
            DisableUart();
            SetLedState(2, ContinuesOff);
            SetLedState(3, ContinuesOff);
            SetLedState(4, ContinuesOff);
            SetLedState(5, ContinuesOff);  
            
            mEspInitializationState = Start;
            return true;
            
        case Finalize:   
            SetLedState(2, ContinuesOff);
            SetLedState(3, ContinuesOff);
            SetLedState(4, ContinuesOff);
            SetLedState(5, ContinuesOff);            
            mEspInitializationState = Idle;
            StartOperationalEspStateMachine();
            return false;
        default:
            return false;    
    }
}

/**
 * Initialize the state machine.
 */
void InitInitializeEspStateMachine()
{
    mpReceivedData = NULL;
    mEspInitializationState = Idle;
    mIpAddress = 0;
    mTriedReset = false;

    SetLedState(2, ContinuesOff);
    SetLedState(3, ContinuesOff);
    SetLedState(4, ContinuesOff);
    SetLedState(5, ContinuesOff); 
}

/**
 * Start the state machine.
 * @return true, when the machine was started.
 */
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

void StartOperationalEspStateMachine()
{
    mpOutMessage = NULL;
    mCurrentOperationalMainState = OperationalIdle;
    mCurrentOperationalSendState = OperationalIdle;
}

void SendMessage(const char *message)
{
    strcpy(mOutMessage, message);
    mpOutMessage = mOutMessage;
}

void SendBuffer(const uint8_t *buffer, const uint8_t size)
{
    char hexValue[3] = "\0\0\0";
    
    // Bytes will be send as HEX characters. So 1 byte takes 2 bytes to send.
    if (size < (MAX_MESSAGE_SIZE / 2))
    {
        uint8_t index;
        for (index = 0; index < size; index++)
        {
            itoa(hexValue, buffer[index], 16);
            
            if (hexValue[1] != '\0')
            {
                mOutMessage[index * 2] = hexValue[0];
                mOutMessage[index * 2 + 1] = hexValue[1];
            }
            else
            {
                mOutMessage[index * 2] = '0';
                mOutMessage[index * 2 + 1] = hexValue[0];
            }
        }
        
        mOutMessage[size * 2] = '\r';
        mOutMessage[size * 2 + 1] = '\n';
        mpOutMessage = mOutMessage;
    }
}

bool OperationalEspSendStateMachine(const char *message)
{
    switch(mCurrentOperationalSendState)
    {
        case OperationalIdle:
            if (mpOutMessage != NULL)                
            {
                mCurrentOperationalSendState = RequestingSend;
                mConnectionIndex = 0;
                return true;
            }
            return false;
        case RequestingSend:            
            if (RequestSend())
            {
                mCurrentOperationalSendState = WaitOnRequestGranted;
            }
            else
            {
                mpOutMessage = NULL;
                mCurrentOperationalSendState = OperationalIdle;
            }
            return true;
        case WaitOnRequestGranted:
            
            if ((message != NULL) && (strncmp(message, cMsgOk, 2) == 0))
            {
                mCurrentOperationalSendState = SendingMessage;
            }
            return true;
        case SendingMessage:
            UartSendString(mpOutMessage);
            mCurrentOperationalSendState = WaitingOnSendDone;
            return true;
        case WaitingOnSendDone:
            if ((message != NULL) && (strncmp(message, "SEND OK", 7) == 0))
            {
                mCurrentOperationalSendState = RequestingSend;
            }
            return true;
        default:
            return false;
    }
}

bool OperationalEspStateMachine()
{
    if ((mpReceivedData == NULL) && (UartInMessageBuffer.HasDataAvailable(&UartInMessageBuffer)))
    {
        mReceivedData = UartInMessageBuffer.GetNext(&UartInMessageBuffer);
        mpReceivedData = &mReceivedData;
    }

    switch(mCurrentOperationalMainState)
    {
        case OperationalIdle:
            if ((mpReceivedData != NULL) || (mpOutMessage != NULL))
            {
                mCurrentOperationalMainState = Parallel;
            }
            return true;
        case Parallel:
            if (mpReceivedData != NULL)
            {
                ProcessReceivedMessage(mpReceivedData->data);
            }
            if (!OperationalEspSendStateMachine(mpReceivedData != NULL ? mpReceivedData->data : NULL))
            {
                mCurrentOperationalMainState = OperationalIdle;
            }
            
            mpReceivedData = NULL;
            return true;
        default:
            return false;
    }
}

void ProcessConnectionMessage(const bool connected, const char* message)
{
    char index[2] = "\0\0";
    strncpy(index, message, 1);
  
    if (connected)
        mConnections |= (1 << atoi(index));
    else
        mConnections &= ~(1 << atoi(index));
    
    SetLedState(1, mConnections > 0 ? ContinuesOn : ContinuesOff);
}

void ProcessReceivedMessage(const char *message)
{
    if (strncmp(message + 2, "CONNECT", 7) == 0)
    {
        ProcessConnectionMessage(true, message);
    }
    else if (strncmp(message + 2, "CLOSED", 6) == 0)
    {
        ProcessConnectionMessage(false, message);
    }
    else if (strncmp(message, "+IPD", 4) == 0)
    {
        ProcessIncommingCommand(message);
    } 
}

void ProcessIncommingCommand(const char *message)
{
    if (ReceivedDataHandler)
    {
        uint8_t position = 7;
        uint8_t datasize = 0;
        char digit;
        bool done = false;

        while (!done)
        {
            digit = message[position];
            done = digit == ':';
            if (!done)
            {
                datasize = (datasize * 10) + (digit - '0');
            }
            position++;
        }

        if (datasize % 2 != 0)
        {
            InError(errInvalidMessageSize);
        }
        else if (datasize > 0)
        {
           char hexValue[3] = { 0, 0, 0}; 
           
           uint8_t rawMessage[MAX_MESSAGE_SIZE];
           uint8_t rawMessagePosition = 0;
           memset(rawMessage, 0, MAX_MESSAGE_SIZE);

           // Translate message from ASCII hex to 'real'hex.
           while ((rawMessagePosition * 2) < datasize)
           {
               hexValue[0] = message[position++];
               hexValue[1] = message[position++];
               rawMessage[rawMessagePosition++] = xtoi(hexValue);
           }
           ReceivedDataHandler(rawMessage);
        }
    }
}

bool RequestSend()
{
    for (mConnectionIndex;  mConnectionIndex < MAX_CONNECTIONS; mConnectionIndex++)
    {
        // Check if connected.
        if ((mConnections & (1 << mConnectionIndex)) > 0)
        {
            char conversion[2];
            // Set 'Channel'
            itoa(conversion, mConnectionIndex, 10);
            mRequestToSendMessage[11] = conversion[0]; 
            
            // Set message size.
            itoa(conversion, strlen(mpOutMessage), 10);
            strncpy(mRequestToSendMessage + 13, conversion, 2);
            
            // Send request.
            UartSendString(mRequestToSendMessage);
            
            // For the next loop because the method ends before the 'for' loop
            // can do it.
            mConnectionIndex++;
            return true;
        }
    }
    return false;
}

/**
 * Get the IP address assigned to the module.
 * @return The last part of the IP address.
 */
uint8_t GetIpAddress()
{
    return mIpAddress;
}

bool IsConnected()
{
   return mConnections > 0;   
}