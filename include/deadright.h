#ifndef DEADRIGHT_H
#define DEADRIGHT_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class DeadRight : public State
{
public:
    virtual ~DeadRight() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
};

#endif // DEADRIGHT_H
