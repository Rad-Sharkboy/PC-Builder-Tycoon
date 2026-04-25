#ifndef PC_H
#define PC_H
#include "Component.h"
class PC{
	Component* parts[10];
	int count;
public:
	PC();
	void addPart(Component*);
	int calculateCost();
	int calculateTotalPerformance();
	~PC();
};
#endif