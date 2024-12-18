#include <iostream>
#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}

////////STUDENT CODE//////


//Write your own test cases here
void StudentTest(){
	Board A("CS","DS","--");
	std::cout << "Board is now" << std::endl << A << std::endl;
	A.insert(9,true);
	std::cout << "Board is now" << std::endl << A << std::endl;
	A.insert(1,false);
	A.insert(1,true);
	std::cout << "Board is now" << std::endl << A << std::endl;
	A.insert(2,false);
	A.insert(3,true);
	A.insert(2,false);
	A.insert(2,true);
	A.insert(3,false);
	
	std::cout << "Board is now" << std::endl << A << std::endl;
	A.insert(0,true);
	A.insert(5,false);
	A.insert(4,true);
	A.insert(5,false);
	std::cout << "Board is now" << std::endl << A << std::endl;
	std::string result=A.insert(4,false);
	std::cout << "Board is now" << std::endl << A << std::endl;
	if(result == "-----"){
		std::cout << "Nothing is intersting." << std::endl;
	}
	else{
		std::cout << result << " is intersting"<<std::endl;
		A.clear();
	}
	std::cout << "Board is now" << std::endl << A << std::endl;
	result="-----";
	while(result=="-----"){
		result=A.insert(3,false);
	}
	std::cout << "Board is now" << std::endl << A << std::endl;
	std::cout << result << " is intersting"<<std::endl;
	A.clear();
	A.insert(1000,true);
	Board B;
	B=A;
	std::cout << "Corner case 1" << std::endl << B << std::endl;
}

