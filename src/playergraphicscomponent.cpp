#include "playergraphicscomponent.h"

/*
  How to call constructor : (0 ... 7)
    walk right , walk left , idle right , idle left , dead right , dead left , jump right , jump left

    images_location = ":resources/images/player1" or images_location = ":resources/images/monster1"
    images_total_count = [<total count of images in the respective folder array>]
*/

PlayerGraphicsComponent::PlayerGraphicsComponent(int images_total_count[] , std::string images_location)
{
    for (int i = 0; i <= 7; i++ )
    {
        this->pixMapMatrix[i] = new QPixmap[images_total_count[i]];
        this->imagesTotalCount[i] = images_total_count[i];
        this->graphicsCounter[i] = 0;
    }

    const int scaling_factor = 200;

    initializePixMaps(images_total_count[0] , images_location + "/walk right/Walk (" , this->pixMapMatrix[0] ,  scaling_factor);
    initializePixMaps(images_total_count[1] , images_location + "/walk left/Walk (" , this->pixMapMatrix[1] ,  scaling_factor);

    initializePixMaps(images_total_count[2] , images_location + "/idle right/Idle (" , this->pixMapMatrix[2] ,  scaling_factor);
    initializePixMaps(images_total_count[3] , images_location + "/idle left/Idle (" , this->pixMapMatrix[3] ,  scaling_factor);

    initializePixMaps(images_total_count[4] , images_location + "/dead right/Dead (" , this->pixMapMatrix[4] ,  scaling_factor);
    initializePixMaps(images_total_count[5] , images_location + "/dead left/Dead (" , this->pixMapMatrix[5] ,  scaling_factor);

    initializePixMaps(images_total_count[6] , images_location + "/jump right/Jump (" , this->pixMapMatrix[6] ,  scaling_factor);
    initializePixMaps(images_total_count[7] , images_location + "/jump left/Jump (" , this->pixMapMatrix[7] ,  scaling_factor);

    this->setPixmap(this->pixMapMatrix[2][0]);
}

void PlayerGraphicsComponent::initializePixMaps(int images_total_count , std::string image_location , QPixmap* array_of_pixmaps , const int scaling_factor)
{
    for(int i = 0; i < images_total_count; i++)
    {
        if(!array_of_pixmaps[i].load((image_location + std::to_string(i+1) +").png").c_str()))
        {
            qDebug() << "ERROR(playergraphicscomponent.cpp) : Failed To Load Image" << image_location.c_str() << (i+1) << ").png" <<endl;
            std::exit(EXIT_FAILURE);
        }
        array_of_pixmaps[i] = array_of_pixmaps[i].scaled(QSize(scaling_factor,scaling_factor),  Qt::KeepAspectRatio);
    }
}

int PlayerGraphicsComponent::updateGraphicsCounter(int index , GameObject * obj)
{
    for(int i = 0; i < NO_Of_GRAPHICS_STATES ; i++)
    {
        //1 state will be incremented , other states will be initialized to 0 for them to start again
        //except the dead left , dead right
        if(i == index)
        {
            this->graphicsCounter[i]++;
            this->graphicsCounter[i] %= this->imagesTotalCount[i];
        }
        else if(i <= 3 || i>=6)  //except dead state all made zero
        {
           this->graphicsCounter[i] = 0;
        }
        //if it is dead state then at the last iteration bool isDead in GameObject is made true to
        //stop further change of dead player image
        if( (index == 4 || index == 5 ) && (this->graphicsCounter[i] == (this->imagesTotalCount[i]-1)))
        {
          obj->setIsDead(true);
        }
    }
    return this->graphicsCounter[index];
}

void PlayerGraphicsComponent::update(GameObject &obj)
{
    int state_index = static_cast<int> ((obj.state)->type());
    int jumping_state_index = static_cast<int> ((obj.jumpingState)->type());

    if(jumping_state_index == 0)
    {
        if(state_index >= 0 && state_index <= 3)  //for moving , idle position <right , left>
        {
            this->setPixmap(this->pixMapMatrix[state_index][updateGraphicsCounter(state_index)]);
        }
        else if(state_index == 4 || state_index == 5)  //if is dead state
        {
            if(!obj.getIsDead())  //if isDead == false , dead player image slideshow not fully shown , hence show next image
            {
                this->setPixmap(this->pixMapMatrix[state_index][updateGraphicsCounter(state_index , &obj)]);
            }
        }
        else
        {
            qDebug() << "ERROR(playergraphicscomponent.cpp) : Invalid State in is_not_jumping case : " <<  state_index <<endl;
            std::exit(EXIT_FAILURE);
        }
    }
    else if(jumping_state_index == 1)
    {
        if(state_index == 0 || state_index == 2)  //jump right
        {
            this->setPixmap(this->pixMapMatrix[6][updateGraphicsCounter(6)]);
        }
        else if(state_index == 1 || state_index == 3)  //jump left
        {
            this->setPixmap(this->pixMapMatrix[7][updateGraphicsCounter(6)]);
        }
        else if(state_index == 4 || state_index == 5)  //if dead , so stop jumping and show dead image
        {
            if(!obj.getIsDead())
            {
                this->setPixmap(this->pixMapMatrix[state_index][updateGraphicsCounter(state_index , &obj)]);
            }
        }
        else
        {
            qDebug() << "ERROR(playergraphicscomponent.cpp) : Invalid State in is_jumping case : " <<  state_index <<endl;
            std::exit(EXIT_FAILURE);
        }
    }
    else
    {
        qDebug() << "ERROR(playergraphicscomponent.cpp) : Invalid JumpingState" <<  jumping_state_index <<endl;
        std::exit(EXIT_FAILURE);
    }
}
















