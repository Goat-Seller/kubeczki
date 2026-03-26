#pragma once
#include <iostream>
#include <vector>
class Substance
{
	std::string name;
	double ro; // [kg/m3]

public:
	Substance(std::string name, double ro);

	std::string get_name();
	double get_ro();
};

extern std::vector<Substance>menu;