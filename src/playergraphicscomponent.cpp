#include "include/playergraphicscomponent.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(int images_max_count[] , std::string images_location[])
{
    this->pixMapMatrix[GRAPHICS_DEAD_LEFT] = new QPixmap[images_max_count[GRAPHICS_DEAD_LEFT]];
    this->imagesMaxCount[GRAPHICS_DEAD_LEFT] = images_max_count[GRAPHICS_DEAD_LEFT];
    this->graphicsCounter[GRAPHICS_DEAD_LEFT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_DEAD_LEFT] , ":resources/images/dead left/Dead (" , this->pixMapMatrix[GRAPHICS_DEAD_LEFT] ,  200);

    this->pixMapMatrix[GRAPHICS_DEAD_RIGHT] = new QPixmap[images_max_count[GRAPHICS_DEAD_RIGHT]];
    this->imagesMaxCount[GRAPHICS_DEAD_RIGHT] = images_max_count[GRAPHICS_DEAD_RIGHT];
    this->graphicsCounter[GRAPHICS_DEAD_RIGHT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_DEAD_RIGHT] , ":resources/images/dead right/Dead (" , this->pixMapMatrix[GRAPHICS_DEAD_RIGHT] ,  200);

    this->pixMapMatrix[GRAPHICS_IDLE_LEFT] = new QPixmap[images_max_count[GRAPHICS_IDLE_LEFT]];
    this->imagesMaxCount[GRAPHICS_IDLE_LEFT] = images_max_count[GRAPHICS_IDLE_LEFT];
    this->graphicsCounter[GRAPHICS_IDLE_LEFT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_IDLE_LEFT] , ":resources/images/idle left/Idle (" , this->pixMapMatrix[GRAPHICS_IDLE_LEFT] ,  200);

    this->pixMapMatrix[GRAPHICS_IDLE_RIGHT] = new QPixmap[images_max_count[GRAPHICS_IDLE_RIGHT]];
    this->imagesMaxCount[GRAPHICS_IDLE_RIGHT] = images_max_count[GRAPHICS_IDLE_RIGHT];
    this->graphicsCounter[GRAPHICS_IDLE_RIGHT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_IDLE_RIGHT] , ":resources/images/idle right/Idle (" , this->pixMapMatrix[GRAPHICS_IDLE_RIGHT] ,  200);

    this->pixMapMatrix[GRAPHICS_JUMP_LEFT] = new QPixmap[images_max_count[GRAPHICS_JUMP_LEFT]];
    this->imagesMaxCount[GRAPHICS_JUMP_LEFT] = images_max_count[GRAPHICS_JUMP_LEFT];
    this->graphicsCounter[GRAPHICS_JUMP_LEFT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_JUMP_LEFT] , ":resources/images/jump left/Jump (" , this->pixMapMatrix[GRAPHICS_JUMP_LEFT] ,  200);

    this->pixMapMatrix[GRAPHICS_JUMP_RIGHT] = new QPixmap[images_max_count[GRAPHICS_JUMP_RIGHT]];
    this->imagesMaxCount[GRAPHICS_JUMP_RIGHT] = images_max_count[GRAPHICS_JUMP_RIGHT];
    this->graphicsCounter[GRAPHICS_JUMP_RIGHT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_JUMP_RIGHT] , ":resources/images/jump right/Jump (" , this->pixMapMatrix[GRAPHICS_JUMP_RIGHT] ,  200);

    this->pixMapMatrix[GRAPHICS_WALK_LEFT] = new QPixmap[images_max_count[GRAPHICS_WALK_LEFT]];
    this->imagesMaxCount[GRAPHICS_WALK_LEFT] = images_max_count[GRAPHICS_WALK_LEFT];
    this->graphicsCounter[GRAPHICS_WALK_LEFT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_WALK_LEFT] , ":resources/images/walk left/Walk (" , this->pixMapMatrix[GRAPHICS_WALK_LEFT] ,  200);

    this->pixMapMatrix[GRAPHICS_WALK_RIGHT] = new QPixmap[images_max_count[GRAPHICS_WALK_RIGHT]];
    this->imagesMaxCount[GRAPHICS_WALK_RIGHT] = images_max_count[GRAPHICS_WALK_RIGHT];
    this->graphicsCounter[GRAPHICS_WALK_RIGHT] = 0;
    initializePixMaps(images_max_count[GRAPHICS_WALK_RIGHT] , ":resources/images/walk right/Walk (" , this->pixMapMatrix[GRAPHICS_WALK_RIGHT] ,  200);

    this->setPixmap(this->pixMapMatrix[GRAPHICS_IDLE_RIGHT][0]);
}

