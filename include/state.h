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
    static MovingRight movingRight;
    static MovingLeft movingLeft;
    static Jumping jumping;
    static JumpingRight jumpingRight;
    static JumpingLeft jumpingLeft;
    static Stop stop;
    State() {}
    virtual ~State() {}
    virtual void update(GameObject &,std::set<Qt::Key>) {}
};

#endif // STATE_H
