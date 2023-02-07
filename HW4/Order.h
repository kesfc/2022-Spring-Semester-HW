#ifndef __order_H
#define __order_H
#include <string>
#include <list>

class Order{
    public:
    //Constructor
    Order();
    Order(int a_id, int a_promised_time, std::list <std::string> 
    a_order_list);
    //Accessor
    std::list <std::string> getItems()const{return Items;}
    int get_id()const{return id;}
    int get_promised_time()const{return promised_time;}
    int get_n_item()const{return n_item;}
    //chenge time
    void minus_one(){promised_time=promised_time-1;}
    private:
    int id;
    int promised_time;
    int n_item;
    std::list <std::string> Items;
    
};
//sortings
bool sort_promised_time(const Order&A, const Order&B);
bool sort_id(const Order&A, const Order&B);
#endif