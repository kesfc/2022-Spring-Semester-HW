#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include"Class.h"
#include <utility>

/*This function will asking for a Class vector, the name of output file, and a 
department. And it will write each class Coursenum, Class Title, Day, Start 
Time, End Time in order.
*/
void dept_out(std::vector <Class> class_in_dept, std::string output_file, 
std::string dept_name){
    // erro checking, if the output file is able to creat or open.
    std::ofstream out_str(output_file);
    if (!out_str) {
        std::cerr << "Could not open " << output_file << " to write.\n";
        exit(0);
    }
    // set a length for class title and day, and loop to find the longest
    std::string longest_class = "Class Title", longest_day = "Day";
    int max_length_class = longest_class.size(), max_length_day = longest_day.size();
    int number_class = class_in_dept.size();
        for (int i = 0; i < number_class; i++){
            int length_class = class_in_dept[i].getclass_name().size();
            int length_day = class_in_dept[i].getclass_day().size();
            if (length_class > max_length_class){
                max_length_class = length_class;
                longest_class = class_in_dept[i].getclass_name();
            }
            if (length_day > max_length_day){
                max_length_day = length_day;
                longest_day = class_in_dept[i].getclass_day();
            }
        }
    // writting the first two line of the in the output file.
    out_str << "Dept " << dept_name << std::endl;
    out_str << std::setw(11) << std::left << "Coursenum";
    out_str << std::setw(max_length_class + 2) << std::left << "Class Title";
    out_str << std::setw(max_length_day + 2) << std::left << "Day";
    out_str << std::setw(12) << std::left << "Start Time";
    out_str << std::setw(8) << std::left << "End Time" << std::endl;
    out_str << std::string (9, '-') << "  " << std::string (max_length_class, '-')
    << "  " << std::string ( max_length_day, '-') << "  " << std::string (10, '-')
    <<"  " << std::string ( 8, '-') << std::endl;
    // loop to get all the class information into the input file.
    for (int i = 0; i < number_class; i++){
        out_str << std::setw(11) << std::left << class_in_dept[i].getclass_code();
        out_str << std::setw(max_length_class + 2) << std::left << 
        class_in_dept[i].getclass_name();
        out_str << std::setw(max_length_day + 2) << std::left << 
        class_in_dept[i].getclass_day();
        out_str << std::setw(12) << std::left << class_in_dept[i].getclass_start();
        out_str << std::setw(8) << std::left << class_in_dept[i].getclass_end() 
        << std::endl;
    }
    //writting the last line and close the file.
    out_str << number_class<<" entries" << std::endl;
    out_str << std::endl;
    out_str.close();
}

