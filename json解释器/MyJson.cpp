#include"MyJson.h"
#include"MyParser.h"
MyJson::MyJson() :type_(null_json) {}

MyJson::MyJson(Type _type) : type_(_type) {}

MyJson::MyJson(string _type, bool construction) {
	try {
		if (_type == "null")
			type_ = null_json;
		else if (_type == "bool")
			type_ = bool_json;
		else if (_type == "number")
			type_ = number_json;
		else if (_type == "string")
			type_ = string_json;

		else if (_type == "list")
			type_ = list_json;

		else if (_type == "map")
			type_ = map_json;

		else
			throw exception("class:MyJson\n funtion:construction function\n reason:invalid type");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
}

MyJson::MyJson(bool _value) :type_(bool_json) {
	value_.value_bool = _value;
}

MyJson::MyJson(short _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(int _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(float _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(double _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(long double _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(long int _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(long long int _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(unsigned int _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}
MyJson::MyJson(unsigned long int _value) : type_(number_json) {
	value_.value_number = static_cast<long double> (_value);
}

MyJson::MyJson(const string& _value) : type_(string_json) {
	value_.value_string = _value;
}
MyJson::MyJson(const char* _value) : type_(string_json) {
	value_.value_string = _value;
}

MyJson::MyJson(const list<MyJson>& _value) : type_(list_json) {
	value_.value_list = vector<MyJson>(_value.begin(),_value.end());
}
MyJson::MyJson(const vector<MyJson>& _value) : type_(list_json) {
	value_.value_list = _value;
}

MyJson::MyJson(const map<string, MyJson>& _value) : type_(map_json) {
	value_.value_map = _value;
}

MyJson::~MyJson() {
}

ostream& operator<<(ostream& _os, const MyJson& _myjson) {
	switch (_myjson.type_) {
	case null_json:
		_os << "null" << flush;
		break;
	case bool_json:
		_os << (_myjson.value_.value_bool == true ? "true" : "false") << flush;
		break;
	case number_json:
		_os << _myjson.value_.value_number << flush;
		break;
	case string_json:
		_os << "\"" << _myjson.value_.value_string << "\"" << flush;
		break;
	case list_json:
		_os << "[" << flush;
		for (auto i = _myjson.value_.value_list.begin();i != _myjson.value_.value_list.end();i++){
			if (i != _myjson.value_.value_list.end() - 1)
				_os << *i << ',' << flush;
			else
				_os << *i << flush;
		}
		_os << "]" << flush;
		break;
	case map_json:
		_os << "{" << endl;
		auto end = _myjson.value_.value_map.end();
		end--;
		for (auto i = _myjson.value_.value_map.begin(); i != _myjson.value_.value_map.end(); i++) {
			if (i != end) {
				_os << "\t" << "\"" << i->first << "\" " << ": "
					<< i->second <<',' << endl;
			}
			else {
				_os << "\t" << "\"" << i->first << "\" " << ": "
					<< i->second  << endl;
			}
			
		}
		_os << endl;
		_os << "}" << flush;

	}
	return _os;
}

void MyJson::parse(const string& _str) {
	MyParser m(_str);
	*this = m.parse();
	
}

string MyJson::type() {
	string result;
	switch (type_) {
	case null_json:
		result = "null";
		break;
	case bool_json:
		result = "bool";
		break;
	case number_json:
		result = "number";
		break;
	case string_json:
		result = "string";
		break;
	case list_json:
		result = "list";
		break;
	case map_json:
		result = "map";
		break;
	}
	return result;
}

Value MyJson::value() {
	return value_;
}

MyJson& MyJson:: operator[](size_t _index) {
	try {
		if (type_ != list_json)
			throw exception("class:MyJson\n function:operator[]\n reason:type_error");
		if (_index >= value_.value_list.size())
			throw exception("class:MyJson\n function:operator[]\n reason:out_of_range");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return value_.value_list[_index];
}

MyJson& MyJson:: operator[](string _key) {
	try {
		if (type_ != map_json)
			throw exception("class:MyJson\n function:operator[]\n reason:type_error");
		if (value_.value_map.find(_key) == value_.value_map.end())
			throw exception("class:MyJson\n function:operator[]\n reason:out_of_range");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return value_.value_map[_key];
}

MyJson& MyJson::operator[](const MyJson& _m) {
	try {
		if (_m.type_ == number_json) {
			return operator[](_m.value_.value_number);
		}
		else if (_m.type_ == string_json) {
			return operator[](_m.value_.value_string);
		}
		else {
			throw exception("class:MyJson\n function:operator[]\n reason:type_error");
		}
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}

}

MyJson& MyJson::operator=(const MyJson& _m) {
	this->type_ = _m.type_;
	switch ( _m.type_)
	{
	case null_json:
		break;
	case bool_json:
		this->value_.value_bool = _m.value_.value_bool;
		break;
	case number_json:
		this->value_.value_number = _m.value_.value_number;
		break;
	case string_json:
		this->value_.value_string = _m.value_.value_string;
		break;
	case list_json:
		this->value_.value_list = _m.value_.value_list;
		break;
	case map_json:
		this->value_.value_map = _m.value_.value_map;
		break;
	default:
		break;
	}
	return *this;
}

size_t MyJson::erase(string _key) {
	try {
		if (this->type_ != map_json)
			throw exception("class :MyJson\n function : erase\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_map.erase(_key);
}

MyJson::iter_list MyJson::erase(iter_list _iter) {
	try{
	if (this->type_ != list_json)
		throw exception("class :MyJson\n function : erase\n reason : type_error");
}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_list.erase(_iter);

}

MyJson::iter_map MyJson::erase(iter_map _iter) {
	try {
		if (this->type_ != map_json)
			throw exception("class :MyJson\n function : erase\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_map.erase(_iter);
}

MyJson::iter_list MyJson::erase(iter_list _iter_begin, iter_list _iter_end) {
	try {
		if (this->type_ != list_json)
			throw exception("class :MyJson\n function : erase\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_list.erase(_iter_begin, _iter_end);
}

MyJson::iter_map MyJson::erase(iter_map _iter_begin, iter_map _iter_end) {
	try {
		if (this->type_ != map_json)
			throw exception("class :MyJson\n function : erase\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_map.erase(_iter_begin, _iter_end);
}

MyJson::iter_map MyJson::find(string _key) {
	try {
		if (this->type_ != map_json)
			throw exception("class :MyJson\n function : find\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_map.find(_key);
}

pair< MyJson::iter_map, bool> MyJson::insert(pair<string, MyJson> _pair) {
	try {
		if (this->type_ != map_json)
			throw exception("class :MyJson\n function : insert\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_map.insert(_pair);
}

MyJson::iter_list MyJson::insert(iter_list _iter, const MyJson& _arg) {
	try {
		if (this->type_ != list_json)
			throw exception("class :MyJson\n function : insert\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return this->value_.value_list.insert(_iter, _arg);
}

void MyJson::push_back(const MyJson& _arg) {
	try {
		if (this->type_ != list_json)
			throw exception("class :MyJson\n function : push_back\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	this->value_.value_list.push_back(_arg);
}


MyJson::iter_list MyJson::begin_list() {
	try {
		if (this->type_ != list_json)
			throw exception("class :MyJson\n function : begin_list\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return value_.value_list.begin();
}

MyJson::iter_list MyJson::end_list() {
	try {
		if (this->type_ != list_json)
			throw exception("class :MyJson\n function : end_list\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return value_.value_list.end();
}

MyJson::iter_map MyJson::begin_map() {
	try {
		if (this->type_ != map_json)
			throw exception("class :MyJson\n function : begin_map\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return value_.value_map.begin();
}

MyJson::iter_map MyJson::end_map() {
	try {
		if (this->type_ != map_json)
			throw exception("class :MyJson\n function : end_map\n reason : type_error");
	}
	catch (exception e) {
		cout << e.what() << endl << "行数" << __LINE__ << endl;
		exit(1);
	}
	return value_.value_map.end();
}
