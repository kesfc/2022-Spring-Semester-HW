#ifndef __item_H
#define __item_H
#include<string>
class Item{
    public:
    //Constructor
    Item();
    Item(int a_time, std::string a_food);
    //Accesoor
    int get_time()const{return time;}
    std::string getName()const{return food;}
    //Change time
    void minus_one(){time=time-1;}
    private:
    int time;
    std::string food;

};
//sorting
bool sort_time(const Item &A, const Item &B);
#endif