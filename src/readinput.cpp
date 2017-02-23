#include "readinput.h"

ReadInput::ReadInput(QGraphicsScene * scene)
{
    this->scene = scene;
}

void ReadInput::functionToCreateTileMap(std::string file_path , int size_of_tile , int row_tile_matrix_size , int column_tile_matrix_size)
{
    std::ifstream infile;
    infile.open(file_path , std::ios_base::in);

    if(!infile.is_open())
    {
        qDebug() <<"ERROR(readinput.cpp) Failed to Open "<<file_path.c_str()<<endl;
        std::exit(EXIT_FAILURE);
    }

    int left_position = 0 , top_position = 0;
    bool is_obstacle = false;

    for(int matrix_row_iterator = 0; matrix_row_iterator < row_tile_matrix_size; matrix_row_iterator++)
    {
        (this->tileMap).push_back(std::vector<Tile*> (column_tile_matrix_size));
        for(int matrix_column_iterator = 0 ; matrix_column_iterator < column_tile_matrix_size ; matrix_column_iterator++)
        {
            infile >> left_position;
            infile >> top_position;
            infile >> is_obstacle;
            (this->tileMap)[matrix_row_iterator][matrix_column_iterator] = new Tile(this->scene , left_position , top_position , size_of_tile , size_of_tile , is_obstacle);
            (this->scene)->addItem(((this->tileMap)[matrix_row_iterator][matrix_column_iterator])->getR());
        }
    }
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
        (this->scene)->addItem((this->gems).back());
    }
}


void ReadInput::functionToCreatePlayerGameObject(std::string file_path , Qt::Key jump_input, Qt::Key right_input, Qt::Key left_input)
{
    std::string images_location;
    std::vector<int> images_total_count;
    int images_count_temp;
    int scaling_factor;
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
        infile >> scaling_factor;
        infile >> x_coordinate;
        infile >> y_coordinate;
        GraphicsComponent* graphics_component = new PlayerGraphicsComponent(images_location , images_total_count , scaling_factor , x_coordinate , y_coordinate , false);
        Keys* key_pointer = new Keys( jump_input, right_input , left_input);
        InputComponent *input_component = new HumanInputComponent(key_pointer);

        int max_jump_count;
        infile >> max_jump_count;

        (this->gameObject).push_back(new GameObject(input_component , graphics_component , max_jump_count));
}


void ReadInput::functionToCreateMonsterGameObject(std::string file_path)
{
    std::string images_location;
    std::vector<int> images_total_count;
    int images_count_temp;
    int scaling_factor;
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
    infile >> scaling_factor;

        while(true)
        {
            infile >> x_coordinate;
            infile >> y_coordinate;
            infile>>walk_frames_count;
            GraphicsComponent* graphics_component = new PlayerGraphicsComponent(images_location , images_total_count , scaling_factor , x_coordinate , y_coordinate , true);
            InputComponent *input_component = new ComputerInputComponent(walk_frames_count);

            (this->gameObject).push_back(new GameObject(input_component , graphics_component , 0));
        }

}
