#include <iostream>
#include "substance.h"
#include "cup.h"
#include <vector>

using namespace std;

void Cup::add(Substance substance, double volume_in_ml) {
    int id = get_vol_id(substance.get_name());

    if (id != -1) {
        // Substance already in cup, just increase volume
        volumes[id] += volume_in_ml / 1e6;
    }
    else {
        // New substance
        substances.push_back(substance);
        volumes.push_back(volume_in_ml / 1e6);
    }
}

void Cup::add(std::string name, double volume_in_ml) {
    int _id = get_substance_id(name);
    if (_id >= 0) {
        this->add(menu[_id], volume_in_ml);
    }
}

void Cup::show() {
    int count = substances.size();
    if (count == 0) {
        cout << "Kubek jest pusty." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        double mass = substances[i].get_ro() * volumes[i] * 1000; // g
        cout << substances[i].get_name()
            << "; objetosc: " << volumes[i] * 1e6 << " ml"
            << "; masa: " << mass << " g" << endl;
    }

    print_coe_vol();
    print_coe_mass();
    cout << endl;
}

void Cup::print_coe_vol() {
    cout << "Volume coe: ";
    double sum = sum_volumes();

    if (sum <= 0) {
        for (double v : volumes) cout << "0% ";
    }
    else {
        for (double v : volumes) {
            cout << (v * 1e6 / sum) * 100 << "% ";
        }
    }
    cout << endl;
}

void Cup::print_coe_mass() {
    cout << "Mass coe: ";
    double total_mass = sum_mass();

    if (total_mass <= 0) {
        for (size_t i = 0; i < substances.size(); ++i) cout << "0% ";
    }
    else {
        for (int i = 0; i < substances.size(); i++) {
            double current_mass = substances[i].get_ro() * volumes[i] * 1000;
            cout << (current_mass / total_mass) * 100 << "% ";
        }
    }
    cout << endl;
}

int Cup::get_substance_id(string name) {
    for (int i = 0; i < menu.size(); i++) {
        if (menu[i].get_name() == name) return i;
    }
    cout << "Nie znaleziono plynu o podanej nazwie: \"" << name << "\"!\n";
    return -1;
}

int Cup::get_vol_id(string name) {
    for (int i = 0; i < substances.size(); i++) {
        if (substances[i].get_name() == name) return i;
    }
    return -1;
}

void Cup::set_vol_percentage(string name, double percentage) {
    if (percentage >= 100) {
        cout << "Procent musi byc mniejszy niz 100, aby dolewka miala sens.\n";
        return;
    }

    double sum = sum_volumes();
    if (sum <= 0) {
        cout << "Nie mozna ustawic procentu objetosci, gdy kubek jest pusty!\n";
        return;
    }

    int id = get_vol_id(name);
    double vol_current = (id == -1) ? 0 : volumes[id] * 1e6;

    // Formula: (V_current + V_add) / (Total + V_add) = P / 100
    double p_dec = percentage / 100.0;
    double to_add = (p_dec * sum - vol_current) / (1.0 - p_dec);

    if (to_add < 0) {
        cout << "Substancja juz przekracza zadany procent!\n";
        return;
    }

    add(name, to_add);
}

void Cup::set_mass_percentage(string name, double percentage) {
    if (percentage >= 100) return;

    double total_m = sum_mass();
    if (total_m <= 0) {
        cout << "Nie mozna ustawic procentu masowego, gdy kubek jest pusty!\n";
        return;
    }

    int id = get_vol_id(name);
    double mass_current = (id == -1) ? 0 : (substances[id].get_ro() * volumes[id] * 1000);

    double p_dec = percentage / 100.0;
    double mass_to_add = (p_dec * total_m - mass_current) / (1.0 - p_dec);

    if (mass_to_add > 0) {
        // Convert mass to volume: V = m / ro
        int menu_id = get_substance_id(name);
        double vol_to_add_ml = (mass_to_add / 1000.0) / (menu[menu_id].get_ro()) * 1e6;
        add(name, vol_to_add_ml);
    }
}

double Cup::sum_volumes() {
    double sum = 0;
    for (double v : volumes) sum += v * 1e6;
    return sum;
}

double Cup::sum_mass() {
    double sum = 0;
    for (int i = 0; i < substances.size(); i++) {
        sum += substances[i].get_ro() * volumes[i] * 1000;
    }
    return sum;
}

void Cup::pour_over(Cup& other) {
    for (int i = 0; i < substances.size(); i++) {
        other.add(substances[i], volumes[i] * 1e6);
    }
    substances.clear();
    volumes.clear();
}