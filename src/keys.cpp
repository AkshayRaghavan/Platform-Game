#include "keys.h"

Keys::Keys(Qt::Key jump_input, Qt::Key right_input, Qt::Key left_input)
{
    jump = jump_input;
    right = right_input;
    left = left_input;
}

bool Keys::find(Qt::Key find_key)
{
    if(jump == find_key || right == find_key || left == find_key)
    {
        return true;
    }
    return false;
}
