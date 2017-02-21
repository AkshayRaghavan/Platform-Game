#ifndef KEYS_H
#define KEYS_H

#include <Qt>
#include <set>

class Keys
{
public:
    Qt::Key jump,right,left;
    Keys(std::set<Qt::Key>);
};

#endif // KEYS_H
