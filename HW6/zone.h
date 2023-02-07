#ifndef ZONE_H__
#define ZONE_H__
#include<string>
#include<vector>

class Zone{
    public:
    Zone(char aletter, int anumber): letter(aletter), number(anumber){}
    char get_letter()const{return letter;}
    int get_number()const{return number;}
    std::vector<int> get_azone(int index)const{return positions[index];}
    void add_position(std::vector<int> position){positions.push_back(position);}


    private:
    char letter; 
    int number;
    std::vector<std::vector<int>> positions;
};
bool sort_number(const Zone& a, const Zone& b){
    return a.get_number()<b.get_number();
}
#endif
