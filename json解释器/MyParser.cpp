#include"MyParser.h"
MyJson MyParser::parse() {
	get_next_token();
	try {
		if (json_str_.substr(index_, 4) == "null")
			return null_parse();

		if (json_str_.substr(index_, 4) == "true" || json_str_.substr(index_, 5) == "false")
			return bool_parse();

		if (isdigit(json_str_[index_]) > 0 ||
			(json_str_[index_] == '-' && isdigit(json_str_[index_ + 1]) > 0))
			return number_parse();

		if (json_str_[index_] == '"' || json_str_[index_] == '\'')
			return string_parse();

		if (json_str_[index_] == '[')
			return list_parse();

		if (json_str_[index_] == '{')
			return map_parse();

		throw exception("class:MyParser\n funtion:parse\n reason:unexcepted charactor");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}

}

void MyParser::get_next_token() {
	while (json_str_[index_] == ' ' || json_str_[index_] == '\r' ||
		json_str_[index_] == '\n' || json_str_[index_] == '\t') {
		index_++;
	}
	if (index_ >= json_str_.size()) {
		try {
			throw exception("class:MyParser\n function:get_next_token\n reason:out of range");
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}
	}

}

MyJson MyParser::null_parse() {
	index_ += 4;
	return MyJson("null", 1);
}

MyJson MyParser::bool_parse() {
	if (json_str_.compare(index_, 4, "true") == 0)
	{
		index_ += 4;
		return MyJson(true);
	}
	else {
		index_ += 5;
		return MyJson(false);
	}

}

MyJson MyParser::number_parse() {
	size_t pos_intital = index_;
	//负数
	if (json_str_[index_] == '-') {
		index_++;
		try {
			if (isdigit(json_str_[index_]) == 0)
				throw exception("class: MyParser\n funtion:number_parse\n reason:invalid formation");
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}
	}

	//整数
	if (json_str_[index_] == '0')
		index_++;

	else {
		index_++;
		while (isdigit(json_str_[index_]) > 0)
			index_++;
	}

	//小数
	if (json_str_[index_] == '.') {
		index_++;
		try {
			if (isdigit(json_str_[index_]) == 0)
				throw exception("class: MyParser\n funtion:number_parse\n reason:invalid formation");
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}
		while (isdigit(json_str_[index_]) > 0)
			index_++;
	}
	return MyJson(std::stod(json_str_.substr(pos_intital, index_ - pos_intital + 1)));

}

MyJson MyParser::string_parse() {
	index_++;
	size_t pos_intitial = index_;
	while (true)
	{
		try {
			if (index_ >= json_str_.size()) {
				throw exception("class:MyParser\n function:string_parse\n reason:out_of_range");
			}
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}

		if (json_str_[index_] == '"')
		{
			break;
		}

		// The usual case: non-escaped characters
		if (json_str_[index_] == '\\')
		{
			index_++;
			switch (json_str_[index_]){
			case 'b':
			case 't':
			case 'n':
			case 'f':
			case 'r':
			case '"':
			case '\\':
				break;
			default:
				break;
			}
		}
		index_++;
	}
	return MyJson(json_str_.substr(pos_intitial, index_ - pos_intitial));
}

MyJson MyParser::list_parse() {
	vector<MyJson> result;
	index_++;
	get_next_token();
	if (json_str_[index_] == ']')
		return MyJson(result);
	while (true)
	{
		MyJson m = parse();
		if (m.type() == "string" || m.type() == "list" || m.type() == "map")
			index_++;
		result.push_back(m);
		get_next_token();
		if (json_str_[index_] == ']')
		{
			break;
		}
		try {
			if (json_str_[index_] != ',')
			{
				throw exception("class: MyParser\n funtion:list_parse\n reason:invalid formation");
			}
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}

		index_++;
	}
	MyJson result_ = MyJson(result);
	return result_;
}

MyJson MyParser::map_parse() {
	index_++;
	map<string, MyJson> result;
	get_next_token();
	if (json_str_[index_] == '}')
	{
		return MyJson(result);
	}
	while (true)
	{
		get_next_token();
		try {
			if (json_str_[index_] != '"')
			{
				throw exception("class: MyParser\n funtion:map_parse\n reason:invalid formation");
			}
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}

		string key = string_parse().value().value_string;
		index_++;
		get_next_token();
		try {
			if (json_str_[index_] != ':')
			{
				throw exception("class: MyParser\n funtion:map_parse\n reason:invalid formation");
			}
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}
		index_++;
		MyJson m = parse();
		if (m.type() == "string" || m.type() == "list" || m.type() == "map")
			index_++;
		result.insert({key,m});
		get_next_token();
		if (json_str_[index_] == '}')
		{
			break;
		}
		try {
			if (json_str_[index_] != ',')
			{
				throw exception("class: MyParser\n funtion:map_parse\n reason:invalid formation");
			}
		}
		catch (exception e) {
			cout << e.what() << endl << "行数" << __LINE__ << endl;
			exit(1);
		}
		index_++;
	}
	return MyJson(result);
}