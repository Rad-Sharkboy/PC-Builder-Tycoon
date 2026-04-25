#include "PC.h"

PC::PC(){count=0;}
void PC::addPart(Component* c){
	if(count<10){
		parts[count++]=c;
	}
}
int PC::calculateCost(){
	int total=0;

	for(int i=0;i<count;i++){
		total+=parts[i]->getPrice();
	}

	return total;
}
int PC::calculateTotalPerformance(){
	int total=0;

	for(int i=0;i<count;i++){
		total+=parts[i]->calculatePerformance();
	}

	return total;
}
PC::~PC(){
	for(int i=0;i<count;i++){
		delete parts[i];
	}
}