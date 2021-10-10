//
//  main.cpp
//  Hakkaton
//
//  Created by Alina Shlyakhta on 09.10.2021.
//

#include <iostream>
#include <vector>
using namespace std;
//#include<fstream>;

struct house {
public:
    int number;
    double koff;
    int cars;

    friend istream& operator >> (istream& in, house& Z);
    friend ostream& operator << (ostream& out,const house& Z);
    
    
    house();
    house(int num);
    
};

house :: house(){
    number = 0;
    koff=0;
    cars =0;
    
};

house :: house(int num){
    number = num;
        double dist, car;
        double distance_koff=0;
        cout << "Введите расстояние в метрах до пс и кол-во машин: ";
        cin >> dist >> car;
    cars = car;
        
    if (dist < 200) distance_koff = 1;
    if ((dist >= 200)&&(dist <500)) distance_koff = 0.7;
    if ((dist >= 500)&&(dist <1000)) distance_koff = 0.5;
    if ((dist >= 1000)&&(dist <2000)) distance_koff = 0.2;
    if (dist > 200) distance_koff = 0.001;
    
        
    koff = distance_koff * car;
    
};

istream& operator >> (istream& in, house& Z)
{
 
        cout << "   Ввeдите номер дома: ";
        cin >> Z.number;
   
    double dist, car;
    double distance_koff=0;
    cout << "   Введите расстояние в метрах до пс и кол-во машин: ";
    cin >> dist >> car;
    
    Z.cars = car;
if (dist < 200) distance_koff = 1;
if ((dist >= 200)&&(dist <500)) distance_koff = 0.7;
if ((dist >= 500)&&(dist <1000)) distance_koff = 0.5;
if ((dist >= 1000)&&(dist <2000)) distance_koff = 0.2;
if (dist > 200) distance_koff = 0.001;

    
Z.koff = distance_koff * car;
    
    return in;
}


ostream& operator << (ostream& out, const house& Z)
{
    cout << "Номер дома : " << Z.number << endl;
    
    return out;
}


struct district {
public:
    string name;
    double koff;
    vector <int> number_house; // ранжированный список
   
    
    
    district();
    district(string name,double koff);
    friend istream& operator >> (istream& in, district& Z);
    friend ostream& operator << (ostream& out,const district& Z);
    void find_percent_house();
    double return_koff(){return koff;}
    
};


district:: district (){
    
    name = "falled";
    koff = 0;
   // number_house(0)
};


district:: district (string n, double koff){
    
    name = n;
    double power, percent_power=0, installed;
    cout << "  Введите резерв в мВт и кол-во установленных зарядок в %";
    cin >> power >> installed;
    
    double koff_inst=0;
    
    if (installed < 30) koff_inst = 1;
    if ((installed >= 30)&&(installed <50)) koff_inst = 0.7;
    if ((installed >= 50)&&(installed <70)) koff_inst = 0.5;
    if ((installed >= 70)&&(installed <=100)) koff_inst = 0.2;
   
    
    if (power < 30) percent_power = 0.0005;
    if ((power >= 30)&&(power <50)) percent_power = 0.1;
    if ((power >= 50)&&(power <100)) percent_power = 0.3;
    if ((power >= 100)&&(power <150)) percent_power = 0.5;
    if ((power >= 150)&&(power <250)) percent_power = 0.7;
    if (power > 250) percent_power = 0.9;
  
    koff = percent_power*koff_inst; // домножить на колво людей в районе
    
    vector <int> house{0};
    number_house = house;
};

istream& operator >> (istream& in, district& Z)
{
    
   // ifstream fin("input.txt");
  //  ofstream fout("output.txt");

    cout << "Ввeдите название paйона : ";
    cin >> Z.name;
    
    double power, percent_power = 0, installed;
    cout << "  Введите резерв в мВт и кол-во установленных зарядок в %: ";
    cin >> power>>installed;
    
    double koff_inst=0;
    
    if (installed < 30) koff_inst = 1;
    if ((installed >= 30)&&(installed <50)) koff_inst = 0.7;
    if ((installed >= 50)&&(installed <70)) koff_inst = 0.5;
    if ((installed >= 70)&&(installed <=100)) koff_inst = 0.2;
    
    if (power < 30) percent_power = 0.0005;
    if ((power >= 30)&&(power <50)) percent_power = 0.1;
    if ((power >= 50)&&(power <100)) percent_power = 0.3;
    if ((power >= 100)&&(power <150)) percent_power = 0.5;
    if ((power >= 150)&&(power <250)) percent_power = 0.7;
    if (power > 250) percent_power = 0.9;
    
    Z.koff = percent_power*koff_inst;
   // fin.close();
  //  fout.close();
    
    return in;
}


ostream& operator << (ostream& out, const district& Z)

{
    cout << "Название района: " << Z.name << endl;
    cout << "Итоговый коэффициент: " << Z.koff << endl;
    return out;
}

void district:: find_percent_house(){
    
    int k;
    cout << "Введите количество домов в районе " << name << " : ";
    cin>> k;
    vector <house> vect;
    
    for (int i=0; i<k; i++){ // вводят house
        cout << "  Введите информацию о доме: "<< endl;
        house rast;
        cin >> rast;
        vect.push_back(rast);
        
        int kol=0;
        for (int i=0; i< vect.size(); i++){
            kol= kol+vect[i].cars;
        };
        
       // cout << "Kolvo " << kol;
    
           koff = koff*kol;
        
        for (int i = 0; i < vect.size() ; i++) {
           for (int j = 0; j < vect.size()-1; j++) {
             if (vect[j].koff > vect[j + 1].koff) {
               house b = vect[j]; // создали дополнительную переменную
               vect[j] = vect[j + 1]; // меняем местами
               vect[j + 1] = b; // значения элементов
             }
           }
         }
        
        vector <int> numb; // ранжир список
        
        
        for (int i = 0; i< vect.size();i++){
            numb.push_back(vect[i].number);
        };
   
    
        
    };
    
    
    
}


int main() {
    

    
    district R;
    
    district dist [3];
    
    for (int i=0; i<3; i++){
        
        cin >> dist[i];
    };
    
    //cin>> R;
    
    for (int i=0; i<3; i++){
        dist[i].find_percent_house();
    };
    
    
    
    for (int i = 0; i < 3 ; i++) {
       for (int j = 0; j < 3-1; j++) {
         if (dist[j].return_koff() < dist[j + 1].return_koff()) {
           district b = dist[j]; // создали дополнительную переменную
           dist[j] = dist[j + 1]; // меняем местами
           dist[j + 1] = b; // значения элементов
         }
       }
     }
    
    cout << "Полученный список районов отсортирован по первоочередности установки зарядок в районе. От района в первую очередь к району в последнюю очередь: "<< endl;
    
    for (int i=0; i<3; i++){
        cout<< dist[i];
    };
    
    
    return 0;
}
