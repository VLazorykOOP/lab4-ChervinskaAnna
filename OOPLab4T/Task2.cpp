#include "Task2.h"
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <fstream>
using namespace std;
typedef unsigned int uint;

struct Produkt
{
	string Name;

	bool operator==(Produkt& s)
	{
		return Name.compare(s.Name);
	}

};

ostream& operator<<(ostream& os, Produkt& n) {
	cout << n.Name;
	return os;
}
istream& operator>>(istream& iso, Produkt& n) {
	cin >> n.Name;
	return iso;
}

class Sclad
{
	uint* InventNumber;
	Produkt* Tovari;
	int MaxRec;
	int numRec;
	int State;
public:
	Sclad() :
		numRec(0), MaxRec(20) {
		InventNumber = new uint[20]; 
		Tovari = new Produkt[20];
	}

	~Sclad() {
		if (InventNumber != nullptr) delete[] InventNumber;
		if (Tovari != nullptr) delete[] Tovari;
	}

	Sclad(int size, uint* iN, Produkt* tm) : numRec(size), MaxRec(size + 5) {
		InventNumber = new uint[MaxRec]; Tovari = new Produkt[MaxRec];
		for (int i = 0; i < size; i++) {
			InventNumber[i] = iN[i];
			Tovari[i] = tm[i];
		}
	}

	void TableInvNum()
	{
		cout << " TableInvNum \n";
		for (int i = 0; i < numRec; i++) {
			cout << " InvNumber " << InventNumber[i] << " Name " << Tovari[i] << endl;
		}
	}

	uint operator[](Produkt& s) {
		uint InvN = 0;
		for (int i = 0; i < numRec; i++)
			if (Tovari[i] == s) return InventNumber[i];
		cout << " Error: item not found ";
		State = -1;
		return InvN;
	}

	Produkt operator[](uint& s) {
		Produkt Nname = Produkt();
		for (int i = 0; i < numRec; i++)
			if (InventNumber[i] == s) return Tovari[i];
		cout << " Error: item not found ";
		State = -1;
		return Nname;
	}

	void operator()(string Str) {
		bool t = false;
		for (int i = 0; i < numRec; i++)
			if (Tovari[i].Name.find(Str) != std::string::npos) {
				cout << InventNumber[i] << "\t";
				t = true;
			}
		if (t == false) cout << " Item not found \n";
		cout << endl;
		return;
	}
};


void Task2()
{
	cout << " End begin \n";
	uint InvNum[5] = { 5,2,8,4,3 };
	Produkt NameP[5] = { "Milk", "Bread", "Butter", "Ice", "Boxs"};
	Sclad dbase(5, InvNum, NameP);
	dbase.TableInvNum();
	string Name;
	cout << "Vvedite name product" << endl;
	cin >> Name;
	cout << "Result find" << endl;
	dbase(Name);
	uint Num;
	cout << "Vvedite invent number" << endl;
	cin >> Num;
	cout << "Result find" << endl;
	Produkt Presult;
	Presult = dbase[Num];
	cout <<"Number " << Num << " Product " << Presult << endl;

	
	/*Produkt r = { 10,30 }, ro;
	uint fli = 32;
	ro = dbase[fli];
	cout << " Test : uint operator[](MyTime&s) " << " time " << r << " light " << dbase[r] << endl;
	cout << " Flight with time : 9 to 11 \n";
	dbase(9, 11);
	cout << " End test \n";*/
}