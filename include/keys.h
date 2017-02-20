#ifndef KEYS_H
#define KEYS_H

#include <Qt>

class Keys
{
public:
    Qt::Key jump,right,left;
    Keys(Qt::Key,Qt::Key,Qt::Key);
};

#endif // KEYS_H
