#include "RAM.h"

RAM::RAM(string n,int p,int bp):Component(n,p,bp){}
int RAM::calculatePerformance(){
	return basePerformance+50;
}