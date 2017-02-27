#include "readinput.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

ReadInput::ReadInput(QGraphicsScene * scene_local)
{
    scene = scene_local;
}

void ReadInput::functionToCreateTileMap(std::string file_path)
{
    std::ifstream infile;
    infile.open(file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }
    int row_tile_matrix_size;
    int column_tile_matrix_size;

    /*infile >> screenWidth;
    infile >> screenHeight;

    infile >> width_of_tile;
    infile >> height_of_tile;*/

    infile >> row_tile_matrix_size;
    infile >> column_tile_matrix_size;

    QRect rec = QApplication::desktop()->availableGeometry();
    screenHeight = rec.height() - QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    screenWidth = screenHeight * 1.5;

    qDebug() << "sw,sh: " << screenWidth << " " << screenHeight;

    width_of_tile = static_cast<qreal>(screenWidth) / (column_tile_matrix_size-1);
    height_of_tile = static_cast<qreal>(screenHeight) / (row_tile_matrix_size-1);

    qDebug() << "w,h : " << width_of_tile << " " << height_of_tile;

    qreal column_position = 0 , row_position = 0;
    bool is_obstacle = false;
    for(int matrix_row_iterator = 0; matrix_row_iterator < row_tile_matrix_size; matrix_row_iterator++)
    {
        tileMap.push_back(std::vector<Tile*> (column_tile_matrix_size));
        for(int matrix_column_iterator = 0 ; matrix_column_iterator < column_tile_matrix_size ; matrix_column_iterator++)
        {
            infile >> column_position;
            infile >> row_position;
            infile >> is_obstacle;

            column_position *= width_of_tile;
            row_position *= height_of_tile;

            tileMap[matrix_row_iterator][matrix_column_iterator] = new Tile(scene , column_position ,  row_position  ,width_of_tile , height_of_tile , is_obstacle);
        }
    }
}

GameState* ReadInput::createGameStateObject(std::string tile_map_path , std::string gem_path , std::string player1_file_path , std::string player2_file_path , std::string monster_file_path , std::string fire_file_path , std::string door_file_path, int milliseconds_per_frame)
{

    /* std::thread t1( [this , tile_map_path] (){functionToCreateTileMap(tile_map_path);});
     t1.join();*/
    functionToCreateTileMap(tile_map_path);

    /* std::thread t2( [this , gem_path] (){functionToCreateGem(gem_path);}    );
     t2.join();
*/
   functionToCreateGem(gem_path);

    functionToCreatePlayerGameObject(player1_file_path , Qt::Key_Up, Qt::Key_Right ,  Qt::Key_Left);

    functionToCreatePlayerGameObject(player2_file_path , Qt::Key_W, Qt::Key_D ,  Qt::Key_A);

    functionToCreateMonsterGameObject(monster_file_path);

    functionToCreateFireObject(fire_file_path);

    functionToCreateDoor(door_file_path);

  /*  std::thread t1( [this , tile_map_path] (){functionToCreateTileMap(tile_map_path);}    );
    std::thread t2( [this , gem_path] (){functionToCreateGem(gem_path);}    );
    std::thread t3( [this , player1_file_path] (){functionToCreatePlayerGameObject(player1_file_path , Qt::Key_Up, Qt::Key_Right ,  Qt::Key_Left);}    );
    std::thread t4( [this , player2_file_path] (){functionToCreatePlayerGameObject(player2_file_path , Qt::Key_W, Qt::Key_D ,  Qt::Key_A);}    );
    std::thread t5( [this , monster_file_path] (){functionToCreateMonsterGameObject(monster_file_path);}    );


/*
    std::thread t2(&ReadInput::functionToCreateGem , gem_path);
    std::thread t3(&ReadInput::functionToCreatePlayerGameObject , player1_file_path , Qt::Key_Up, Qt::Key_Right ,  Qt::Key_Left);
    std::thread t4(&ReadInput::functionToCreatePlayerGameObject , player2_file_path , Qt::Key_W, Qt::Key_D ,  Qt::Key_A);
    std::thread t5(&ReadInput::functionToCreateMonsterGameObject , monster_file_path);
*/

/*    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();*/
    return new GameState(this->gameObject , this->tileMap , this->gems , this->screenWidth , this->screenHeight , this->scene , milliseconds_per_frame, 30000); //hard coded for now
}


