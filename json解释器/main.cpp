#include <iostream>
#include <fstream>
#include <sstream>
#include<cctype>
#include<iomanip>
using namespace std;
#include "MyJson.h"
//Ê¾Àý³ÌÐò
int main() {
    MyJson p;
    p.parse("{\"hellworld\":[0,1,2,3]}");//json-type string
    cout << p << endl;
}
