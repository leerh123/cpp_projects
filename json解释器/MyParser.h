#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<stdexcept>
#include<cctype>
#include"MyJson.h"
using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::ofstream;
using std::exception;
class MyParser {
	friend class MyJson;
private:
	string json_str_;
	size_t index_;
public:
	MyParser():index_(0){}
	MyParser(const string& _str):json_str_(_str),index_(0){}
	MyJson parse();
private:
	void get_next_token();
	MyJson null_parse();
	MyJson bool_parse();
	MyJson number_parse();
	MyJson string_parse();
	MyJson list_parse();
	MyJson map_parse();

};

