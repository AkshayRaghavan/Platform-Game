#ifndef STOPRIGHT_H
#define STOPRIGHT_H

#include "state.h"
class GameObject;
#include <Qt>
#include <set>

class StopRight : public State
{
public:
    virtual ~StopRight() {}
    virtual State* update(GameObject &,std::set<Qt::Key>);
};

#endif // STOPRIGHT_H
