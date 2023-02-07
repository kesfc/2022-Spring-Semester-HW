#ifndef HashTable_h_
#define HashTable_h_
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include "Query.h"
#include "Movie.h"
class HashTable
{
public:
    HashTable() : table_size(100), size(0), occupancy(0.5)
    {
        Query temp;
        std::list<Movie *> temp1;
        //initial something inside table
        table = std::vector<std::pair<Query, std::list<Movie *>>>(100, 
        std::make_pair(temp, temp1));
    }
    //function that use to resize.
    void change_table_size(unsigned int num)
    {
        //copy the old vector
        std::vector<std::pair<Query, std::list<Movie *>>> old = table;
        table.clear();//clear the member function table
        Query temp;
        std::list<Movie *> temp1;
        table = std::vector<std::pair<Query, std::list<Movie *>>>(num, 
        std::make_pair(temp, temp1));//inital table with new size
        for (unsigned int i = 0; i < table_size; i++)
        {
            if (old[i].first.get_time() != "")//if there is somehting at old index.
            {
                unsigned int New_hash = (old[i].first).find_hash_value();
                unsigned int index = New_hash % num;//find it's new index
                if (table[index].first.get_title() == "")//if this index is empty
                {//add it at this size
                    table[index].first.copy_Query(old[i].first);
                    table[index].second = old[i].second;
                }
                else
                {//loop it untile find the next empty index
                    index++;
                    if (index == num)//when it loop to the last index, change it the firts
                    //index.
                    {
                        index = 0;
                    }
                }
            }
        }
        table_size = num;//change tbale size
    }
    void change_occupancy(float num) { occupancy = num; }
    //function that use to inset pair into the table;
    void insert(const Query &query, Movie *movie)
    {
        unsigned Hash_value = query.find_hash_value();
        unsigned int index = Hash_value % table_size;
        //find the index for the quries
        if ((table[index].first).get_time() == "")
        {//if the index is empty add it at this index.
            table[index].first.copy_Query(query);
            table[index].second.push_back(movie);
            size++;
        }
        else
        {
            while (true)//loop it untill...
            {
                if (index == table_size)
                //if index goes at the last position move it the first
                {
                    index = 0;
                }
                else if (table[index].first.isthesame(query))
                //if loop and find the same query, add the movies in the list.
                {
                    table[index].second.push_back(movie);
                    size++;
                    break;
                }
                else if (table[index].first.get_time() == "")
                {//if loop at the index that is empty add it at that position.
                    (table[index].first).copy_Query(query);
                    table[index].second.push_back(movie);
                    size++;
                    break;
                }
                else
                {
                    index++;
                }
            }
        }
        if (size >= table_size * occupancy)
        {
            change_table_size(table_size * 2);
        }
    }
    //function that take a query and list of movie pointer, it will find the same queris
    //in the hash table(if there is), and copy it's list into the list pass in.
    void find(const Query &query, std::list<Movie *> &all_movies)
    {
        unsigned int hash_value = query.find_hash_value();
        unsigned int index = hash_value % table_size;
        while (!query.isthesame(table[index].first))
        {
            if (table[index].first.get_time() == "")
            {
                return;
            }
            index++;
            if (index == table_size)
            {
                index = 0;
            }
        }
        all_movies = table[index].second;
        return;
    }

private:
    std::vector<std::pair<Query, std::list<Movie *>>> table;
    unsigned int table_size;
    int size;
    float occupancy;
};
#endif