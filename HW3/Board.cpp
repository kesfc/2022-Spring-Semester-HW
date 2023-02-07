#include "Board.h"
#include<string>
#include<iostream>

// Default Constructor
Board::Board(){
    symbol_1="";
    symbol_2="";
    empty="";
    m_data=new std::string *[column];
    for(int i=0; i<column; i++){
        m_data[i]=nullptr;
    }
    height=new int[column];
    for(int i=0; i<column; i++){
        height[i]=0;
    }
}

//Constructor
Board::Board(std::string asymbol_1, std::string asymbol_2, std::string aempty){
    row=5;
    column=4;
    symbol_1=asymbol_1;
    symbol_2=asymbol_2;
    empty=aempty;
    //assign the array of pointer as size 4
    m_data=new std::string *[column];
    //Assign pinter in array of point point at a nullptr at first
    for(int i=0; i<column; i++){
        m_data[i]=nullptr;
    }
    /*height is pointer an array on the heap and it will use to track height of 
    each column*/
    height=new int[column];
    for(int i=0; i<column; i++){
        height[i]=0;
    }
};

//return how many Token in column
int Board::numTokensInColumn (int column_num)const{
    if (column_num+1>column){
        return -1;
    }
    return height[column_num];
}

//return how many tokens in row
int Board::numTokensInRow(int row_num) const{
    if (row_num+1>row){
        return -1;
    }
    int out=0;
    for(int i=0; i<column; i++){
        int size=height[i];
        if(size>row_num){
                out++;
        }
    }
    return out;
}

/* This member function will ask for a column index and a true or false statement, in 
this function it may resize the array of pointer of array, and it will add a token on 
the column index being giving.
*/
std::string Board::insert(int column_num, bool statement){
    /*if the column giving is greater than the column have right now, it will creat a new
    array of pointer of array that size is equal to the column number giving +1(bebuase 
    giving is a index +1 get the size) and copy every thing in the old array.
    */
    if (column_num>column-1){
        std::string **new_data=new std::string *[column_num+1];
        for(int i=0; i< column_num+1; i++){
            new_data[i]=nullptr;
        }
        int *new_height=new int[column_num+1];
        for(int i=0; i<column_num+1; i++){
            new_height[i]=0;
        }
        for(int i=0; i<column; i++){
            if (height[i]>0){
                int size=height[i];
                new_data[i]=new std::string[size];
                for(int n=0; n<height[i]; n++){
                    new_data[i][n]=m_data[i][n];
                }
            }
            new_height[i]=height[i];
            delete []m_data[i];
        }
        delete []m_data;
        delete []height;
        column=column_num+1;
        m_data=new_data;
        height=new_height;
    }
    /*the size of the coluumn index being giving will +1, and it will creat an new array
    that is 1 size bigger than the origin one on the heap, and it will copy every token in
    old array and make judegment which symbol will be placing on the last symbol.
    */
    height[column_num]+=1;
    int size=height[column_num];

    if(size>row){
        row=size;
    }
    std::string*new_vec=new std::string[size];
    if (size>1){
        for(int i=0; i<size-1; i++){
            new_vec[i]=m_data[column_num][i];
        }
    }
    if(statement){
        new_vec[size-1]=symbol_1;
    }
    else{
        new_vec[size-1]=symbol_2;
    }
    delete []m_data[column_num];
    m_data[column_num]=new_vec;
    /*last step in the function it will check if there 4 same token together, if there
    is return the winner's token, else return "-----", at here it will call the checking
    function
    */
    std::string out=winner_check();
    return out;
}

/*\This function will check if there are same 4 tokens connect together, if there is
it will return the token, else it will return "-----", this is use to check if there is 
winner already.
    */
std::string Board::winner_check(){
    int count=0;
    std::string winner="";
    for(int i=0; i<column; i++){
        int length=height[i];
        if (length>3){
            for(int n=0; n<length; n++){
                if(m_data[i][n]!=winner){
                    winner=m_data[i][n];
                    count=0;
                }
                else{
                    count++;
                }
                if (count==3){
                    return winner;
                }
            }
        }

    }
    for(int n=0; n<row; n++){
        for(int i=0; i<column; i++){
            if(n<height[i]){
                if(m_data[i][n]!=winner){
                    count=0;
                    winner=m_data[i][n];
                }
                else{
                    count++;
                    if(count==3){
                        return winner;
                    }
                }
            }
            else{
                winner="";
                count=0;
            }
        }
    }
    return "-----";
}

//use to copy
void Board::copy(const Board& board){
    this->symbol_1=board.symbol_1;
    this->symbol_2=board.symbol_2;
    this->empty=board.empty;
    this->row=board.row;
    this->column=board.column;
    this->height=new int [board.column];
    this->m_data=new std::string *[board.column];
    for(int i=0; i<this->column; i++){
        this->height[i]=board.height[i];
    }
    for(int i=0; i<this->column; i++){
        this->m_data[i]=new std::string[this->height[i]];
        for(int n=0; n<board.height[i]; n++){
            this->m_data[i][n]=board.m_data[i][n];
        }
    }
}

//This function is using to cout the board.
std::ostream &operator<<(std::ostream& out, const Board& board){
    for(int n=(board.numRows())-1; n>-1; n--){
        for(int i=0; i<(board.numColumns()-1); i++){
            if(n<board.get_height(i)){
                out<<board.point_on_grid(i,n)<<" ";
            }
            else{
                out<<board.get_empty()<<" ";
            }
        }
        if(n<board.get_height(board.numColumns()-1)){
            int colnum_num=board.numColumns()-1;

            out<<board.point_on_grid(colnum_num, n)<<std::endl;
        }
        else{
            out<<board.get_empty()<<std::endl;
        }
    }
    return out;
}

//clear everything on the board and back to original height.
void Board::clear(){
    for(int i=0; i<column; i++){
        delete []m_data[i];
    }
    delete []m_data;
    row=5;
    column=4;
    m_data=new std::string *[column];
    for(int i=0; i<column; i++){
        m_data[i]=nullptr;
    }
    delete []height;
    height=new int[column];
    for(int i=0; i<column; i++){
        height[i]=0;
    }
}

//assignment
Board &Board::operator=(const Board &board){
    if (this != &board){
        for(int i=0; i<column; i++){
            delete [] m_data[i];
        }
        delete [] m_data;
        delete [] height;
        this -> copy(board);
    }
    return *this;
}

//Deconstructor
Board::~Board(){
    for(int i=0; i<column; i++){
        delete []m_data[i];
    }
    delete []m_data;
    delete []height;
}