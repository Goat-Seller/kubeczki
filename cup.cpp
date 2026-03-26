#include <iostream>
#include "substance.h"
#include "cup.h"
#include <vector>

using namespace std;

void Cup::add(Substance substance, double volume_in_ml) {
	int count = substances.size();
	int id = -1;
	for (int i = 0; i < count; i++)
	{
		if (substance.get_name() == substances[i].get_name()) id = get_vol_id(substance.get_name());
	}
	if (id > -1 && id < volumes.size())
	{
		volumes[id] += volume_in_ml / 1e6;
	}
	else {
		substances.push_back(substance);
		volumes.push_back(volume_in_ml / 1e6);
	}
	
	
}

void Cup::add(std::string name, double volume_in_ml)
{
	int _id = get_substance_id(name);

	if (_id >= 0)
	{
		this->add(menu[_id], volume_in_ml);
	};
}

void Cup::show()
{
	int count = substances.size();

	for (int i = 0; i < count; i++)
	{
		double mass = substances[i].get_ro() * volumes[i] * 1000; //gramy
		cout << substances[i].get_name()
			<< "; objetosc: " << volumes[i] * 1e6 << " ml"
			<< "; masa: " << mass << " g" << endl;
	}

	print_coe_vol();
	print_coe_mass();
	cout << endl;

}
void Cup::print_coe_vol() {
	cout << "\n Volume coe: ";
	double count_v = volumes.size();
	vector<double> sum_vol;
	
	double sum = sum_volumes();

	for (int j = 0; j < count_v; j++)
	{
		double count_sub = 0;
		sum_vol.push_back(volumes[j] * 1e6/ sum *100);
		cout << sum_vol[j] << "% ";
	}
}

void Cup::print_coe_mass() {
	cout << "\n Mass coe: ";
	double count_v = volumes.size();
	double count_s = substances.size();
	vector<double> mass;
	double sum_mass = 0;
	for (int i = 0; i < count_v; i++) {

		sum_mass += (substances[i].get_ro() * volumes[i] * 1000);
		
	}
	//cout << sum_mass << " ";

	for (int i = 0; i < count_v; i++)
	{
		double mas = substances[i].get_ro() * volumes[i] * 1000;
		mass.push_back(mas / sum_mass *100);
	cout << mass[i] << "% ";
	}
}

int Cup::get_substance_id(string name)
{
	int count = menu.size();
	int _id = -1;
	bool run = true;

	while (run)
	{
		_id += 1;
		string sub_name = menu[_id].get_name();

		if (sub_name == name) run = false;

		if ((run == true) && (_id + 1 == count))
		{
			cout << "Nie znaleziono plynu o podanej nazwie: \"" << name << "\"!\n\n";
			run = false;
			_id = -1;
		}
	}
	return _id;
}



void Cup::set_vol_percentage(string name, double percentage)
{
	int _id = get_substance_id(name);
	if (_id >= 0)
	{
		double sum = sum_volumes();
		int id = get_vol_id(name);
		if (id == -1)
		{
			add(name, 0);
		}
		id = get_vol_id(name);
		double vol = volumes[id] * 1e6;
		
		if (sum == 0)
		{
			cout << "Nie mozna ustawic procentu objetosci dla substancji, gdy masa calkowita jest rwwna 0!\n\n";
			return;
		}
		double to_add = (percentage/100* sum - vol)/(1 - percentage/100);
		cout << "to add: " << to_add << " " << endl;
		add(name, to_add);
	};
}



void Cup::set_mass_percentage(string name, double percentage)
{
	double sum = sum_mass();
	int id = get_vol_id(name);
	if (id == -1)
	{
		add(name, 0);
	}
	id = get_vol_id(name);
	double mass = substances[id].get_ro() * volumes[id] * 1000;
	if(sum == 0)
	{
		cout << "Nie można ustawić procentu masowego dla substancji, gdy masa całkowita jest równa 0!\n\n";
		return;
	}
	double to_add = (percentage / 100 * sum - mass) / (1 - percentage / 100);
	add(name, to_add);
}

int Cup::get_vol_id(string name)
{
	int count = substances.size();
	int _id = -1;
	bool run = count;

	while (run)
	{
		_id += 1;
		string sub_name = substances[_id].get_name();

		//cout << "sub name: " << sub_name << "id: " << _id << endl;
		if (sub_name == name) run = false;

		if ((run == true) && (_id + 1 == count))
		{
			run = false;
			_id = -1;
		}
	}
	return _id;
}

double Cup::get_volume_from_name(string name)
{
	int count = substances.size();
	if (count == 0) return 0;

	for (int i = 0; i < count; i++)
	{
		if (substances[i].get_name() == name) return volumes[i];
	}
	return 0;
}

double Cup::sum_volumes() {
	double count_v = volumes.size();
	if (count_v == 0) return 0;
	double sum = 0;
	for (int i = 0; i < count_v; i++) {
		sum += volumes[i] * 1e6;
	}
	return sum;
}
double Cup::sum_mass() {
	double count_v = volumes.size();
	if (count_v == 0) return 0;
	double sum = 0;
	for (int i = 0; i < count_v; i++) {
		sum += substances[i].get_ro() * volumes[i] * 1000;
	}
	return sum;
}

void Cup::pour_over(Cup& other) {
	int count_s = substances.size();
	for (int i = 0; i < count_s; i++)
	{
		other.add(substances[i].get_name(), volumes[i] * 1e6);
	}
	substances.clear();
	volumes.clear();
}