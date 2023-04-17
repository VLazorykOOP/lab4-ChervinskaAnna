#include "Lab4.h"
#define _USE_MATH_DEFINES 
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
using namespace std;
typedef unsigned int uint;

enum State {
	NoErrors,
	NoMemori, //не вистачає пам'яті
	NotInRange, //виходить за межі множини
	InvalidNumber // ініціалізація числом
};

static string SetStateStrings[] = { "NoErrors", "NoMemori", "NotInRange", "InvalidNumber" };

class  VectorULong {
	unsigned long state, size;

public:
	 long* v;
	VectorULong() {
		v = (long*)calloc(1, sizeof(long));
		v[0] = 0;
		size = 1;
	}

	VectorULong(unsigned long SizeVec) {
		v = (long*)calloc(SizeVec, sizeof(long));
		for (int i = 0; i < SizeVec; i++) {
			v[i] = 0;
		}
		size = SizeVec;
	}

	VectorULong(unsigned long SizeVec, long value) {
		v = (long*)calloc(SizeVec, sizeof(long));
		for (int i = 0; i < SizeVec; i++) {
			v[i] = value;
		}
		size = SizeVec;
	}

	VectorULong(const VectorULong& ref_Point)
	{
		this->state = ref_Point.state;
		this->size = ref_Point.size;

		this->v = (long*)calloc(size, sizeof(long));
		for (int i = 0; i < size; i++) {
			this->v[i] = ref_Point.v[i];
		}
	}

	~VectorULong() {
		free(v);
	}

	VectorULong& operator++(const int param) {
		for (int i = 0; i < size; i++) {
			this->v[i]++;
		}
		return *this;
	}

	VectorULong& operator--(const int param) {
		for (int i = 0; i < size; i++) {
			this->v[i]--;
		}
		return *this;
	}

	bool operator!() {
		return size != 0;
	}


	VectorULong& operator~() {
		for (int i = 0; i < size; i++) {
			this->v[i] = ~v[i];
		}
		return *this;
	}

