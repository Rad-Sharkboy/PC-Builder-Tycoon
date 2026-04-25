#include "GPU.h"

GPU::GPU(string n,int p,int bp):Component(n,p,bp){}
int GPU::calculatePerformance(){
	return basePerformance*3;
}