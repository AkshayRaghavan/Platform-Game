#ifndef STOPRIGHT_H
#define STOPRIGHT_H

#include "state.h"
class GameObject;

class StopRight : public State
{
public:
    virtual ~StopRight() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
    virtual enumerator::State type();
};

#endif // STOPRIGHT_H
