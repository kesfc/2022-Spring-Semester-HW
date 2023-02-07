#ifndef Query_h_
#define Query_h_
#include <string>
#include <vector>
#include<iostream>
#include "Movie.h"
class Query{
    public:
        //Default Constructor
        Query(): title(""), year(""), time("") {}
        //Constructor
        Query(std::string atitle, std::string ayear, std::string atime):
        title(atitle),year(ayear),time(atime){}
        //function that use to copy a movie to a query object
        void change_Query( const Movie& movie){
            title=movie.get_title();
            year=movie.get_year();
            time=movie.get_time();
            GenreList=movie.get_GenreList();
            ActorList=movie.get_ActorList();
            RoleList=movie.get_RoleList();
        }
        //function that will copy the query
        void copy_Query(const Query &query){
            title=query.get_title();
            year=query.get_year();
            time=query.get_time();
            GenreList=query.get_GenreList();
            ActorList=query.get_ActorList();
            RoleList=query.get_RoleList();
        }
        //Add something in list;
        void add_Genre(const std::string& Genre){GenreList.push_back(Genre);}
        void add_Actor(const std::string& Actor){ActorList.push_back(Actor);}
        void add_Role(const std::string& Role){RoleList.push_back(Role);}
        //Getter
        const std::string &get_title() const {return title;}
        const std::string &get_year() const {return year;}
        const std::string &get_time() const {return time;}
        unsigned int Genre_count() const {return GenreList.size();}
        unsigned int Actor_count() const {return ActorList.size();}
        unsigned int Role_count() const {return RoleList.size();}
        const std::vector<std::string> &get_GenreList() const {return GenreList;}
        const std::vector<std::string> &get_ActorList() const {return ActorList;}
        const std::vector<std::string> &get_RoleList() const {return RoleList;}
        //change to wild card.
        void change_title(){title="?";}
        void change_year(){year="?";}
        void change_time(){time="?";}
        void change_Genre(){GenreList.clear();}
        void change_Actor(){ActorList.clear();}
        void change_Role(){RoleList.clear();}
        //function use to find if both query is the same.
        bool isthesame(const Query& old)const{
            if(title!=old.get_title()){
                return false;
            }
            else if(time!=old.get_time()){
                return false;
            }
            else if(year!=old.get_year()){
                return false;
            }
            else{
                std::vector<std::string> old_G=old.get_GenreList();
                std::vector<std::string> old_A=old.get_ActorList();
                std::vector<std::string> old_R=old.get_RoleList();
                if(old_G!=GenreList){
                    return false;
                }
                if(old_A!=ActorList){
                    return false;
                }
                if(old_R!=RoleList){
                    return false;
                }
                return true;
            }
        };
        //hash function, using to find hash value
        unsigned int find_hash_value()const{
            //  This implementation comes from 
            //  http://www.partow.net/programming/hashfunctions/
            //
            //  This is a general-purpose, very good hash function for strings.
            unsigned int hash = 231301;
            for(unsigned int i=0; i<title.size(); i++){
                hash ^= ((hash << 5) + title[i] + (hash >> 2));
            }
            for(unsigned int i=0; i<year.size(); i++){
                hash ^= ((hash << 5) + year[i] + (hash >> 2));
            }
            for(unsigned int i=0; i<time.size(); i++){
                hash ^= ((hash << 5) + time[i] + (hash >> 2));
            }
            for(unsigned int i=0; i<GenreList.size(); i++){
                for(unsigned int k=0; k<GenreList[i].size(); k++){
                    hash ^= ((hash << 5) + GenreList[i][k] + (hash >> 2));
                }
            }
            for(unsigned int i=0; i<ActorList.size(); i++){
                for(unsigned int k=0; k<ActorList[i].size(); k++){
                    hash ^= ((hash << 5) + ActorList[i][k] + (hash >> 2));
                }
            }
            for(unsigned int i=0; i<RoleList.size(); i++){
                for(unsigned int k=0; k<RoleList[i].size(); k++){
                    hash ^= ((hash << 5) + RoleList[i][k] + (hash >> 2));
                }
            }
            return hash;
        }
            private:
                std::string title;
                std::string year;
                std::string time;
                std::vector<std::string> GenreList;
                std::vector<std::string> ActorList;
                std::vector<std::string> RoleList;
        };

#endif