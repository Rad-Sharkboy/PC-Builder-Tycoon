#include "CPU.h"

CPU::CPU(string n,int p,int bp):Component(n,p,bp){}
int CPU::calculatePerformance(){
	return basePerformance*2; //Differennt formula for cpus
}