/*This function will asking a class vector, an output file, and the name of the 
room want to get write in the output file. This function will then write all 
the class's Dept, Coursenum. Class Title, Day, Start Time, End Time in the output 
with class alphabetic number.
*/
void room_out(std::vector <Class> class_in_room, std::string output_file, 
std::string room_name){
    std::ofstream out_str(output_file);
    // erro checking, if the output file is able to creat or open.
    if (!out_str) {
        std::cerr << "Could not open " << output_file << " to write.\n";
        exit(0);
    }
    /* set a initial length for dept, class title, day, and then loop 
    to find the longest for each */
    std::string longest_dept = "Dept", longest_class = "Class Title", 
    longest_day = "Day";
    int max_length_dept = longest_dept.size(), max_length_class = 
    longest_class.size(), max_length_day = longest_day.size(), 
    number_class = class_in_room.size();
    for (int i = 0; i < number_class; i++){
        int length_dept = class_in_room[i].getdepartment().size();
        int length_class = class_in_room[i].getclass_name().size();
        int length_day = class_in_room[i].getclass_day().size();
        if (length_dept > max_length_dept){
            max_length_dept = length_dept;
            longest_dept = class_in_room[i].getclass_name();
        }
        if (length_class > max_length_class){
            max_length_class = length_class;
            longest_class = class_in_room[i].getclass_name();
        }
        if (length_day > max_length_day){
            max_length_day = length_day;
            longest_day = class_in_room[i].getclass_day();
        }
    }
    //writting the first two lines in the output file
    out_str << "Room " << room_name << std::endl;
    out_str << std::setw(max_length_dept + 2) << std::left << "Dept";
    out_str << std::setw(11) << std::left << "Coursenum";
    out_str << std::setw(max_length_class + 2) << std::left << "Class Title";
    out_str << std::setw(max_length_day + 2) << std::left << "Day";
    out_str << std::setw(12) << std::left << "Start Time";
    out_str << std::setw(8) << std::left << "End Time" << std::endl;
    out_str << std::string (max_length_dept, '-') << "  "
    << std::string (9, '-') <<
    "  " << std::string (max_length_class, '-') << "  " <<
    std::string ( max_length_day, '-') << "  " << std::string (10, '-')
    << "  " << std::string ( 8, '-') << std::endl;
    // looping to write all class information
    for (int i = 0; i < number_class; i++){
        out_str << std::setw(max_length_dept +2 ) << std::left << 
        class_in_room[i].getdepartment() << std::setw(11) << 
        std::left << class_in_room[i].getclass_code() << 
        std::setw(max_length_class + 2) << std::left << 
        class_in_room[i].getclass_name() << std::setw(max_length_day+2)
        << std::left << class_in_room[i].getclass_day() << std::setw(12) 
        << std::left << class_in_room[i].getclass_start() << std::setw(8) 
        << std::left << class_in_room[i].getclass_end() << std::endl;
    }
    out_str << number_class << " entries" << std::endl;
}

/*This function will asking a class vector with all the classes from the 
input file and the name of the expecting output file. Then it will output
all room with classes take place in each room.
*/
void all_room_out(std::vector <Class> all_class, std::string output_file){
    std::ofstream out_str(output_file);
    // erro checking, if the output file is able to creat or open.
    if (!out_str) {
        std::cerr << "Could not open " << output_file << " to write.\n";
        exit(0);
    }
    std::string room = "0";
    // find number of class and looping the find all rooms
    int class_num = all_class.size();
    std::vector<std::string> rooms;
    for (int i = 0; i < class_num; i++){
        if (all_class[i].getroom() != room){
            room = all_class[i].getroom();
            rooms.push_back(room);
        }
    }
    //find the length of the room vector and start looping
    int room_num = rooms.size();
    for (int i = 0; i < room_num; i++){
        std::vector<Class> class_in_room;
        //find the classes in each room
        for(int k = 0; k< class_num; k++){
            if (all_class[k].getroom() == rooms[i]){
                class_in_room.push_back(all_class[k]);
            }
        }
        // writting the first two line for each room
        std::string longest_dept = "Dept", longest_class = "Class Title", 
        longest_day = "Day";
        int max_length_dept = longest_dept.size(), max_length_class = 
        longest_class.size(), max_length_day = longest_day.size(), 
        number_class = class_in_room.size();
        //looping to write all class information in each room
        for (int j = 0; j < number_class; j++){
            int length_dept = class_in_room[j].getdepartment().size();
            int length_class = class_in_room[j].getclass_name().size();
            int length_day = class_in_room[j].getclass_day().size();
            if (length_dept > max_length_dept){
                max_length_dept = length_dept;
                longest_dept = class_in_room[j].getclass_name();
            }
            if (length_class > max_length_class){
                max_length_class = length_class;
                longest_class = class_in_room[j].getclass_name();
            }
            if (length_day > max_length_day){
                max_length_day = length_day;
                longest_day = class_in_room[j].getclass_day();
            }
        }
        out_str << "Room " << rooms[i] << std::endl;
        out_str << std::setw(max_length_dept+2) << std::left << "Dept";
        out_str << std::setw(11) << std::left << "Coursenum";
        out_str << std::setw(max_length_class+2) << std::left << "Class Title";
        out_str << std::setw(max_length_day+2) << std::left << "Day";
        out_str << std::setw(12) << std::left << "Start Time";
        out_str << std::setw(8) << std::left << "End Time" << std::endl;
        out_str << std::string (max_length_dept, '-') << "  " << std::string (9, '-')
        << "  "  << std::string (max_length_class, '-') << "  " 
        << std::string ( max_length_day, '-') <<"  " << std::string (10, '-')
        << "  " << std::string ( 8, '-') << std::endl;
        for (int j = 0; j < number_class; j++){
            out_str << std::setw(max_length_dept+2) << std::left 
            << class_in_room[j].getdepartment();
            out_str << std::setw(11) << std::left << 
            class_in_room[j].getclass_code();
            out_str << std::setw(max_length_class+2) << 
            std::left << class_in_room[j].getclass_name();
            out_str << std::setw(max_length_day+2) << 
            std::left << class_in_room[j].getclass_day();
            out_str << std::setw(12) << std::left << 
            class_in_room[j].getclass_start();
            out_str << std::setw(8) << std::left << 
            class_in_room[j].getclass_end() << std::endl;
        }
        out_str << number_class <<" entries" << std::endl;
        out_str << std::endl;
        }
}

