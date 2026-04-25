#include "Component.h"

Component::Component(string n,int p,int b):name(n),price(p),basePerformance(b){}
string Component::getName(){return name;}
int Component::getPrice(){return price;}
Component::~Component(){}