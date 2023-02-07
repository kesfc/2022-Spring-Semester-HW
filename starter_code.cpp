/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
*/
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "Query.h"
#include "HashTable.h"
#include "Movie.h"

// permute to find all 64 possiblity and add it to a vector of vetor of int
void permute_filters(int pos, std::vector<int> &filter, std::vector<std::vector<int>> 
&all_possible)
{
	if (pos == 6)
	{
		all_possible.push_back(filter);
		return;
	}
	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos + 1, filter_new, all_possible);
	permute_filters(pos + 1, filter, all_possible);
}

// Driver function, feel free to modify to pass more arguments
void permute_filters(std::vector<std::vector<int>> &all_possible)
{
	std::vector<int> filter;
	permute_filters(0, filter, all_possible);
}

//giving a movie object, and a vetor of vector of int that contains all possibilty. 
//and return a vertor of query that contains all queries that movie can be in.
std::vector<Query> find_all_Query(const Movie &movie, const std::vector<std::vector<int>> 
&List)
{
	std::vector<Query> all_query;
	for (unsigned int i = 0; i < List.size(); i++)
	{
		Query New;
		New.change_Query(movie);
		if (List[i][0] == 1)
		{
			New.change_title();
		}
		if (List[i][1] == 1)
		{
			New.change_year();
		}
		if (List[i][2] == 1)
		{
			New.change_time();
		}
		if (List[i][3] == 1)
		{
			New.change_Genre();
		}
		if (List[i][4] == 1)
		{
			New.change_Actor();
		}
		if (List[i][5] == 1)
		{
			New.change_Role();
		}
		all_query.push_back(New);
	}
	return all_query;
}

//function that help parse all movies form a giving file
void parse_movie(const std::string &file_name, std::vector<Movie> &all_movies)
{
	std::ifstream in_str(file_name);
	std::string title;
	std::string year;
	std::string time;
	if (!in_str.good())
	{
		std::cerr << "Can't open " << file_name << " to read.\n";
		exit(1);
	}
	while (in_str >> title)
	{
		in_str >> year;
		in_str >> time;
		Movie temp(title, year, time);
		int num;
		std::string temp_str;
		in_str >> num;
		for (int i = 0; i < num; i++)
		{
			in_str >> temp_str;
			temp.add_Genre(temp_str);
		}
		in_str >> num;
		for (int i = 0; i < num; i++)
		{
			in_str >> temp_str;
			temp.add_Actor(temp_str);
		}
		in_str >> num;
		for (int i = 0; i < num; i++)
		{
			in_str >> temp_str;
			temp.add_Role(temp_str);
		}
		all_movies.push_back(temp);
	}
}

//function that help to parse actors from a file;
void parse_actor(const std::string &file_name, std::map<std::string, std::string> &
												   actor_name)
{
	std::ifstream in_str(file_name);
	if (!in_str.good())
	{
		std::cerr << "Can't open " << file_name << " to read.\n";
		exit(1);
	}
	std::string key;
	std::string value;
	while (in_str >> key)
	{
		in_str >> value;
		actor_name[key] = value;
	}
}

//function help parse query by std::cin;
void parse_query(Query &query)
{
	int number;
	std::string temp;
	std::cin >> number;
	for (int i = 0; i < number; i++)
	{
		std::cin >> temp;
		query.add_Genre(temp);
	}
	std::cin >> number;
	for (int i = 0; i < number; i++)
	{
		std::cin >> temp;
		query.add_Actor(temp);
	}
	std::cin >> number;
	for (int i = 0; i < number; i++)
	{
		std::cin >> temp;
		query.add_Role(temp);
	}
}

//healper function help to print all movies that would fit query.
void print_ans(const Movie *movie, std::map<std::string, std::string> &actors_name)
{
	std::cout << (*movie).get_title() << std::endl;
	std::cout << (*movie).get_year() << std::endl;
	std::cout << (*movie).get_time() << std::endl;
	//copy all list down
	std::vector<std::string> Genre = (*movie).get_GenreList();
	std::vector<std::string> Actor = (*movie).get_ActorList();
	std::vector<std::string> Role = (*movie).get_RoleList();
	std::cout << (*movie).Genre_count();
	for (int i = 0; i < (*movie).Genre_count(); i++)
	{
		std::cout << " " << Genre[i];
	}
	std::cout << std::endl;
	std::cout << (*movie).Actor_count();
	for (int i = 0; i < (*movie).Actor_count(); i++)
	{
		std::cout << " " << actors_name[(Actor[i])] << " (" << Role[i] << ")";
	}
	std::cout << std::endl;
}

int main()
{
	std::string inputs;
	//movie vector use to store all movies
	std::vector<Movie> all_movies;
	//what actor called is key, actor's real name as value;
	std::map<std::string, std::string> actor_name;
	std::string file_name;
	HashTable Hash;//initial a hashtable objext
	std::vector<std::vector<int>> all_possible;
	//get all possible combination by using the helper function
	permute_filters(all_possible);
	while (true)
	{
		std::cin >> inputs;
		if (inputs == "table_size")
		{
			int table_size;
			std::cin >> table_size;
			Hash.change_table_size(table_size);//change table size
		}
		if (inputs == "occupancy")
		{
			float occupancy;
			std::cin >> occupancy;
			Hash.change_occupancy(occupancy);//change table's occupancy
		}
		if (inputs == "quit")
		{
			break;
		}
		else if (inputs == "movies")
		{
			std::cin >> file_name;
			parse_movie(file_name, all_movies);//parse every movie in a function by 
			//calling the function.
			for (unsigned int i = 0; i < all_movies.size(); i++)
			{
				std::vector<Query> all_query = find_all_Query(all_movies[i], all_possible);
				for (unsigned int k = 0; k < all_query.size(); k++)
				{//insert a pointer of movies and it's possible queries into hashtable;
					Movie *movie = &(all_movies[i]);
					Hash.insert(all_query[k], movie);
				}
			}
		}
		else if (inputs == "actors")
		{
			std::cin >> file_name;
		//parsing a file in to a map which key is what actor called, value is real name
			parse_actor(file_name, actor_name);
		}
		else if (inputs == "query")
		{
			std::string title;
			std::string year;
			std::string time;
			std::cin >> title;
			std::cin >> year;
			std::cin >> time;
			Query query(title, year, time);//parse everything into a query objet.
			parse_query(query);
			std::list<Movie *> Movies;//creat a empty list of movie object
			Hash.find(query, Movies);
			//use find function to find pointer of movies that fit queries 
			int number_ans = Movies.size();
			if (number_ans == 0)
			{
				std::cout << "No results for query." << std::endl;
			}
			else
			{
				std::cout << "Printing " << number_ans << " result(s):" << std::endl;
				std::list<Movie *>::const_iterator i;
				for (i = Movies.begin(); i != Movies.end(); i++)
				{
					//use print_ans function to help print out the final staff.
					print_ans(*i, actor_name);
				}
			}
		}
	}
}
