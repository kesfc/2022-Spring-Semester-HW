#ifndef BOARD_H__
#define BOARD_H__
#include <vector>
class Board{
    public:
    //constructor
    Board(): row(-1), column(-1){}
    Board(int arow, int acolumn);
    //accessor
    int get_row()const{return row;}
    int get_column()const{return column;}
    char get_point(int arow, int acolumn)const{return grid[arow][acolumn];}
    int number_in_row(int arow)const{return every_row[arow];}
    int number_in_column(int acolumn)const{return every_column[acolumn];}
    std::vector<std::vector<int>> get_tokens()const{return all_token;}
    int get_number_tokens()const{return all_token.size();}
    //editor
    void add_point(int arow, int acolumn, char token){grid[arow][acolumn]=token;}
    void add_token(int arow, int acolumn);
    //copy
    void copy(const Board& old);
    private:
    //// REPRESENTATIONi
    int row;
    int column;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<int>> all_token;
    std::vector<int> every_row;
    std::vector<int> every_column;
};
std::ostream &operator<<(std::ostream& out, const Board& board);
#endif