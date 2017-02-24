#include "playergraphicscomponent.h"
#include <QPainter>
#include <QPen>

/*
  How to call constructor : (0 ... 7)
    walk right , walk left , idle right , idle left , dead right , dead left , jump right , jump left

    images_location = ":resources/images/player1" or images_location = ":resources/images/monster1"
    images_total_count = [<total count of images in the respective folder array>]
*/

PlayerGraphicsComponent::PlayerGraphicsComponent(QGraphicsScene* scene ,  std::string images_location , std::vector<int> &images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate , bool is_monster):isMonster(is_monster)
{
    for (int i = 0; i < NO_Of_GRAPHICS_STATES; i++ )
    {
        if(images_total_count[i] == 0)
        {
            continue;
        }
        this->qImageMatrix.push_back(new QImage[images_total_count[i]]);
        this->painterMatrix.push_back(new QPainter[images_total_count[i]]);
        this->imagesTotalCount.push_back(images_total_count[i]);
        this->graphicsCounter.push_back(0);
    }

    initializePixMaps(images_total_count[0] , images_location + "/walk right/Walk(" , this->qImageMatrix[0] , this->painterMatrix[0] ,  image_width , image_height);
    initializePixMaps(images_total_count[1] , images_location + "/walk left/Walk(" , this->qImageMatrix[1] , this->painterMatrix[1] ,  image_width , image_height);

    initializePixMaps(images_total_count[2] , images_location + "/idle right/Idle(" , this->qImageMatrix[2] , this->painterMatrix[2] ,  image_width , image_height);
    initializePixMaps(images_total_count[3] , images_location + "/idle left/Idle(" , this->qImageMatrix[3] , this->painterMatrix[3] ,  image_width , image_height);

    initializePixMaps(images_total_count[4] , images_location + "/dead right/Dead(" , this->qImageMatrix[4] , this->painterMatrix[4] ,  image_width , image_height);
    initializePixMaps(images_total_count[5] , images_location + "/dead left/Dead(" , this->qImageMatrix[5] , this->painterMatrix[5] ,  image_width , image_height);

    if(this->isMonster == false)
    {
        initializePixMaps(images_total_count[6] , images_location + "/jump right/Jump(" , this->qImageMatrix[6] , this->painterMatrix[6] ,  image_width , image_height);
        initializePixMaps(images_total_count[7] , images_location + "/jump left/Jump(" , this->qImageMatrix[7] , this->painterMatrix[7] ,  image_width , image_height);
    }

    this->setPixmap(this->painterMatrix[2][0]);
    this->setPos(x_coordinate,y_coordinate);
    scene->addItem(this);
    this->scene = scene;

}

void PlayerGraphicsComponent::initializePainters(int images_total_count , std::string image_location ,  QImage* array_of_image , QPainter* array_of_painter , const int image_width , const int image_height)
{
    for(int i = 0; i < images_total_count; i++)
    {


        array_of_image[i] = new QImage((image_location + std::to_string(i+1) +").png").c_str());
        array_of_painter[i] = new QPainter(&image);
        array_of_painter[i].setPen(QPen(Qt::red));
        array_of_painter[i].setFont(QFont("Times", 100, QFont::Bold));
        array_of_painter[i].drawText(array_of_image[i].rect(), Qt::AlignVCenter, "Text");
        QPixmap r = QPixmap::fromImage(image);
        r = r.scaled(QSize(width_of_tile*8,height_of_tile*8));


        if(!array_of_pixmaps[i].load((image_location + std::to_string(i+1) +").png").c_str()))
        {
            qDebug() << "ERROR(playergraphicscomponent.cpp) : Failed To Load Image" << image_location.c_str() << (i+1) << ").png" <<endl;
            std::exit(EXIT_FAILURE);
        }
        array_of_pixmaps[i] = array_of_pixmaps[i].scaled(QSize(image_width,image_height) , Qt::KeepAspectRatio);  //? ,  Qt::KeepAspectRatio
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

std::vector<qreal> PlayerGraphicsComponent::getSizePositionOfObject()
{
    QRectF obj = this->boundingRect();
    std::vector<qreal> ans(4);
    ans[0] = (this->x());
    ans[1] = (this->y());
    ans[2] = (obj.width());
    ans[3] = (obj.height());
    return ans;
}

void PlayerGraphicsComponent::update(GameObject &obj)
{
    enumerator::JumpingState jumpingEnum = (obj.jumpingState)->type();
    enumerator::State stateEnum = (obj.state)->type();

    int state_index = static_cast<int> (stateEnum);
    int jumping_state_index = static_cast<int> (jumpingEnum);

    if( jumpingEnum == enumerator::JumpingState::IS_NOT_JUMPING)
    {
        if(stateEnum == enumerator::State::MOVING_RIGHT || stateEnum == enumerator::State::MOVING_LEFT || stateEnum == enumerator::State::STOP_RIGHT || stateEnum == enumerator::State::STOP_LEFT)  //for moving , idle position <right , left>
        {
            this->setPixmap(this->pixMapMatrix[state_index][updateGraphicsCounter(state_index)]);
        }
        else if(stateEnum == enumerator::State::DEAD_RIGHT || stateEnum == enumerator::State::DEAD_LEFT )  //if is dead state
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
    else if(jumpingEnum == enumerator::JumpingState::IS_JUMPING)
    {
        if(stateEnum == enumerator::State::MOVING_RIGHT || stateEnum == enumerator::State::STOP_RIGHT )  //jump right
        {
            this->setPixmap(this->pixMapMatrix[6][updateGraphicsCounter(6)]);
        }
        else if(stateEnum == enumerator::State::MOVING_LEFT || stateEnum == enumerator::State::STOP_LEFT )  //jump left
        {
            this->setPixmap(this->pixMapMatrix[7][updateGraphicsCounter(6)]);
        }
        else if( stateEnum == enumerator::State::DEAD_RIGHT || stateEnum == enumerator::State::DEAD_LEFT )  //if dead , so stop jumping and show dead image
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

bool PlayerGraphicsComponent::getIsMonster()
{
    return this->isMonster;
}


