#include <string.h>

#include "Types.h"
#include "Counters.h"
#include "ESP8266.h"
#include "Uart.h"
#include "DigitalSensors.h"
#include "LEDs.h"

#include "MessageFIFOBuffer.h"

// Add global variables here.
extern bool Button1Clicked;
extern MessageFIFOBuffer UartInMessageBuffer;

// Add local variables here.
typedef enum _OPERATIONAL_STATE
{
    Idle,
    Start,
    SendingMessage,
    Finalize,
} enmOperationalState;

static enmOperationalState mCurrentState;

// Add function prototypes here.


/**
* The state machine when the module is in measure mode.
* @return True when STM busy, otherwise false.
*/
bool OperationalStateMachine(void)
{
    static bool isShowingIp = false;
    
    if (Button1Clicked)
    {
        Button1Clicked = false;
        isShowingIp ? ClearByteValueInLed() : SetByteValueInLed(GetIpAddress());
        isShowingIp = !isShowingIp;
    }
    
    MessageFIFOElement element;
    
    switch(mCurrentState)
    {
        case Idle:
            return false;
        case Start:
            
//            memcpy(element.data, "0,CONNECT", 9);
//            UartInMessageBuffer.Add(&UartInMessageBuffer, &element);
#ifdef SIMULATED
            SetTimer(0, 1);
#else
            SetTimer(0, 5000);            
#endif            
            mCurrentState = SendingMessage;
            return true;
        case SendingMessage:
            if (IsTimerExpired(0))
            {                
                SendMessage("Hello world");
                //uint8_t testBuffer[4] = { 21, 9, 19, 78 };
                //UartSendBytes(testBuffer, 4);
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
        mCurrentState = Start;
        return true;
    }
    //Busy
    return false;
}

