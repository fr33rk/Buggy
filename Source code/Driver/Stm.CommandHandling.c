#include "Types.h"
#include "Stm.CommandHandling.h"
#include "MessageFIFOBuffer.h"

extern MessageFIFOBuffer UartInMessageBuffer;

// Add global variables here.
typedef enum 
{
    Idle,
    ListeningForCommand,
    HandlingCommand,
    Finalize,
} enmCommandHandlingState;

// Add local variables here.
//static enmCommandHandlingState mCurrentState;
//
//
//// Add function prototypes here.
//void HandleCommand();

/**
* The state machine when the module is handling commands.
* @return True when STM busy, otherwise false.
*/
bool CommandHandlingStm()
{
    
//    switch(mCurrentState)
//    {
//        case Idle:
//            return false;
//        case ListeningForCommand:
//            if (UartInMessageBuffer.HasDataAvailable(&UartInMessageBuffer))
//            {
//                
//            }
//            break;
//        case HandlingCommand:
//            HandleCommand();
//            mCurrentState = ListeningForCommand;
//            break;
//        default:
//            mCurrentState = Idle;
//            return false;
//    }
//    
//    return true;
}

void InitCommandHandlingStm()
{
//    mCurrentState = Idle;
}


bool StartCommandHandlingStm()
{
//    if(mCurrentState == Idle)
//    {
//        mCurrentState = ListeningForCommand;
//        return true;
//    }
//    //Busy
//    return false;
}

void HandleCommand()
{
    
}
