#ifndef Movie_h_
#define Movie_h_
#include <string>
#include <vector>
class Movie{
    public:
        //Default Constructor
        Movie(): title(""), year(""), time("") {}
        //Constructor
        Movie(std::string atitle, std::string ayear, std::string atime):
        title(atitle),year(ayear),time(atime){}
        //Add something in list;
        void add_Genre(const std::string& Genre){GenreList.push_back(Genre);}
        void add_Actor(const std::string& Actor){ActorList.push_back(Actor);}
        void add_Role(const std::string& Role){RoleList.push_back(Role);}
        //Getter
        const std::string &get_title() const {return title;}
        const std::string &get_year() const {return year;}
        const std::string &get_time() const {return time;}
        int Genre_count() const {return GenreList.size();}
        int Actor_count() const {return ActorList.size();}
        int Role_count() const {return RoleList.size();}
        const std::vector<std::string> &get_GenreList() const {return GenreList;}
        const std::vector<std::string> &get_ActorList() const {return ActorList;}
        const std::vector<std::string> &get_RoleList() const {return RoleList;}
    private:
        std::string title;
        std::string year;
        std::string time;
        std::vector<std::string> GenreList;
        std::vector<std::string> ActorList;
        std::vector<std::string> RoleList;

};

#endif