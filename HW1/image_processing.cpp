#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*This function will ask use for a string vector, the character user want to get replace, the
Character user want to replace with the previous character, the size of vector, and the size of 
the string in the vector. This vector then will replace the first character with the second 
in the vector be given and won't return any thing.
*/

void raplce_fun(std::vector<std::string> &input, char origin, char replace, int height, int lenth){
	for (int i=0; i<height; i+=1){
		for (int j=0; j<lenth; j+=1){
			if (input[i][j]==origin){
				input[i][j]=replace;
				}

			}
		}
}

/*
This function will asking for a string vector(grid), a charcter, the size of the vector, and the size
of the string in the vector. And it will change all the character next to the input character(up, down,
left, right) to the character been given.
*/
void dilation_erosion_fun(std::vector<std::string> &input, char symbol, int height, int lenth){
	//set a copy of the grid that can use to check the origin place for each character.
	std::vector<std::string> grid=input;
	for( int i=0; i<height; i++){
		for(int j=0; j<lenth; j++){
			//chack each position, if it is not out of boundary, it will replace with the give character.
			if (grid[i][j]==symbol){
				if (i-1>=0){               //check if it is at the first row
					input[i-1][j]=symbol;
				}
				if (i+1<height){           //check if it is at the last row
					input[i+1][j]=symbol;
				}
				if (j-1>=0){             //check if it is at the first column
					input[i][j-1]=symbol;
				}
				if (j+1<lenth){          //check if it is at the last column
					input[i][j+1]=symbol;
				}
				}
			}
		}
	}

int main(int argc, char*argv[]){
	/*since it only should have 4-5 argument, so if the given less the 4 or more than 5, it means
	the argument is not correct. The code will imediately stop runnig.
	*/
	if (argc>6 | argc<5){
		std::cout<<"Please only enter 4-5 command line arguments"<<std::endl;
	}
	// here will take each part of argument and change each to a variable.
	std:: string input_file = argv[1];
	std:: string output_file = argv[2];
	std:: string function = argv[3];
	char origin = argv[4][0];
	//open the file and check if the is able to open, if the file can't open, code will stop running
	std:: ifstream file (input_file);
	if (!file.good()) {
    	std::cerr << "Can't open " << input_file << " to write."<<std::endl;
    exit(1);
  }
	// set up a vector and add each line of the file to to the vector
	std:: vector<std::string> input_grid;
	std:: string line;
	int lenth;
	while(getline(file,line)){
		input_grid.push_back(line);
		lenth=line.size();
	}
	int height=input_grid.size();
	file.close();
	/* checking what fuction did the argument been given asking us to run, and run the specific
	function and the vector will get changed in the function to fit what the arguments asking to do.
	*/
	if (function=="replace"){
		char replace = argv[5][0];
		raplce_fun(input_grid, origin, replace, height, lenth);
	}
	else if (function=="dilation"){
		dilation_erosion_fun(input_grid, origin, height, lenth);
	}

	else if (function=="erosion"){
		char replace=argv[5][0];
		dilation_erosion_fun(input_grid, replace, height, lenth);
	}
	/* Try to open or creat file with file name be given in the arguments, if the file can't be
	open code will stop running
	*/
	std::ofstream fileout(output_file);
	if (!fileout.good()) {
    	std::cerr << "Can't open " << output_file << " to write."<<std::endl;
    	exit(1);
  }
	//Last it will write the vector in the file line by line, and then close the file.
		for (int i=0; i<height; i+=1){
			for (int j=0; j<lenth; j+=1){
				fileout<<input_grid[i][j];
			}
			fileout<<std::endl;
		}
		fileout.close();
	return 0;
}