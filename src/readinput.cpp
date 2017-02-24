#include "readinput.h"

ReadInput::ReadInput(QGraphicsScene * scene)
{
    this->scene = scene;
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
    int width_of_tile;
    int height_of_tile;

    infile >> this->screenWidth;
    infile >> this->screenHeight;

    infile >> width_of_tile;
    infile >> height_of_tile;

    infile >> row_tile_matrix_size;
    infile >> column_tile_matrix_size;

    int column_position = 0 , row_position = 0;
    bool is_obstacle = false;

    for(int matrix_row_iterator = 0; matrix_row_iterator < row_tile_matrix_size; matrix_row_iterator++)
    {
        (this->tileMap).push_back(std::vector<Tile*> (column_tile_matrix_size));
        for(int matrix_column_iterator = 0 ; matrix_column_iterator < column_tile_matrix_size ; matrix_column_iterator++)
        {
            infile >> column_position;
            infile >> row_position;
            infile >> is_obstacle;

            (this->tileMap)[matrix_row_iterator][matrix_column_iterator] = new Tile(this->scene , column_position ,  row_position  ,width_of_tile , height_of_tile , is_obstacle);
        //     qDebug()<<matrix_row_iterator<<" , "<<matrix_column_iterator<<left_position<<" , "<<top_position<<" , "<<is_obstacle<<" , "<<((this->tileMap)[matrix_row_iterator][matrix_column_iterator])->getR();
        }
    }
}

GameState* ReadInput::createGameStateObject(std::string tile_map_path , std::string gem_path , std::string player1_file_path , std::string player2_file_path , std::string monster_file_path)
{
    this->functionToCreateTileMap(tile_map_path);

    this->functionToCreateGem(gem_path);

    this->functionToCreatePlayerGameObject(player1_file_path , Qt::Key_Up, Qt::Key_Right ,  Qt::Key_Left);

    this->functionToCreatePlayerGameObject(player2_file_path , Qt::Key_W, Qt::Key_D ,  Qt::Key_A);

    this->functionToCreateMonsterGameObject(monster_file_path);


    return new GameState(this->gameObject , this->tileMap , this->gems , this->screenWidth , this->screenHeight , this->scene );
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
    int width = 0 , height = 0;
    qreal x_coordinate = 0 , y_coordinate = 0;

    while(true)
    {
        infile >> image_file_path;
        infile >> width;
        infile >> height;
        infile >> x_coordinate;
        infile >> y_coordinate;
        if(infile.eof())
        {
            break;
        }
        (this->gems).push_back(new Diamond(image_file_path , width , height , x_coordinate , y_coordinate));
        (this->gems).back()->setQGraphicsScene(this->scene);
        (this->gems).back()->draw();
    }
}

//file path ex : ":resources/images/player1"
void ReadInput::functionToCreatePlayerGameObject(std::string file_path , Qt::Key jump_input, Qt::Key right_input, Qt::Key left_input)
{
    std::string images_location;
    std::vector<int> images_total_count;
    int images_count_temp;
    int image_width , image_height , font_size;
    qreal x_coordinate;
    qreal y_coordinate;

    std::ifstream infile;
    infile.open(file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

        infile >> images_location;
        for(int i = 0; i < 8 ; i++)
        {
            infile >> images_count_temp;
            images_total_count.push_back(images_count_temp);
        }
        infile >> image_width;
        infile >> image_height;
        infile >> x_coordinate;
        infile >> y_coordinate;
        GraphicsComponent* graphics_component = new PlayerGraphicsComponent(this->scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate ,false );
        Keys* key_pointer = new Keys( jump_input, right_input , left_input);
        InputComponent *input_component = new HumanInputComponent(key_pointer);
        PhysicsComponent * physics_component = new PlayerPhysicsComponent(this->tileMap , ((this->tileMap)[0][0])->getHeightOfTile() ,  ((this->tileMap)[0][0])->getWidthOfTile() , this->screenHeight , this->screenWidth , this->scene);
        int max_jump_count;
        infile >> max_jump_count;

        (this->gameObject).push_back(new GameObject(input_component , graphics_component , physics_component , max_jump_count));
}


void ReadInput::functionToCreateMonsterGameObject(std::string file_path)
{
    std::string images_location;
    std::vector<int> images_total_count;
    int images_count_temp;
    int image_width , image_height;
    qreal x_coordinate;
    qreal y_coordinate;
    int walk_frames_count;

    std::ifstream infile;
    infile.open(file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

    infile >> images_location;
    for(int i = 0; i < 8 ; i++)
    {
        infile >> images_count_temp;
        images_total_count.push_back(images_count_temp);
    }
    infile >> image_width;
    infile >> image_height;
        while(true)
        {
            infile >> x_coordinate;
            infile >> y_coordinate;
            infile >> walk_frames_count;
            if(infile.eof())
            {
                break;
            }
            GraphicsComponent* graphics_component = new PlayerGraphicsComponent(this->scene , images_location , images_total_count , image_width , image_height , x_coordinate , y_coordinate , true );
            InputComponent *input_component = new ComputerInputComponent(walk_frames_count);
            PhysicsComponent * physics_component = new MonsterPhysicsComponent(this->tileMap , ((this->tileMap)[0][0])->getHeightOfTile() ,  ((this->tileMap)[0][0])->getWidthOfTile() , this->screenHeight , this->screenWidth);

            (this->gameObject).push_back(new GameObject(input_component , graphics_component , physics_component , 0));
        }

}
