#include "include/jumpingstate.h"

JumpingState::JumpingState(const int &max_jump_count) : maxJumpCount(max_jump_count)
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


