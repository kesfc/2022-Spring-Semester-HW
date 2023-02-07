#include"Class.h"
#include <iostream>
#include<istream>
#include <algorithm>
#include<string>
#include<string.h>
#include<utility>

// make an array to help write the day in the file later
const std::string DaysInWeek[6] = 
{"","Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

// initial all the contributes that going to be use later
Class::Class(){
    std::string CRN = "";
    std::string departmen = "";
    std::string class_code = "";
    std::string class_name = "";
    std::string class_start = "";
    std::string class_end = "";
    std::string room = "";
}

// implement constructor
Class::Class(std::string aCRN, std::string adepartemnt, 
    std::string aclass_code, std::string aclass_name, char aclass_day, 
    std::string aclass_start, std::string aclass_end, std::string aroom){
    CRN = aCRN;
    department = adepartemnt;
    class_code = aclass_code;
    class_name = aclass_name;
    class_start = aclass_start;
    class_end = aclass_end;
    room = aroom;
    if (aclass_day =='M')
        class_day = 1;
    else if (aclass_day =='T')
        class_day = 2;
    else if (aclass_day =='W')
        class_day = 3;
    else if (aclass_day =='R')
        class_day = 4;
    else if (aclass_day =='F')
        class_day = 5;
}

//implement all accesor
std::string Class::getCRN() const{
    return CRN;
}

std::string Class::getdepartment() const{
    return department;
}

std::string Class::getclass_code() const{
    return class_code;
}

std::string Class::getclass_name() const{
    return class_name;
}

int Class::getday_Int() const{
    return class_day;
}

std::string Class::getclass_day() const{
    return DaysInWeek[class_day];
}

std::string Class::getclass_start() const{
    return class_start;
}

std::string Class::getclass_end() const{
    return class_end;
}

std::string Class::getroom() const{
    return room;
}

// here will give user the times take for a class
std::pair<int,int> Class::getclass_time() const{
    std::pair<int,int> out;
    int start_hour = std::stoi(class_start.substr(0, 2));
    int end_hour = std::stoi(class_end.substr(0, 2));
    int start_minute = std::stoi(class_start.substr(3, 2));
    int end_minute = std::stoi(class_end.substr(3, 2));
    if(start_hour == 12){
        start_hour -= 12;
    }
    if(end_hour == 12){
        end_hour -= 12;
    }
    std::string start_AMPM = class_start.substr(5, 2);
    std::string end_AMPM = class_end.substr(5, 2);
    if (start_AMPM == "PM"){
        start_hour += 12;
    }
    if (end_AMPM == "PM"){
        end_hour += 12;
    }
    out.first = end_hour - start_hour;
    out.second = end_minute - start_minute;
    if (out.second < 0){
        out.second += 60;
        out.first -= 1;
    }
    return out;
}

/* this function will sort a Class class first with room's
alphabetically order, then sort which class day is earlier
then sort whic class is earlier in the day, and last sort by
course code.
*/
bool room_sort(const Class&a, const Class&b){
    int a_day = a.getday_Int();
    int b_day = b.getday_Int();
    int a_hour = std::stoi(a.getclass_start().substr(0, 2));
    int b_hour = std::stoi(b.getclass_start().substr(0, 2));
    if(a_hour == 12){
        a_hour -= 12;
    }
    if(b_hour == 12){
        b_hour -= 12;
    }
    std::string a_AMPM = a.getclass_start().substr(5, 2);
    std::string b_AMPM = b.getclass_start().substr(5, 2);
    if (a_AMPM == "PM"){
        a_hour += 12;
    }
    if (b_AMPM == "PM"){
        b_hour += 12;
    }
    int a_minute = stoi(a.getclass_start().substr(3, 2));
    int b_minute = stoi(b.getclass_start().substr(3, 2));
    std::string a_room = a.getroom();
    std::string b_room = b.getroom();
    if ( a_room < b_room || (a_room == b_room && a_day < b_day)|| (a_room == b_room &&
    a_day == b_day && a_hour < b_hour) ||(a_room == b_room && a_day == b_day && 
    a_hour == b_hour && a_minute < b_minute))
        return true;
    else
        return false;
}

/*This function will by course code first, then by earliest 
course day, and then by latest starting hour if
there is a tie for course code and day
*/
bool department_sort(const Class&a, const Class&b){
    int a_code = (std::stoi(a.getclass_code().substr(0, 4)));
    int b_code = (std::stoi(b.getclass_code().substr(0, 4)));
    int a_code_1 = std::stoi(a.getclass_code().substr(5, 2));
    int b_code_1 = std::stoi(b.getclass_code().substr(5, 2));
    int a_day = a.getday_Int();
    int b_day = b.getday_Int();
    int a_hour = std::stoi(a.getclass_start().substr(0, 2));
    int b_hour = std::stoi(b.getclass_start().substr(0, 2));
    if(a_hour == 12){
        a_hour -= 12;
    }
    if(b_hour == 12){
        b_hour -= 12;
    }
    std::string a_AMPM = a.getclass_start().substr(5, 2);
    std::string b_AMPM = b.getclass_start().substr(5, 2);
    if (a_AMPM == "PM"){
        a_hour += 12;
    }
    if (b_AMPM == "PM"){
        b_hour += 12;
    }
    int a_minute = stoi(a.getclass_start().substr(3, 2));
    int b_minute = stoi(b.getclass_start().substr(3, 2));
    if (a_code < b_code || (a_code == b_code && a_code_1 < b_code_1) || 
    (a_code == b_code && a_code_1 == b_code_1 && a_day < b_day) ||
    (a_code == b_code && a_code_1 == b_code_1 && a_day == b_day && a_hour > b_hour)||
    (a_code == b_code && a_code_1 == b_code_1 && a_day == b_day && a_hour == b_hour 
    && a_minute > b_minute))
        return true;
    else 
        return false;
}

/* this function will sort with department's 
alphabetically order,
*/
bool sort_by_department(const Class&a, const Class&b){
    std::string a_dept = a.getdepartment();
    std::string b_dept = b.getdepartment();
    return a_dept < b_dept;
}

