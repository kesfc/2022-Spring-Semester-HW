#include <string>
#include <vector>


void Query::change_Query(const Movie& movie){
    title=movie.get_title();
    year=movie.get_year();
    time=movie.get_time();
    GenreList=movie.get_GenreList();
    ActorList=movie.get_ActorList();
    RoleList=movie.get_RoleList();
}



bool Query::isthesame(const Query& query){
    if(title!=query.get_title()){
        return false;
    }
    if(time!=query.get_time()){
        return false;
    }
    if(year!=query.get_year()){
        return false;
    }
    else{
        std::vector<string> old_G=query.get_GenreList();
        std::vector<string> old_A=query.get_ActorList();
        std::vector<string> old_R=query.get_RoleList();
        for(unsigned int i=0; i< old_G; i++){
            if(old_G[i]!=GenreList[i]){
                return false;
            }
        }
        for(unsigned int i=0; i< old_R; i++){
            if(old_G[i]!=ActorList[i]){
                return false;
            }
        }
        for(unsigned int i=0; i< old_R; i++){
            if(old_G[i]!=RoleList[i]){
                return false;
            }
        }
        return true;
    }
}
