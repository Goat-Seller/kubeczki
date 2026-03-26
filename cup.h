#pragma once
#include <iostream>
#include <vector>

#include "substance.h"

class  Cup
{
	std::vector<Substance> substances;
	std::vector<double> volumes;

public:
	void add(Substance substance, double volume_in_ml);
	void add(std::string name, double volume_in_ml);
	void set_vol_percentage(std::string name, double percentage);
	void set_mass_percentage(std::string name, double percentage);
	void show();
	void pour_over(Cup& other);
private:
	void print_coe_vol();
	void print_coe_mass();
	double sum_volumes();
	double sum_mass();
	int get_vol_id(std::string name);
	int get_substance_id(std::string name);
	double get_volume_from_name(std::string name);
};