/*This function is asking for vector class of the the class from the input file, 
a vector of all department from input file, the name of output file, the length of
the longest dept.
*/
void custom_out(std::vector <Class> all_class, std::vector <std:: string> all_dept, 
std::string output_file, int max_dept){
    std::ofstream out_str(output_file);
    // erro checking, if the output file is able to creat or open.
    if (!out_str) {
        std::cerr << "Could not open " << output_file << " to write.\n";
        exit(0);
    }
    //find number of class and number depr involved.
    int total_class=all_class.size();
    int size =all_dept.size();
    //writting the first two line in the output file.
    out_str<<std::setw(max_dept+2) << std::left << "dept" << std::setw(11) << std::left 
    << "class_num"<< std::setw(16) << std::left << "types_of_class" << 
    "hours_of_class_per_week" << std::endl;
    out_str << std::string (max_dept, '-') << "  " << std::string (9, '-')
    << "  " << std::string (14, '-') << "  " << std::string (23, '-') << std::endl;
    //looping the to write all the dept information in output file
    for (int i = 0; i<size; i++){
        /*creat an vector, the index 0 will be the number of class,
        index 1 will be the number of types of class, index 2 will
        be the total hour of class for a dept, and index 3 will be
        the total minute of class for a dept. index 2 and 3 combine 
        together will be the total hours of class for a department
        each week
        */
        std::string class_code_change = "0000";
        std::string section = "00";
        std::vector<int> a;
        a.push_back(0);
        a.push_back(0);
        a.push_back(0);
        a.push_back(0);
        /*looping to find number of class, number of types of class,
        total hour, and total minute*/
        for (int k = 0; k<total_class; k++){
            if(all_class[k].getdepartment() == all_dept[i]){
                std::pair <int,int> out;
                out = all_class[k].getclass_time();
                std::string class_code = all_class[k].getclass_code();
                if (class_code_change != class_code.substr(0,4)){
                    a[0] += 1;
                    a[1] += 1;
                    class_code_change = class_code.substr(0,4);
                }
                else if (section != class_code.substr(4,2)){
                    a[0] += 1;
                    section = class_code.substr(4,2);
                }
                a[2] += out.first;
                a[3] += out.second;
            }
            /*minute might be over 60, so divide by minute 60,
            add the number get to hour, and minute will be remaining
            number.
            */
            a[2] += a[3]/60;
            a[3] = a[3]%60;
        }
    //since hour and minute may can be 0, if is equal to 0, replace with "00".
    std::string hour = std::to_string(a[2]);
    std::string minute = std::to_string(a[3]);
    if (hour == "0"){
        hour = "00";
    };
    if (minute == "0"){
        minute = "00";
    };
    //write the information of each dept into the output file.
    out_str << std::setw(max_dept+2) << std::left << all_dept[i] << std::setw(11) 
    << std::left << a[0] << std::setw(16) << std::left << a[1] << 
    hour << ":" << minute << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // erro checking, if given too many argument or too less.
    if ((4 > argc) | (5 < argc)) {
        std::cerr << "Given incorect number of arguments.\n";
        return 1;
    }
    std::ifstream in_str(argv[1]);
    // erro checking, if the input file is able to creat or open.
    if (!in_str) {
        std::cerr << "Could not open " << argv[1] << " to read.\n";
        return 1;
    }
    std::string output_file = argv[2];
    std::string output_type = argv[3], CRN, department, class_code, class_name;
    std::string class_days, class_start, class_end, room;
    std::vector<Class> All_class;
    //read file and pass it to all varieble, and then store each line as class.
    while (true) {
       if(!(in_str >> CRN)){
           break;
       }
        in_str >> department >> class_code >> class_name >> class_days
        >> class_start >> class_end >> room;
        int days = class_days.size();
        for (int i = 0; i < days; i++){
            char class_day = class_days[i];
            All_class.push_back(Class(CRN, department, class_code, 
            class_name, class_day, class_start, class_end, room));
        }
    }
    in_str.close();
    int class_size = All_class.size();
    if (class_size == 0){
        std::ofstream out_str(output_file);
        // erro checking, if the output file is able to creat or open.
        if (!out_str) {
            std::cerr << "Could not open " << output_file << " to write.\n";
            exit(0);
        }
        out_str<<"No data available."<<std::endl;
    }
    else if (output_type == "room"){
        //check if it gave the forth argument.
        if (argc == 5){
            /*if give the 4th argument, it will creat a new vector
            and stor all classes that take place in the room be giving.
            */
            std::vector <Class> class_in_room;
            std::string room_name = argv[4];
            int classes = All_class.size();
            for (int i = 0; i < classes; i++){
                if (All_class[i].getroom() == room_name){
                    class_in_room.push_back(All_class[i]);
                    }   
                }
            sort(class_in_room.begin(),class_in_room.end(),room_sort);
            room_out(class_in_room, output_file, room_name);
        }
        else{
            sort(All_class.begin(),All_class.end(),room_sort);
            all_room_out(All_class, output_file);
        }
    }
    /* when teh third argument is "dept", it will first creat a
    vector and store all the class that is in the dept that giving
    in the forth argument, and then sort, last go to a out put function.
    */
    else if (output_type == "dept"){
        std::vector <Class> class_in_dept;
        std::string dept_name = argv[4];
        int classes = All_class.size();
        for (int i = 0; i < classes; i++){
            if (All_class[i].getdepartment() == dept_name){
                class_in_dept.push_back(All_class[i]);
                }   
            }
        sort(class_in_dept.begin(), class_in_dept.end(), department_sort);
        dept_out(class_in_dept, output_file, dept_name);
    }
    /* For intersting statistic, I choose to make an output, of class of each
    dept each week(if a class have two days of class per week, it will still 
    cout 1), types of class in a dept each week(it will count by the course code
    if the first 4 digit of classes code is the same, thoese classes will be 
    consider as a same class or same type of class), last it will have the total 
    times of each dept's class for a week.
    */
    else if (output_type=="custom"){
        std::vector<std::string> all_dept;
        std::string Dept="dept";
        int max_dept=0;
        //loop to find the longest dept
        sort(All_class.begin(), All_class.end(), sort_by_department);
        for(int i=0; i<class_size; i++){
            if (Dept != All_class[i].getdepartment()){
                Dept=All_class[i].getdepartment();
                all_dept.push_back(Dept);
            }
            int dept_size=All_class[i].getdepartment().size();
            if (max_dept<dept_size){
                max_dept=dept_size;
            }
        }
        sort(All_class.begin(), All_class.end(), department_sort);
        custom_out(All_class, all_dept, output_file, max_dept);
        }
  return 0;
}
