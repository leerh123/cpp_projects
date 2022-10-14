# 接口风格与标准库一致的轻型json解释器

# API接口

​	MyJson类有两个成员：type\_和value\_。type_是一个Type类型枚举，里面存有null\_json、bool\_json、number\_json、string\_json、list\_json、map\_json几种类型。

​	对于MyJson类，构造函数有以下几种。

```c++
	  
	//指定类型
	//传入Type枚举中的参数
	explicit MyJson(Type);
	//_type的值可以为"null","bool","number","string","list"，"map"。后面的construction建议传入true
	explicit MyJson(string _type,bool construction);

	
	//初始化为null_json类型
	explicit MyJson();
	//初始化为bool_json类型
	explicit MyJson(bool);
	//初始化为number_json类型
	explicit MyJson(short);
	explicit MyJson(int);
	explicit MyJson(float);
	explicit MyJson(double);
	explicit MyJson(long double);
	explicit MyJson(long int);
	explicit MyJson(long long int);
	explicit MyJson(unsigned int);
	explicit MyJson(unsigned long int);
	//初始化为string_json类型
	explicit MyJson(const string&);
	explicit MyJson(const char*);
	//初始化为list_json类型
	explicit MyJson(const list<MyJson>&);
	explicit MyJson(const vector<MyJson>&);
	//初始化为map_list类型
	explicit MyJson(const map<string,MyJson>&);

```

​	对于parse解析函数，声明如下

```c++
//传入一个符合json格式的字符串
void parse(const string&);
```

​	标准库风格的接口

```c++
	//格式化输出
	ostream& operator<<(ostream& os, const MyJson& stu);
	//用下标或者key获取相应的对象
	MyJson& operator[](size_t);
	MyJson& operator[](string);
	MyJson& operator[](const MyJson&);
	//赋值运算
	MyJson& operator=(const MyJson&);
	//删除操作(list_json与map_json有效)
	size_t erase(string);
	iter_list erase(iter_list);
	iter_map erase(iter_map);
	iter_list erase(iter_list, iter_list);
	iter_map erase(iter_map, iter_map);
	//find(map_json有效)
	iter_map find(string);
	//insert(list_json与map_json有效)
	pair<iter_map, bool>  insert(pair<string, MyJson>);
	iter_list insert(iter_list, const MyJson&);
	void push_back(const MyJson&);
	//iterator(list_json与map_json有效)
	iter_list begin_list();
	iter_list end_list();
	iter_map begin_map();
	iter_map end_map();
```

​	其他接口

```c++
	//返回值为"null","bool","number","string","list","map"中的一种
	string type();
	//Value是一个struct，格式如下
	//struct Value {
	//bool value_bool;
	//long double value_number;
	//string value_string;
	//vector<MyJson> value_list;
	//map<string, MyJson> value_map;
	//};
	//需要注意的是，只有对于一种类型，只有对应类型的数据有实际意义，其他数据都是默认初始化的值。
	Value value();
```



# 接口调用

1. 初始化MyJson类
2. 调用parse进行解析
3. 使用其他成员函数进行相关操作



```c++
//示例程序
int main() {
    MyJson p;
    p.parse("{\"hellworld\":[0,1,2,3]}");//json-type string
    cout << p << endl;
}
```



# 代码思路

​	代码使用两个类，MyParser和MyJson。其中MyParser负责解析工作，MyJson负责接口实现。

​	主要思想为递归，认为整个json字符串为MyJson类型，json字符串的元素(数组的元素，字典的关键字和值等)也为MyJson类型。增强了代码的简洁性和可读性。