void PlayerGraphicsComponent::initializePixMaps(int upper_limit , std::string image_location , QPixmap* array_of_pixmaps , int scaling_factor)
{
    for(int i = 0; i < upper_limit ; i++)
    {
        if(!array_of_pixmaps[i].load((image_location+ std::to_string(i+1) +").png").c_str()))
        {
            qDebug() << "Failed To Load Image" << image_location << std::to_string(i+1) +").png"<<endl;
            std::exit(EXIT_FAILURE);
        }
        array_of_pixmaps[i] = array_of_pixmaps[i].scaled(QSize(scaling_factor,scaling_factor),  Qt::KeepAspectRatio);
    }
}

int PlayerGraphicsComponent::updateGraphicsCounter(int index)
{
    for(int i = 0; i < NO_Of_GRAPHICS_STATES ; i++)
    {
        if(i == index)
        {
            this->graphicsCounter[i]++;
            this->graphicsCounter[i] %= this->imagesMaxCount[i];
        }
        else
        {
           this->graphicsCounter[i] = 0;
        }
    }
    return this->graphicsCounter[index];
}

void update(GameObject &obj)
{
    switch((obj.jumpingState)->getState())
    {
        case IS_NOT_JUMPING:
            switch ((obj.state)->getState())
            {
                case DEAD_LEFT:
                    this->setPixmap(this->pixMapMatrix[GRAPHICS_DEAD_LEFT][updateGraphicsCounter(GRAPHICS_DEAD_LEFT)]);
                    break;

                case DEAD_RIGHT:
                    this->setPixmap(this->pixMapMatrix[GRAPHICS_DEAD_RIGHT][updateGraphicsCounter(GRAPHICS_DEAD_RIGHT)]);
                    break;

                case MOVING_LEFT:
                    this->setPixmap(this->pixMapMatrix[GRAPHICS_WALK_LEFT][updateGraphicsCounter(GRAPHICS_WALK_LEFT)]);
                    break;

                case MOVING_RIGHT:
                    this->setPixmap(this->pixMapMatrix[GRAPHICS_WALK_RIGHT][updateGraphicsCounter(GRAPHICS_WALK_RIGHT)]);
                    break;

                case STOP_LEFT:
                    this->setPixmap(this->pixMapMatrix[GRAPHICS_IDLE_LEFT][updateGraphicsCounter(GRAPHICS_IDLE_LEFT)]);
                    break;

                case STOP_RIGHT:
                    this->setPixmap(this->pixMapMatrix[GRAPHICS_IDLE_RIGHT][updateGraphicsCounter(GRAPHICS_IDLE_RIGHT)]);
                    break;

                default:
                    qDebug() << "Invalid State In IS_NOT_JUMPING State" << obj.state->getState() <<endl;
                    std::exit(EXIT_FAILURE);
                    break;
            }
            break;

        case IS_JUMPING:
            switch (obj.state->getState())
            {
            case MOVING_LEFT:
                this->setPixmap(this->pixMapMatrix[GRAPHICS_JUMP_LEFT][updateGraphicsCounter(GRAPHICS_JUMP_LEFT)]);
                break;

            case MOVING_RIGHT:
                this->setPixmap(this->pixMapMatrix[GRAPHICS_JUMP_RIGHT][updateGraphicsCounter(GRAPHICS_JUMP_RIGHT)]);
                break;

            default:
                qDebug() << "Invalid State In IS_JUMPING State" << obj.state->getState() <<endl;
                std::exit(EXIT_FAILURE);
                break;
            }
            break;

        default:
            qDebug() << "Invalid Jumping State" << obj.jumpingState->getState()<<endl;
            std::exit(EXIT_FAILURE);
    }
}
