	VectorULong& operator-() {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] * (-1);
		}
		return *this;
	}

	VectorULong& operator=(VectorULong& a) {
		this->size = a.size;
		free(v);
		v = (long*)calloc(a.size, sizeof(long));
		for (int i = 0; i < a.size; i++) {
			this->v[i] = a.v[i];
		}
		return *this;
	}

	VectorULong& operator+=(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] + a.v[i];
			}
			else if (i < this->size) {
			v_temp[i] = this->v[i];
			}
			else {
				v_temp[i]= a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}




	VectorULong& operator-=(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] - a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = 0;
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}

	VectorULong& operator*=(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] * value;
		}
		return *this;
	}

	VectorULong& operator/=(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] / value;
		}
		return *this;
	}

	VectorULong& operator%=(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] % value;
		}
		return *this;
	}

	VectorULong& operator|=(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] | a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}

	VectorULong& operator^=(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] ^ a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;

	}

	VectorULong& operator&=(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] & a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;

	}

	VectorULong& operator+(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] + a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = a.v[i];
			}
		}


		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}

	VectorULong& operator-(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] - a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = 0;
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}

	VectorULong& operator*(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] * value;
		}
		return *this;
	}

	VectorULong& operator/(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] / value;
		}
		return *this;
	}

	VectorULong& operator%(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] % value;
		}
		return *this;
	}


	VectorULong& operator|(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] | a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}

	VectorULong& operator^(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] ^ a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;

	}

	VectorULong& operator&(VectorULong& a) {
		long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (long*)calloc(new_size, sizeof(long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] & a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;

	}

	VectorULong& operator>>(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] >> value ;
		}
		return *this;
	}

	VectorULong& operator<<(long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] << value;
		}
		return *this;
	}

	bool operator==(VectorULong& a) {

		if (this->size != a.size) {
			return false;
		}

		for (int i = 0; i < size; i++){
			if (this->v[i] != a.v[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(VectorULong& a) {
		if (this->size != a.size) {
			return true;
		}
		for (int i = 0; i < size; i++){
			if (this->v[i] != a.v[i]) {
				return true;
			}
		}
		return false;
	}

	long& operator[](const int index) {
		if (size < index) {
			state = NotInRange;
			return v[size-1];
		}
		else {
			return v[index];
		}
	}
	
	long GetObjectWeight() {
		unsigned long j = 0;
		for (int i = 0; i < size; i++) {
			j = j + (v[i] * v[i]);
		}
		return j;
	}

	bool operator>(VectorULong& a) {
		return a.GetObjectWeight() > this->GetObjectWeight();
	}

	bool operator>=(VectorULong& a) {
		return a.GetObjectWeight() >= this->GetObjectWeight();
	}

	bool operator<(VectorULong& a) {
		return a.GetObjectWeight() < this->GetObjectWeight();
	}

	bool operator<=(VectorULong & a) {
		return a.GetObjectWeight() <= this->GetObjectWeight();
	}

	void printInfo()
	{

		cout << "Size =" << size << " ";
		cout << "State=" << SetStateStrings[state] << " ";
		for (int i = 0; i < size; i++) {
			cout << "[" << v[i] << "] ";
		}

		cout << endl;
	}
};

void Unari() {
	VectorULong obj1(5, 4);
	obj1.v[1]=6;
	obj1.printInfo();
	cout << "Test ++" << endl;
	obj1++; 
	obj1.printInfo();
	cout << "Test --" << endl;
	obj1--;
	obj1.printInfo();
	cout << "Test !" << endl;
	cout << "Result " << !obj1 << endl;
	cout << "Test ! if size = 0" << endl;
	VectorULong obj2(0);
	cout <<"Result "<< !obj2 << endl;

	VectorULong obj3(5, 4);
	obj3.v[1] = 6;
	obj3.printInfo();
	cout << "Test ~" << endl;
    ~obj3;
	obj3.printInfo();
	cout << "Test -" << endl;
	VectorULong obj6(5, 4);
	obj6.v[1] = 6;
	VectorULong obj5;
	obj6.printInfo();
	obj5= -obj6;
	obj6.printInfo();

}

void Prisvoena(){

cout << "Test =" << endl;
	VectorULong obj7(5, 4);
	obj7.v[1] = 6;
	VectorULong obj8(6, 3);
	obj8.v[1] = 5;
	cout << "Before" << endl;
	obj7.printInfo();
	obj8.printInfo();
	cout << "After" << endl;
	obj8 = obj7;
	obj7.printInfo();
	obj8.printInfo();

	cout << "Test +=" << endl;
	VectorULong obj3(6, 7);
	obj3.v[1] = 5;
	VectorULong obj4(6, 3);
	obj4.v[1] = 5;
	cout << "Before" << endl;
	obj3.printInfo();
	cout << "After" << endl;
	obj3 += obj4;
	obj3.printInfo();

	cout << "Test -=" << endl;
	VectorULong obj5(6, 2);
	obj5.v[1] = 8;
	VectorULong obj6(6, 4);
	obj6.v[1] = 1;
	cout << "Before" << endl;
	obj5.printInfo();
	cout << "After" << endl;
	obj5 -= obj6;
	obj5.printInfo();

	cout << "Test *=" << endl;
	VectorULong obj1(4, 7);
	obj1.v[1] = 4;
	cout << "Before" << endl;
	obj1.printInfo();
	cout << "After" << endl;
	obj1 *= 8;
	obj1.printInfo();

	cout << "Test /=" << endl;
	VectorULong obj2(7, 2);
	obj2.v[1] = 4;
	cout << "Before" << endl;
	obj2.printInfo();
	cout << "After" << endl;
	obj2 /= 2;
	obj2.printInfo();

	cout << "Test %=" << endl;
	VectorULong obj9(4, 7);
	obj9.v[1] = 4;
	cout << "Before" << endl;
	obj9.printInfo();
	cout << "After" << endl;
	obj9 %= 4;
	obj9.printInfo();

	cout << "Test |=" << endl;
	VectorULong obj10(3, 5);
	obj10.v[1] = 9;
	VectorULong obj11(7, 2);
	obj11.v[1] = 9;
	cout << "Before" << endl;
	obj10.printInfo();
	cout << "After" << endl;
	obj10 |= obj11;
	obj10.printInfo();

	cout << "Test ^=" << endl;
	VectorULong obj12(6, 2);
	obj12.v[1] = 8;
	VectorULong obj13(6, 4);
	obj13.v[1] = 1;
	cout << "Before" << endl;
	obj12.printInfo();
	cout << "After" << endl;
	obj12 ^= obj13;
	obj12.printInfo();

	cout << "Test &=" << endl;
	VectorULong obj14(6, 2);
	obj14.v[1] = 8;
	cout << "Before" << endl;
	obj14.printInfo();
	cout << "After" << endl;
	obj14 &= obj14;
	obj14.printInfo();
}

void Arithmetic() {
	cout << "Test +" << endl;
	VectorULong obj5(6, 7);
	obj5.v[1] = 5;
	VectorULong obj4(6, 3);
	obj4.v[1] = 5;
	cout << "Before" << endl;
	obj4.printInfo();
	obj5.printInfo();
	VectorULong obj3;
	cout << "After" << endl;
	obj3= obj4+ obj5;
	obj3.printInfo();

	cout << "Test -" << endl;
	VectorULong obj1(5, 7);
	obj1.v[1] = 4;
	VectorULong obj2(4, 3);
	obj2.v[1] = 5;
	cout << "Before" << endl;
	obj1.printInfo();
	obj2.printInfo();
	VectorULong obj6;
	cout << "After" << endl;
	obj6 = obj1 - obj2;
	obj6.printInfo();

	cout << "Test *" << endl;
	VectorULong obj7(4, 7);
	obj7.v[1] = 4;
	cout << "Before" << endl;
	obj7.printInfo();
	cout << "After" << endl;
	VectorULong obj8;
	obj8 = obj7 * 5;
	obj8.printInfo();

	cout << "Test /" << endl;
	VectorULong obj10(3, 9);
	obj10.v[1] = 3;
	cout << "Before" << endl;
	obj10.printInfo();
	cout << "After" << endl;
	VectorULong obj11;
	obj11 = obj10 / 3;
	obj11.printInfo();

	cout << "Test %" << endl;
	VectorULong obj9(6, 8);
	obj9.v[1] = 4;
	cout << "Before" << endl;
	obj9.printInfo();
	cout << "After" << endl;
	VectorULong obj12;
	obj12 = obj9 % 3;
	obj12.printInfo();
}

void Pobitovi() {
	cout << "Test |" << endl;
	VectorULong obj1(5, 7);
	obj1.v[1] = 4;
	VectorULong obj2(3, 4);
	obj2.v[1] = 8;
	cout << "Before" << endl;
	obj1.printInfo();
	obj2.printInfo();
	VectorULong obj3;
	cout << "After" << endl;
	obj3 = obj1 | obj2;
	obj3.printInfo();

	cout << "Test ^" << endl;
	VectorULong obj4(5, 4);
	obj4.v[1] = 3;
	VectorULong obj5(4, 3);
	obj5.v[1] = 5;
	cout << "Before" << endl;
	obj4.printInfo();
	obj5.printInfo();
	VectorULong obj6;
	cout << "After" << endl;
	obj6 = obj4 ^ obj5;
	obj6.printInfo();

	cout << "Test &" << endl;
	VectorULong obj7(7, 8);
	obj7.v[1] = 6;
	VectorULong obj8(6, 9);
	obj8.v[1] = 3;
	cout << "Before" << endl;
	obj7.printInfo();
	obj8.printInfo();
	VectorULong obj9;
	cout << "After" << endl;
	obj9 = obj7 & obj8;
	obj9.printInfo();
}

void Operation() {
	cout << "Test >>" << endl;
	VectorULong obj7(4, 7);
	obj7.v[1] = 4;
	cout << "Before" << endl;
	obj7.printInfo();
	cout << "After" << endl;
	VectorULong obj8;
	obj8 = obj7 >> 5;
	obj8.printInfo();

	cout << "Test <<" << endl;
	VectorULong obj9(6, 8);
	obj9.v[1] = 4;
	cout << "Before" << endl;
	obj9.printInfo();
	cout << "After" << endl;
	VectorULong obj12;
	obj12 = obj9 << 3;
	obj12.printInfo();

	cout << "Test ==" << endl;
	VectorULong obj1(5, 4);
	obj1.v[1] = 6;
	VectorULong obj2(6, 3);
	obj2.v[1] = 5;
	cout << "Result " << (obj1 == obj2) << endl;

	cout << "Test !=" << endl;
	VectorULong obj3(3, 4);
	obj3.v[1] = 8;
	VectorULong obj4(6, 3);
	obj4.v[1] = 7;
	cout << "Result " << (obj3 != obj4) << endl;

	cout << "Test []" << endl;
	VectorULong obj13(6, 3);
	obj13[1] = 5;
	obj13.printInfo();


}

void Comparition() {
	cout << "Test >" << endl;
	VectorULong obj3(3, 4);
	obj3.v[1] = 8;
	VectorULong obj4(6, 3);
	obj4.v[1] = 7;
	cout << "Result " << (obj3 > obj4) << endl;

	cout << "Test >=" << endl;
	VectorULong obj1(5, 4);
	obj1.v[1] = 6;
	VectorULong obj2(6, 3);
	obj2.v[1] = 5;
	cout << "Result " << (obj1 >= obj2) << endl;

	cout << "Test <" << endl;
	VectorULong obj5(4, 6);
	obj5.v[1] = 2;
	VectorULong obj6(5, 8);
	obj6.v[1] = 1;
	cout << "Result " << (obj5 < obj6) << endl;

	cout << "Test <=" << endl;
	VectorULong obj7(3, 4);
	obj7.v[1] = 8;
	VectorULong obj8(3, 4);
	obj8.v[1] = 8;
	cout << "Result " << (obj7 <= obj8) << endl;

}

void Errors() {
	cout << "Test []" << endl;
	VectorULong obj13(6, 3);
	obj13[100] = 5;
	obj13.printInfo();
}

void Task1() {
	char ch;
	do {
		cout << "\nSelect operation: \n";
		cout << "    1.  Unarni operation \n";
		cout << "    2.  Operation Prisvoena \n";
		cout << "    3.  Arithmetic binary\n";
		cout << "    4.  Pobitovi operation\n";
		cout << "    5.  Operation ==,!=,[]\n";
		cout << "    6.  Operation comparition (>, >=, <,<= ) \n";
		cout << "    7.  Test Errors \n";
		cout << "    8.  Exit \n";

		ch = _getch();
		switch (ch) {
		case '1':  Unari(); break;
		case '2': Prisvoena(); break;
		case '3': Arithmetic(); break;
		case '4': Pobitovi(); break;
		case '5': Operation(); break;
		case '6': Comparition(); break;
		case '7': Errors(); break;
		}
	} while (ch != '8');
}

//
//int lab4() {
//	char ch;
//	do {
//		cout << "\nSelect Task: \n";
//		cout << "    1.  Task1 \n";
//		cout << "    2.  Task2 \n";
//		cout << "    3.  Exit \n";
//
//		ch = _getch();
//		switch (ch) {
//		case '1':  Task1(); break;
//	    case '2': Task2(); break;
//		}
//	} while (ch != '3');
//	return 0;
//}
