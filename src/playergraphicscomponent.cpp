#include "playergraphicscomponent.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(int images_max_count[] , std::string images_location)
{
    for (int i = enumerator::State::MOVING_RIGHT; i != enumerator::State::DEAD_LEFT; i++ )
    {
        this->pixMapMatrix[i] = new QPixmap[images_max_count[i]];
        this->imagesMaxCount[i] = images_max_count[i];
        this->graphicsCounter[i] = 0;
    }
    for ( int i = 6; i <= 7; i++ )
    {
        this->pixMapMatrix[i] = new QPixmap[images_max_count[i]];
        this->imagesMaxCount[i] = images_max_count[i];
        this->graphicsCounter[i] = 0;
    }

    int index;
    /*
        When It Constructer IS Called images_location = ":resources/images/player1"

        order

        walk right , walk left , idle right , idle left , dead right , dead left , jump right , jump left
    */
    index = static_cast<int> (enumerator::State::MOVING_RIGHT);
    initializePixMaps(images_max_count[index] , images_location + "/walk right/Walk (" , this->pixMapMatrix[index] ,  200);
    index = static_cast<int> (enumerator::State::MOVING_LEFT);
    initializePixMaps(images_max_count[index] , images_location + "/walk left/Walk (" , this->pixMapMatrix[index] ,  200);

    index = static_cast<int> (enumerator::State::STOP_RIGHT);
    initializePixMaps(images_max_count[index] , images_location + "/idle right/Idle (" , this->pixMapMatrix[index] ,  200);
    index = static_cast<int> (enumerator::State::STOP_LEFT);
    initializePixMaps(images_max_count[index] , images_location + "/idle left/Idle (" , this->pixMapMatrix[index] ,  200);

    index = static_cast<int> (enumerator::State::DEAD_RIGHT);
    initializePixMaps(images_max_count[index] , images_location + "/dead right/Dead (" , this->pixMapMatrix[index] ,  200);
    index = static_cast<int> (enumerator::State::DEAD_LEFT);
    initializePixMaps(images_max_count[index] , images_location + "/dead left/Dead (" , this->pixMapMatrix[index] ,  200);

    initializePixMaps(images_max_count[6] , images_location + "/jump right/Jump (" , this->pixMapMatrix[6] ,  200);
    initializePixMaps(images_max_count[7] , images_location + "/jump left/Jump (" , this->pixMapMatrix[6] ,  200);

    this->setPixmap(this->pixMapMatrix[2][0]);
}

void PlayerGraphicsComponent::initializePixMaps(int upper_limit , std::string image_location , QPixmap* array_of_pixmaps , int scaling_factor)
{
    for(int i = 0; i < upper_limit ; i++)
    {
        if(!array_of_pixmaps[i].load((image_location+ std::to_string(i+1) +").png").c_str()))
        {
            qDebug() << "Failed To Load Image" << image_location.c_str() << i << ").png" <<endl;
            std::exit(EXIT_FAILURE);
        }
        array_of_pixmaps[i] = array_of_pixmaps[i].scaled(QSize(scaling_factor,scaling_factor),  Qt::KeepAspectRatio);
    }
}

int PlayerGraphicsComponent::updateGraphicsCounter(int index , GameObject * obj = NULL)
{
    for(int i = 0; i < NO_Of_GRAPHICS_STATES ; i++)
    {
        if(i == index)
        {
            this->graphicsCounter[i]++;
            this->graphicsCounter[i] %= this->imagesMaxCount[i];
        }
        else if(i <= 3)
        {
           this->graphicsCounter[i] = 0;
        }
        if( (index == 4 || index == 5 ) && (this->graphicsCounter[i] == (this->imagesMaxCount[i]-1)))
        {
          obj->setIsDead(true);
        }
    }
    return this->graphicsCounter[index];
}

void update(GameObject &obj)
{
    int state_index = static_cast<int> ((obj.state)->type());
    int jumping_state_index = static_cast<int> ((obj.jumpingState)->type());

    if(jumping_state_enum == 0)
    {
        if(state_index >= 0 && state_index <= 3)
        {
            this->setPixmap(this->pixMapMatrix[state_index][updateGraphicsCounter(state_index)]);
        }
        else if(state_index == 4 || state_index == 5)
        {
            if(!obj.getIsDead())
            {
                this->setPixmap(this->pixMapMatrix[state_index][updateGraphicsCounter(state_index , &obj)]);
            }
        }
        else
        {
            qDebug() << "Invalid State in is_not_jumping case: " <<  state_index <<endl;
            std::exit(EXIT_FAILURE);
        }
    }
    else if(jumping_state_enum == 1)
    {
        if(state_index == 0 || state_index == 2)
        {
            this->setPixmap(this->pixMapMatrix[6][updateGraphicsCounter(6)]);
        }
        else if(state_index == 1 || state_index == 3)
        {
            this->setPixmap(this->pixMapMatrix[7][updateGraphicsCounter(6)]);
        }
        else if(state_index == 4 || state_index == 5)
        {
            if(!obj.getIsDead())
            {
                this->setPixmap(this->pixMapMatrix[state_index][updateGraphicsCounter(state_index , &obj)]);
            }
        }
        else
        {
            qDebug() << "Invalid State in is_jumping case: " <<  state_index <<endl;
            std::exit(EXIT_FAILURE);
        }
    }
    else
    {
        qDebug() << "Invalid JumpingState" <<  jumping_state_index <<endl;
        std::exit(EXIT_FAILURE);
    }
}
















