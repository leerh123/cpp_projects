#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<utility>
#include<list>
#include<array>
#include<iterator>
using std::vector;
using std::map;
using std::string;
using std::cout;
using std::flush;
using std::endl;
using std::ostream;
using std::ofstream;
using std::pair;
using std::list;
using std::array;
class MyJson;

enum Type {
	null_json = 0,
	bool_json,
	number_json,
	string_json,
	list_json,
	map_json
};


struct Value {
	bool value_bool;
	long double value_number;
	string value_string;
	vector<MyJson> value_list;
	map<string, MyJson> value_map;
};

class MyJson {
	
	friend ostream& operator<<(ostream& os, const MyJson& stu);


private:
	typedef vector<MyJson>::iterator iter_list;
	typedef map<string, MyJson>::iterator iter_map;
	Type type_;
	Value value_;

public:
	explicit MyJson();

	explicit MyJson(Type);
	explicit MyJson(string _type,bool construction);

	explicit MyJson(bool);

	explicit MyJson(short);
	explicit MyJson(int);
	explicit MyJson(float);
	explicit MyJson(double);
	explicit MyJson(long double);
	explicit MyJson(long int);
	explicit MyJson(long long int);
	explicit MyJson(unsigned int);
	explicit MyJson(unsigned long int);

	explicit MyJson(const string&);
	explicit MyJson(const char*);

	explicit MyJson(const list<MyJson>&);
	explicit MyJson(const vector<MyJson>&);

	explicit MyJson(const map<string,MyJson>&);

	~MyJson();

	void parse(const string&);
	string type();
	Value value();
	MyJson& operator[](size_t);
	MyJson& operator[](string);
	MyJson& operator[](const MyJson&);
	MyJson& operator=(const MyJson&);
	//delete
	size_t erase(string);
	iter_list erase(iter_list);
	iter_map erase(iter_map);
	iter_list erase(iter_list, iter_list);
	iter_map erase(iter_map, iter_map);
	//find
	iter_map find(string);
	//insert
	pair<iter_map, bool>  insert(pair<string, MyJson>);
	iter_list insert(iter_list, const MyJson&);
	void push_back(const MyJson&);
	//iterator
	iter_list begin_list();
	iter_list end_list();
	iter_map begin_map();
	iter_map end_map();

private:
	


};

