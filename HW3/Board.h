#ifndef __Board_H
#define __Board_H
#include<iostream>
#include<string>
#include<utility>
class Board{
    public:
    //Constructor
    Board();
    Board(std::string asymbol_1, std::string asymbol_2, std::string aempty);
    //Accessor
    int numRows() const{return row;}
    int numColumns() const {return column;}
    int numTokensInColumn(int column_num) const;
    int numTokensInRow(int row_num) const;
    std::string get_empty()const{return empty;}
    //other
    std::string insert(int column_num, bool statement);
    std::string winner_check();
    std::string point_on_grid(int column_num, int row_num)const{return 
    m_data[column_num][row_num];}
    int get_height(int column_num)const{return height[column_num];}
    Board(Board& board){copy(board);}
    Board &operator=(const Board &board);
    //Deconstrctor
    ~Board();
    void clear();

    private:
    std::string symbol_1;
    std::string symbol_2;
    std::string empty;
    std::string **m_data;
    int row=4;
    int column=5;
    int *height;
    void copy(const Board& board); 
};
std::ostream &operator<<(std::ostream& out, const Board& board);
#endif