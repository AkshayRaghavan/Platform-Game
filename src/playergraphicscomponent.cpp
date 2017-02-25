#include "playergraphicscomponent.h"
#include <QPainter>
#include <QPen>

/*
  How to call constructor : (0 ... 7)
    walk right , walk left , idle right , idle left , dead right , dead left , jump right , jump left

    images_location = ":resources/images/player1" or images_location = ":resources/images/monster1"
    images_total_count = [<total count of images in the respective folder array>]
*/

PlayerGraphicsComponent::PlayerGraphicsComponent(QGraphicsScene* scene_formal_arg ,  std::string images_location , std::vector<int> &images_total_count, int image_width , int image_height , qreal x_coordinate , qreal y_coordinate , int font_size , int score_display_diff_x , int score_display_diff_y , bool is_dangerous):
    scoreDisplayDiffX(score_display_diff_x) , scoreDisplayDiffY(score_display_diff_y)
{
    isDangerous = is_dangerous;
    scene = scene_formal_arg;
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

    initializePixMaps(images_total_count[0] , images_location + "/walk right/Walk(" ,  pixMapMatrix[0] ,  image_width , image_height);
    initializePixMaps(images_total_count[1] , images_location + "/walk left/Walk(" ,  pixMapMatrix[1] , image_width , image_height);

    initializePixMaps(images_total_count[2] , images_location + "/idle right/Idle(" ,  pixMapMatrix[2] ,  image_width , image_height);
    initializePixMaps(images_total_count[3] , images_location + "/idle left/Idle(" ,  pixMapMatrix[3] , image_width , image_height);

    initializePixMaps(images_total_count[4] , images_location + "/dead right/Dead(" ,  pixMapMatrix[4] , image_width , image_height);
    initializePixMaps(images_total_count[5] , images_location + "/dead left/Dead(" ,  pixMapMatrix[5] , image_width , image_height);

    if(isDangerous == false)
    {
        initializePixMaps(images_total_count[6] , images_location + "/jump right/Jump(" ,  pixMapMatrix[6] ,  image_width , image_height);
        initializePixMaps(images_total_count[7] , images_location + "/jump left/Jump(" ,   pixMapMatrix[7],  image_width , image_height);
    }

    setPixmap(pixMapMatrix[2][0]);
    setPos(x_coordinate,y_coordinate);
    if(!isDangerous)
    {
        scorePointer = new QGraphicsTextItem();
        scorePointer->setPlainText("0");
        scorePointer->setFont(QFont("Helvetica" , font_size));
        scorePointer->setDefaultTextColor(QColor(51, 51, 255));
        scorePointer->setPos(x_coordinate + score_display_diff_x,y_coordinate + score_display_diff_y);
        scene->addItem(scorePointer);
    }
    scene->addItem(this);
}


void PlayerGraphicsComponent::initializePixMaps(int images_total_count , std::string image_location ,  QPixmap* array_of_pixmaps , const int image_width , const int image_height)
{
    for(int i = 0; i < images_total_count; i++)
    {
        if(!array_of_pixmaps[i].load((image_location + std::to_string(i+1) +").png").c_str()))
        {
            qDebug() << "ERROR(playergraphicscomponent.cpp) : Failed To Load Image" << image_location.c_str() << (i+1) << ").png" <<endl;
            std::exit(EXIT_FAILURE);
        }
        array_of_pixmaps[i] = array_of_pixmaps[i].scaled(QSize(image_width,image_height),  Qt::KeepAspectRatio);
    }
}

void PlayerGraphicsComponent::setPosScorePointer( int going_to_x , int going_to_y )
{
    scorePointer->setPos(going_to_x + scoreDisplayDiffX , going_to_y + scoreDisplayDiffY);
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

    if(!isDangerous)
    {
        scorePointer->setPlainText(std::to_string(obj.getScore()).c_str());
    }

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
