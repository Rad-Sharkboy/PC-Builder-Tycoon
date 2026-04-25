#ifndef RAM_H
#define RAM_H
#include "Component.h"
class RAM:public Component{
public:
	RAM(string,int,int);
	int calculatePerformance();
};
#endif