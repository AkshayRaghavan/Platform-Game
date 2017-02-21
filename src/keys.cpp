#include <Qt>

#include "include/keys.h"

Keys::Keys(Qt::Key jump_input, Qt::Key right_input, Qt::Key left_input)
{
    jump = jump_input;
    right = right_input;
    left = left_input;
}
