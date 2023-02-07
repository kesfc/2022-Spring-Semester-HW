#ifndef __MYCLASS_H
#define __MYCLASS_H
#include<iostream>
#include<string>
#include<utility>
class Class{
    public:
        //Constructor
        Class();
        Class(std::string aCRN, std::string adepartemnt, std::string aclass_code, std::string 
        aclass_name, char aclass_day, std::string aclass_start, std::string aclass_end, 
        std::string aroom);
        //Accessor
        std::string getCRN() const;
        std::string getdepartment() const;
        std::string getclass_code() const;
        std::string getclass_name() const;
        std::string getclass_day() const;
        int getday_Int()const;
        std::string getclass_start() const;
        std::string getclass_end() const;
        std::string getroom() const;
        std::pair<int,int> getclass_time() const;
    private:
        std::string CRN;
        std::string department;
        std::string class_code;
        std::string class_name;
        int class_day;
        std::string class_start;
        std::string class_end;
        std::string room;

};
bool room_sort(const Class&a, const Class&b);
bool department_sort(const Class&a, const Class&b);
bool sort_by_department(const Class&a, const Class&b);
#endif
