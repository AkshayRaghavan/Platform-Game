#ifndef STATE_H
#define STATE_H

class GameObject;
class MovingRight;
class MovingLeft;
class Jumping;
class JumpingRight;
class JumpingLeft;
class Stop;
#include <Qt>
#include <set>

class State
{
public:
    int jumpCount;
    State() { jumpCount = 0; }
    virtual ~State() {}
    virtual State* update(GameObject &,std::set<Qt::Key>) = 0;
};

#endif // STATE_H
