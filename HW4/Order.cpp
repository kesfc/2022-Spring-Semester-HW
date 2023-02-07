#include "Order.h"
Order::Order(){
    id=0;
    promised_time=0;
    n_item=0;
}
Order::Order(int a_id, int a_promised_time, std::list <std::string> 
a_order_list){
    id=a_id;
    promised_time=a_promised_time;
    Items=a_order_list;
}

//sorting by promised_time first, if it is equial, sort by id.
bool sort_promised_time(const Order&A, const Order&B){ 
    int a_time=A.get_promised_time(); 
    int b_time=B.get_promised_time();
    int a_id=A.get_id();
    int b_id=B.get_id();
    return a_time<b_time || (a_time==b_time && a_id<b_id);
}

//sort by id
bool sort_id(const Order&A, const Order&B){
    int a_id=A.get_id();
    int b_id=B.get_id();
    return a_id<b_id;
}