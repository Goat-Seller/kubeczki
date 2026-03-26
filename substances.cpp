#include <iostream>
#include "substance.h"
using namespace std;

Substance::Substance(string name, double ro)
{
	this->name = name;
	this->ro = ro;
}

string Substance::get_name()
{
	return name;
}

double Substance::get_ro()
{
	return ro;
}

vector<Substance> menu = {
	Substance{"woda", 997.8},
	Substance{"mleko", 1030.0},
	Substance{"oliwa", 920.0},
	Substance{"krew", 1050.0}
};