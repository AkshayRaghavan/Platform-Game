#ifndef STOPRIGHT_H
#define STOPRIGHT_H

#include "state.h"
class InputComponent;
class GameObject;

class StopRight : public State
{
public:
    virtual ~StopRight() {}
    virtual State* update(InputComponent *,std::set<Qt::Key>);
    virtual enumerator::State type();
};

#endif // STOPRIGHT_H
