#ifndef CPU_H
#define CPU_H
#include "Component.h"
class CPU:public Component{
public:
	CPU(string,int,int);
	int calculatePerformance();
};
#endif