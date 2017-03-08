#include "readinput.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

ReadInput::ReadInput(QGraphicsScene * scene_local, int screen_width, int screen_height)
{
    scene = scene_local;
    screenWidth = screen_width;
    screenHeight = screen_height;
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

    infile >> row_tile_matrix_size;
    infile >> column_tile_matrix_size;

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
    qDebug() << "Created Tile Map";
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
    int score_of_gem;
    std::string temp_string;

    infile >> temp_string >> temp_string >> temp_string >> temp_string;

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

        infile >> score_of_gem;

        if(infile.eof())
        {
            break;
        }
        gems.push_back(new Diamond(image_file_path , width , height , x_coordinate , y_coordinate , score_of_gem));
    }
    infile.close();
    qDebug() << "Created Gems";
}

void ReadInput::functionToCreatePlayerGameObject(std::string file_path)
{
    std::string images_location;
    std::vector<int> images_total_count;
    int images_count_temp;
    qreal image_width , image_height , font_size;
    int score_display_diff_x , score_display_diff_y;
    int max_jump_count;
    int RGB1 , RGB2 , RGB3;
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
    infile >> tempString >> image_width >> image_height ;
    image_width *= width_of_tile;
    image_height *= height_of_tile;

    infile >> tempString >> x_coordinate >> y_coordinate;
    x_coordinate *= width_of_tile;
    y_coordinate *= height_of_tile;

    infile >> tempString >> font_size;

    infile >> tempString >> score_display_diff_x >> score_display_diff_y;

    infile >> tempString >> max_jump_count;

    infile >> tempString >> RGB1 >> RGB2 >>RGB3;

    GraphicsComponent* graphics_component = new PlayerGraphicsComponent(scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate , false , app);
    ScoreComponent * score_component = new ScoreComponent(scene , x_coordinate , y_coordinate ,  score_display_diff_x , score_display_diff_y , QColor(RGB1, RGB2, RGB3) , QFont("Helvetica" , font_size));
    InputComponent *input_component = NULL;
    PhysicsComponent * physics_component = NULL;

    if(remoteIdentity == enumerator::Identity::CLIENT)
    {
        input_component = new EmptyInputComponent();
        physics_component = new EmptyPhysicsComponent();
        gameObject.push_back(new GameObject(input_component , graphics_component , physics_component , score_component , 0));
    }
    else if(remoteIdentity == enumerator::Identity::SERVER)
    {
        Keys* key_pointer = new Keys( Qt::Key_Up, Qt::Key_Right ,  Qt::Key_Left );
        input_component = new HumanInputComponent(key_pointer);
        physics_component = new PlayerPhysicsComponent(tileMap , (tileMap)[0][0]->getHeightOfTile() ,  (this->tileMap)[0][0]->getWidthOfTile() , screenHeight , screenWidth , scene);
        gameObject.push_back(new GameObject(input_component , graphics_component , physics_component , score_component , max_jump_count , totalTime));
    }
    infile.close();
    qDebug() << "Created A Player";
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

    infile >> temp_string >> image_width >> image_height;
    image_width *= width_of_tile;
    image_height *= height_of_tile;

    infile >> temp_string;

        while(true)
        {
            infile >> x_coordinate >> y_coordinate >> walk_frames_count;

            x_coordinate *= width_of_tile;
            y_coordinate *= height_of_tile;

            if(infile.eof())
            {
                break;
            }

            GraphicsComponent* graphics_component = new PlayerGraphicsComponent(scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate , true , app);
            InputComponent *input_component = NULL;
            PhysicsComponent * physics_component = NULL;

            if(remoteIdentity == enumerator::Identity::CLIENT)
            {
                input_component = new EmptyInputComponent();
                physics_component = new EmptyPhysicsComponent();
            }
            else if(remoteIdentity == enumerator::Identity::SERVER)
            {
                qDebug() << "READinpt erver";
                input_component = new ComputerInputComponent(walk_frames_count);
                physics_component = new MonsterPhysicsComponent(tileMap , (tileMap)[0][0]->getHeightOfTile() ,  (tileMap)[0][0]->getWidthOfTile() , screenHeight , screenWidth, 3);
            }
            gameObject.push_back(new GameObject(input_component , graphics_component , physics_component , NULL , 0));
        }
    infile.close();
    qDebug() << "Created Monsters";
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

    infile >> temp_string >> images_total_count;

    infile >> temp_string >> image_width >> image_height;
    image_width *= width_of_tile;
    image_height *= height_of_tile;

    infile >> temp_string;

        while(true)
        {

            infile >> x_coordinate >> y_coordinate;

            x_coordinate *= width_of_tile;
            y_coordinate *= height_of_tile;

            if(infile.eof())
            {
                break;
            }
            GraphicsComponent* graphics_component = new FireGraphicsComponent(scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate , app);
            InputComponent *input_component = new EmptyInputComponent();
            PhysicsComponent * physics_component = new EmptyPhysicsComponent();
            gameObject.push_back(new GameObject(input_component , graphics_component , physics_component , NULL , 0));
        }
    infile.close();
    qDebug() << "Created Fire";
}

void ReadInput::functionToCreateDoor(std::string door_file_path)
{
    std::string images_location;
    qreal x_coordinate;
    qreal y_coordinate;
    qreal width;
    qreal height;
    std::string temp_string;

    std::ifstream infile;
    infile.open(door_file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<door_file_path.c_str()<<endl;
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
    app->processEvents();

    infile.close();
    qDebug() << "Created Door";
}

void ReadInput::setApp(QApplication * a)
{
    app = a;
}

