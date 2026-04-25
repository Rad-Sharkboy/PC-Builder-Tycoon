#ifndef CPU_H
#define CPU_h
#include "Component.h"
class CPU:public Component{
public:
	CPU(string,int,int);
	int calculatePerformance();
};
#endif