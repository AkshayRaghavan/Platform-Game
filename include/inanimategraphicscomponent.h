#ifndef INANIMATEGRAPHICSCOMPONENT_H
#define INANIMATEGRAPHICSCOMPONENT_H

#include "graphicscomponent.h"

class InanimateGraphicsComponent : public GraphicsComponent
{
public:
    InanimateGraphicsComponent(QGraphicsScene* scene ,  std::string images_location , std::vector<int> &images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate , int font_size , int score_display_diff_x , int score_display_diff_y , bool is_monster);
    virtual void update(GameObject &);
    virtual bool getIsMonster();
};

#endif // INANIMATEGRAPHICSCOMPONENT_H