void ReadInput::functionToCreateGem(std::string file_path)
{
    std::ifstream infile;
    infile.open(file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

    std::string image_file_path = "";
    qreal width = 0 , height = 0;
    qreal x_coordinate = 0 , y_coordinate = 0;
    std::string temp_string;

    infile >> temp_string >> temp_string >> temp_string;

    while(true)
    {
        infile >> image_file_path;

        infile >> width;
        width *= width_of_tile;

        infile >> height;
        height *= height_of_tile;

        infile >> x_coordinate;
        x_coordinate *= width_of_tile;

        infile >> y_coordinate;
        y_coordinate *= height_of_tile;

        if(infile.eof())
        {
            break;
        }
        gems.push_back(new Diamond(scene , image_file_path , width , height , x_coordinate , y_coordinate));
       gems.back()->draw();
    }
}

//file path ex : ":resources/images/player1"
void ReadInput::functionToCreatePlayerGameObject(std::string file_path , Qt::Key jump_input, Qt::Key right_input, Qt::Key left_input)
{
    std::string images_location;
    std::vector<int> images_total_count;
    int images_count_temp;
    qreal image_width , image_height , font_size;
    int score_display_diff_x , score_display_diff_y;
    int max_jump_count;
    qreal x_coordinate;
    qreal y_coordinate;

    std::string tempString;

    std::ifstream infile;
    infile.open(file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

        infile >> images_location;
        infile >> tempString;

        for(int i = 0; i < 8 ; i++)
        {
            infile >> images_count_temp;
            images_total_count.push_back(images_count_temp);
        }
        infile >> tempString;

        infile >> image_width;
        image_width *= width_of_tile;

        infile >> image_height;
        image_height *= height_of_tile;

        infile >> tempString;

        infile >> x_coordinate;
        x_coordinate *= width_of_tile;

        infile >> y_coordinate;
        y_coordinate *= height_of_tile;

        infile >> tempString;
        infile >> font_size;

        infile >> tempString;
        infile >> score_display_diff_x;
        infile >> score_display_diff_y;

        infile >> tempString;
        infile >> max_jump_count;

        GraphicsComponent* graphics_component = new PlayerGraphicsComponent(scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate , font_size , score_display_diff_x , score_display_diff_y , false );
        Keys* key_pointer = new Keys( jump_input, right_input , left_input);
        InputComponent *input_component = new HumanInputComponent(key_pointer);
        PhysicsComponent * physics_component = new PlayerPhysicsComponent(tileMap , (tileMap)[0][0]->getHeightOfTile() ,  (this->tileMap)[0][0]->getWidthOfTile() , screenHeight , screenWidth , scene);

        gameObject.push_back(new GameObject(input_component , graphics_component , physics_component , max_jump_count));
}


void ReadInput::functionToCreateMonsterGameObject(std::string file_path)
{
    std::string images_location;
    std::vector<int> images_total_count;
    int images_count_temp;
    qreal image_width , image_height;
    qreal x_coordinate;
    qreal y_coordinate;
    int walk_frames_count;
    std::string temp_string;

    std::ifstream infile;
    infile.open(file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

    infile >> images_location;

    infile >> temp_string;

    for(int i = 0; i < 8 ; i++)
    {
        infile >> images_count_temp;
        images_total_count.push_back(images_count_temp);
    }

    infile >> temp_string;

    infile >> image_width;
    image_width *= width_of_tile;

    infile >> image_height;
    image_height *= height_of_tile;

    infile >> temp_string;

        while(true)
        {
            infile >> x_coordinate;
            x_coordinate *= width_of_tile;

            infile >> y_coordinate;
            y_coordinate *= height_of_tile;

            infile >> walk_frames_count;
            if(infile.eof())
            {
                break;
            }
            GraphicsComponent* graphics_component = new PlayerGraphicsComponent(scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate , 0 , 0 , 0 , true );
            InputComponent *input_component = new ComputerInputComponent(walk_frames_count);
            PhysicsComponent * physics_component = new MonsterPhysicsComponent(tileMap , (tileMap)[0][0]->getHeightOfTile() ,  (tileMap)[0][0]->getWidthOfTile() , screenHeight , screenWidth, 3);

            gameObject.push_back(new GameObject(input_component , graphics_component , physics_component , 0));
        }

}


void ReadInput::functionToCreateFireObject(std::string fire_file_path)
{
    std::string images_location;
    int images_total_count;
    qreal image_width , image_height;
    qreal x_coordinate;
    qreal y_coordinate;
    std::string temp_string;

    std::ifstream infile;
    infile.open(fire_file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<fire_file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

    infile >> images_location;

    infile >> temp_string;
    infile >> images_total_count;

    infile >> temp_string;

    infile >> image_width;
    image_width *= width_of_tile;

    infile >> image_height;
    image_height *= height_of_tile;

    infile >> temp_string;

        while(true)
        {
            infile >> x_coordinate;
            x_coordinate *= width_of_tile;

            infile >> y_coordinate;
            y_coordinate *= height_of_tile;

            if(infile.eof())
            {
                break;
            }
            GraphicsComponent* graphics_component = new FireGraphicsComponent(this->scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate);
            InputComponent *input_component = new EmptyInputComponent();
            PhysicsComponent * physics_component = new EmptyPhysicsComponent();
            gameObject.push_back(new GameObject(input_component , graphics_component , physics_component , 0));
        }

}

void ReadInput::functionToCreateDoor(std::string fire_file_path)
{
    std::string images_location;
    qreal x_coordinate;
    qreal y_coordinate;
    qreal width;
    qreal height;
    std::string temp_string;

    std::ifstream infile;
    infile.open(fire_file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<fire_file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

    infile >> x_coordinate;
    x_coordinate *= width_of_tile;

    infile >> y_coordinate;
    y_coordinate *= height_of_tile;

    infile >> width;
    width *= width_of_tile;

    infile >> height;
    height *= height_of_tile;

    Door * door = new Door(x_coordinate,y_coordinate,width,height,scene);

    infile.close();
}

