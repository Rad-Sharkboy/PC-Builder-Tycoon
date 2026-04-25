#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <string>

using namespace std;
class Component{
protected:
	string name;
	int price;
	int basePerformance;
public:
	Component(string,int,int);
	int getPrice();
	string getName();
	virtual int calculatePerformance()=0;
	virtual ~Component();
};
#endif