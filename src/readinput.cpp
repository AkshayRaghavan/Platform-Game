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


void ReadInput::functionToCreateGem(std::string file_path , int no_of_diamonds)
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

    for(int i = 0 ; i < no_of_diamonds ; i++)
    {
        infile >> image_file_path;
        infile >> width;
        infile >> height;
        infile >> x_coordinate;
        infile >> y_coordinate;

        (this->gems).push_back(new Diamond(image_file_path , width , height , x_coordinate , y_coordinate));
        (this->scene)->addItem((this->gems)[i]);
        }
}
