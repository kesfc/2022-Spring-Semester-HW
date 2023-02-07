#include "Item.h"
#include<string>

Item::Item(){
    time=0;
    food="";
}
Item::Item(int a_time, std::string a_food){
    time=a_time;
    food=a_food;
}
bool sort_time(const Item &A, const Item &B){
    int a_time=A.get_time(); 
    int b_time=B.get_time();
    std::string a_id=A.getName();
    std::string b_id=B.getName();
    return a_time<b_time ||(a_time==b_time && a_id<b_id);
}