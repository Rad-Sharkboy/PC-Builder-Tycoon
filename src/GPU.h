#ifndef GPU_H
#define GPU_H
#include "Component.h"
class GPU:public Component{
public:
	GPU(string,int,int);
	int calculatePerformance();
};
#endif