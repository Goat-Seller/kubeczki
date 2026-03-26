#include <iostream>
#include <vector>
#include "substance.h"
#include "cup.h"

using namespace std;

int main()
{
	Cup kubek1;
	kubek1.set_vol_percentage("mleko", 40);
	//kubek1.add("woda", 100);
	//kubek1.add("krew", 100);
	kubek1.show();
	cout << endl;

	Cup kubek2;
	kubek2.add("mleko", 100);
	//kubek1.pour_over(kubek2);

	//kubek1.set_vol_percentage("mleko", 40);
	//kubek1.set_mass_percentage("mleko", 70);
	cout << "cup 1: \n";
	kubek1.show();

	cout << "cup 2: \n";
	kubek2.show();

}
