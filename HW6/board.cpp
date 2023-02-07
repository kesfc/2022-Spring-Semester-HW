#include <ostream>
#include "board.h"
Board:: Board(int arow, int acolumn){
    row=arow;
    column=acolumn;
    for(int i=0; i< row; i++){
        std::vector<char> temp;
        every_row.push_back(0);
         for(int k=0; k<column; k++){
             temp.push_back('.');
         }
         grid.push_back(temp);
    }
    for(int i=0; i<column; i++){
        every_column.push_back(0);
    }
};
void Board::add_token(int arow, int acolumn){
    every_row[arow]+=1;
    every_column[acolumn]+=1;
    grid[arow][acolumn]='@';
    std::vector<int> token_position;
    token_position.push_back(acolumn);
    token_position.push_back(arow);
    all_token.push_back(token_position);
}
void Board::copy(const Board& old){
    row=old.row;
    column=old.column;
    grid=old.grid;
    all_token=old.all_token;
    every_row=old.every_row;
    every_column=old.every_column;
}
std::ostream &operator<<(std::ostream& out, const Board& board){

    for(int i=0; i<board.get_row(); i++){
        for(int k=0; k<board.get_column(); k++){
            out<<board.get_point(i,k);
        }
        out<<std::endl;
    }
    return out;
};
