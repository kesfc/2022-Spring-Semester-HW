#include <iostream>
#include <ostream>
#include <fstream>
#include<cassert>
#include<vector>
#include<string>
#include<utility>
#include <algorithm>
#include "board.h"
#include "zone.h"

//this function will take a vector that contains the position, a vector of all token's 
//position and number of token allowed in row and column. and it will return false if 
//there is any token next to the current position
bool any_next(const std::vector<int> &position, const std::vector<std::vector<int>> 
&tokens, int number_token){
  for(int i=0; i<number_token; i++){
    if(abs(tokens[i][0]-position[0])<2 && abs(tokens[i][1]-position[1])<2){
      return true;
    }
  }
  return false;
}

/*This function will take a vector of int that represent the current position, a board, 
and how many star allowed in a row and culomn. This fuction will first checking if the
token in row and clomn is at the limit, if not it will goes to "any_next" function to 
check if there is any token is next to current positon. if it passed both it will return 
true, else return false.
*/
bool able_to_place(const std::vector<int> &position, const Board &board, int stars){
  std::vector<std::vector<int>> tokens = board.get_tokens();
  int size = board.get_number_tokens();
  int current_x=position[0];
  int current_y=position[1];
  if(stars==board.number_in_row(current_y) || stars==board.number_in_column(current_x)){
    return false;
  }
  else if(any_next(position, tokens, size)){
    return false;
  }
  else{
    return true;
  }
}

/* this is my main recursive function, it will take a board, a vector of zone, a int use
to track which zone it is at, a int count how many token in the zone already, a int use 
to track which position it is at in a zone, a int that contains number of stars allowed 
in each row and column and need in a zone, and vector of Board that contains all 
solutions.
*/
void find_solutions(const Board &board, const std::vector<Zone> &all_zones, int zone_num,
int token_in_zone, int zone_index, int stars, std::vector<Board> &solutions){
  int length=all_zones.size();
  if(zone_num==length){
    solutions.push_back(board);
    return;
    //base case:: if the int use to track zone is the same as the the length of the zone
    //vector, it will push_back the board into solutions.
  }
  else if(token_in_zone==stars){
    find_solutions(board, all_zones, zone_num+1, 0, 0, stars, solutions);
    //if the int use to count num of token in zone is equal the token is asking, it will
    //move to the next zone.
  }
  else if(zone_index==all_zones[zone_num].get_number()){
    //if it recursed over a zone, and are not able to fit enough token it means this 
    // is not a possible solution, it will stop.
    return;
  }
  else{
    for(int i=zone_index; i<all_zones[zone_num].get_number()-(stars-token_in_zone)+1;
     i++){
      //loop over rest of positions, and if a position is able to place a token, it will 
      //copy the board and add token in the board in the copied position, and used the 
      //board to go to the function again with token number +1 and int use to track 
      //position in a zone +1;
      if(able_to_place(all_zones[zone_num].get_azone(i), board, stars)){
        int x=all_zones[zone_num].get_azone(i)[0];
        int y=all_zones[zone_num].get_azone(i)[1];
        Board New;
        New.copy(board);
        New.add_token(y,x);
        find_solutions(New, all_zones, zone_num, token_in_zone+1, i+1, stars, 
        solutions);
      }
    }
  }
}

//this function is very similar to the first function, but it will stop when the first 
//answer get out, and instead of taking a vector of board, it will take another board,
//and this board will copy the first solution
void one_solution(const Board &board, const std::vector<Zone> &all_zones, int zone_num,
int token_in_zone, int zone_index, int stars, Board &answer){
  int length=all_zones.size();
  if(zone_num==length){
    answer.copy(board);
    return;
  }
  else if(token_in_zone==stars){
    one_solution(board, all_zones, zone_num+1, 0, 0, stars, answer);
  }
  else if(zone_index==all_zones[zone_num].get_number()){
    return;
  }
  else{
    for(int i=zone_index; i<all_zones[zone_num].get_number()-(stars-token_in_zone)+1;
     i++){
      if(able_to_place(all_zones[zone_num].get_azone(i), board, stars)){
        int x=all_zones[zone_num].get_azone(i)[0];
        int y=all_zones[zone_num].get_azone(i)[1];
        Board New;
        New.copy(board);
        New.add_token(y,x);
        one_solution(New, all_zones, zone_num, token_in_zone+1, i+1, stars, answer);
        if(answer.get_row()!=-1){
          return;
        }
      }
    }
  }
}

int main(int argc, char*argv[]){
    assert(argc==6);
    //stroe all argument.
    std::vector<char> name;
    std::vector<std::vector<int>> area;
    std:: string input_file = argv[1];
    std:: string output_file = argv[2];
    std:: string stars = argv[3];
    int star = stoi(stars);
    std:: string output_mode = argv[4];
    std:: string solution_mode = argv[5];
    std:: ifstream file (input_file);
    if (!file.good()) {
    	std::cerr << "Can't open " << input_file << " to write."<<std::endl;
    exit(1);
  }
  std::vector<Zone> all_zones;
  char letter;
  int row; int column;
  file>>row;
  file>>column;
  Board Grid(row, column);
  while(file>>letter){
    int number;
    file>>number;
    Zone azone(letter, number);
    //parsing the files to the board and zone.
    for(int i=0; i<number; i++){
      int x,y;
      file>>x;
      file>>y;
      std::vector<int> pairs;
      pairs.push_back(x);
      pairs.push_back(y);
      azone.add_position(pairs);
      Grid.add_point(y,x,letter);
    }
    all_zones.push_back(azone);
  }
  file.close();
  //stroe the input_file's information into a board object and zone object.
  std::ofstream fileout(output_file);
	if (!fileout.good()) {
    	std::cerr << "Can't open " << output_file << " to write."<<std::endl;
    	exit(1);
  }
  sort(all_zones.begin(), all_zones.end(), sort_number);//sort the zones by size of zone
  if(solution_mode=="all_solutions"){
    std::vector<Board> solutions;//creat a vector of board use to store all answer.
    find_solutions(Grid, all_zones, 0, 0, 0, star, solutions);
    fileout<<"Number of solutions: "<<solutions.size()<<std::endl;
    if(output_mode=="print"){
      for(long unsigned int i=0; i<(solutions.size()); i++){
        fileout<<"Solution "<<i+1<<":"<<std::endl;
        fileout<<solutions[i]<<std::endl;
      }
    }
  }
  else if(solution_mode=="one_solution"){
    Board answer;
    one_solution(Grid, all_zones, 0, 0, 0, star, answer);
    int num_solution;
    if(answer.get_row()!=-1){//if answer's row is -1 means it didn't get changed, means 
    //there is no solution
      num_solution=1;
    }
    else{
      num_solution=0;
    }
    // write the solutions in the output file.
    fileout<<"Number of solutions: "<<num_solution<<std::endl;
    if(output_mode=="print" && num_solution==1){
      fileout<<"Solution 1:"<<std::endl;
      fileout<<answer<<std::endl;
    }
  }
  fileout.close();
}