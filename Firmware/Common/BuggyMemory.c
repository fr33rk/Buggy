#include "BuggyMemory.h"

/**
 * Inform main loop that the buggy should be put in error mode.
 * @param errorCode, the reason why the buggy should be put in error mode.
 */
void InError(ErrorCode errorCode)
{
    BuggyMemory.IsInError = true;
    BuggyMemory.ErrorCode = errorCode;
}