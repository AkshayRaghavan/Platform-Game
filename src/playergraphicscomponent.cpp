#include "playergraphicscomponent.h"
#include <QPainter>
#include <QPen>
#include <QImage>
#include <thread>

/*
  How to call constructor : (0 ... 7)
    walk right , walk left , idle right , idle left , dead right , dead left , jump right , jump left

    images_location = ":resources/images/player1" or images_location = ":resources/images/monster1"
    images_total_count = [<total count of images in the respective folder array>]
*/

PlayerGraphicsComponent::PlayerGraphicsComponent(QGraphicsScene* scene , std::string images_location , std::vector<int> &images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate , bool is_dangerous, QApplication * a)
{
    qDebug() << images_location.c_str();
    app = a;
    isDangerous = is_dangerous;
    for (int i = 0; i < NO_Of_GRAPHICS_STATES; i++ )
    {
        if(images_total_count[i] == 0)
        {
            continue;
        }
        pixMapMatrix.push_back(new QPixmap[images_total_count[i]]);
        imagesTotalCount.push_back(images_total_count[i]);
        graphicsCounter.push_back(0);
    }
    std::thread t1([&] () {initializePixMaps (images_total_count[0] , images_location + "/walk right/Walk(" ,  pixMapMatrix[0] ,  image_width , image_height);});
    std::thread t2([&] () {initializePixMaps ( images_total_count[1] , images_location + "/walk left/Walk(" ,  pixMapMatrix[1] ,  image_width , image_height);});
    std::thread t3([&] () {initializePixMaps ( images_total_count[2] , images_location + "/idle right/Idle(" ,  pixMapMatrix[2] ,  image_width , image_height);});
    std::thread t4([&] () {initializePixMaps ( images_total_count[3] , images_location + "/idle left/Idle(" ,  pixMapMatrix[3] ,  image_width , image_height);});
    std::thread t5([&] () {initializePixMaps ( images_total_count[4] , images_location + "/dead right/Dead(" ,  pixMapMatrix[4] ,  image_width , image_height);});
    std::thread t6([&] () {initializePixMaps ( images_total_count[5] , images_location + "/dead left/Dead(" ,  pixMapMatrix[5] ,  image_width , image_height);});

    std::thread t7 , t8;
    if(isDangerous == false)
    {
       t7 = std::thread ([&] () {initializePixMaps ( images_total_count[6] , images_location + "/jump right/Jump(" ,  pixMapMatrix[6] ,  image_width , image_height);});
       t8 = std::thread ([&] () {initializePixMaps ( images_total_count[7] , images_location + "/jump left/Jump(" ,  pixMapMatrix[7] ,  image_width , image_height);});
    }
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    if(isDangerous == false)
    {
        t7.join();
        app->processEvents();
        t8.join();
        app->processEvents();
    }
    this->setPos(x_coordinate,y_coordinate);
    this->setPixmap(pixMapMatrix[2][0]);

    qDebug() << "setting pos to : " << x_coordinate << " " << y_coordinate;
    if(this->parent())
    {
        GameObject *parent = dynamic_cast<GameObject*>(this->parent());
        if(parent)
        {
            parent->setPosXY(QPointF(x_coordinate,y_coordinate));
        }
    }
}


void PlayerGraphicsComponent::initializePixMaps(int images_total_count , std::string image_location ,  QPixmap* array_of_pixmaps , const int image_width , const int image_height)
{
    for(int i = 0; i < images_total_count; i++)
    {
        QImage player_picture((image_location + std::to_string(i+1) +").png").c_str());
           if(player_picture.isNull())
           {
               qDebug() << "ERROR(playergraphicscomponent.cpp) : Failed To Load Image" << image_location.c_str() << (i+1) << ").png" <<endl;
               std::exit(EXIT_FAILURE);
           }
           array_of_pixmaps[i] = QPixmap::fromImage(player_picture);
           array_of_pixmaps[i] = array_of_pixmaps[i].scaled(QSize(image_width,image_height),  Qt::KeepAspectRatio);
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
            graphicsCounter[i]++;
            graphicsCounter[i] %= imagesTotalCount[i];
        }
        else if(i <= 3 || i>=6)  //except dead state all made zero
        {
           graphicsCounter[i] = 0;
        }
        //if it is dead state then at the last iteration bool isDead in GameObject is made true to
        //stop further change of dead player image
        if( (index == 4 || index == 5 ) && (graphicsCounter[i] == imagesTotalCount[i]-1))
        {
          obj->setIsDead(true);
        }
    }
    return graphicsCounter[index];
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
            this->setPixmap(pixMapMatrix[state_index][updateGraphicsCounter(state_index)]);
        }
        else if(stateEnum == enumerator::State::DEAD_RIGHT || stateEnum == enumerator::State::DEAD_LEFT )  //if is dead state
        {
            if(!obj.getIsDead())  //if isDead == false , dead player image slideshow not fully shown , hence show next image
            {
                this->setPixmap(pixMapMatrix[state_index][updateGraphicsCounter(state_index , &obj)]);
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
            this->setPixmap(pixMapMatrix[6][updateGraphicsCounter(6)]);
        }
        else if(stateEnum == enumerator::State::MOVING_LEFT || stateEnum == enumerator::State::STOP_LEFT )  //jump left
        {
            this->setPixmap(pixMapMatrix[7][updateGraphicsCounter(7)]);
        }
        else if( stateEnum == enumerator::State::DEAD_RIGHT || stateEnum == enumerator::State::DEAD_LEFT )  //if dead , so stop jumping and show dead image
        {
            if(!obj.getIsDead())
            {
                this->setPixmap(pixMapMatrix[state_index][updateGraphicsCounter(state_index , &obj)]);
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

void PlayerGraphicsComponent::setApp(QApplication * a)
{
    app = a;
}
