#include "include/jumpingstate.h"

JumpingState::JumpingState()
{
    jumpCount = 0;
}

int JumpingState::getJumpCount()
{
    return jumpCount;
}

void JumpingState::setJumpCount(int input_jump_count)
{
    jumpCount = input_jump_count;
}

void JumpingState::jumpUpdate()
{
    if(jumpCount > 0)
    {
        jumpCount --;
    }
}


