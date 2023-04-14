#include "Lab4.h"
#define _USE_MATH_DEFINES 
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
using namespace std;

enum State {
	NoErrors,
	NoMemori, //не вистачає пам'яті
	NotInRange, //виходить за межі множини
	InvalidNumber // ініціалізація числом
};

static string SetStateStrings[] = { "NoErrors", "NoMemori", "NotInRange", "InvalidNumber" };

class  VectorULong {
	unsigned long* v;
	unsigned long state, size;

public:
	VectorULong() {
		v = (unsigned long*)calloc(1, sizeof(unsigned long));
		v[0] = 0;

	}

	VectorULong(unsigned long SizeVec) {
		v = (unsigned long*)calloc(SizeVec, sizeof(unsigned long));
		for (int i = 0; i < SizeVec; i++) {
			v[i] = 0;
		}
	}

	VectorULong(unsigned long SizeVec, unsigned long value) {
		v = (unsigned long*)calloc(SizeVec, sizeof(unsigned long));
		for (int i = 0; i < SizeVec; i++) {
			v[i] = value;
		}
	}

	VectorULong(const VectorULong& ref_Point)
	{
		this->state = ref_Point.state;
		this->size = ref_Point.size;

		this->v = (unsigned long*)calloc(size, sizeof(unsigned long));
		for (int i = 0; i < size; i++) {
			this->v[i] = ref_Point.v[i];
		}
	}

	~VectorULong() {
		free(v);
	}



	int getCount(unsigned long value) {
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (v[i] == value) {
				count++;
			}
		}
		return count;
	}


	void printInfo()
	{

		cout << "State =" << state << " " << "Size =" << size << " ";
		for (int i = 0; i < size; i++) {
			cout << "[" << v[i] << "] ";
		}

		cout << endl;
		//cout << "Intersection operation " << endl;
		//cout << "Difference operation " << endl;
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

	VectorULong& operator-(const int param) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] * (-1);
		}
		return *this;
	}

	VectorULong& operator=(VectorULong& a) {
		this->size = a.size;
		free(v);
		v = (unsigned long*)calloc(a.size, sizeof(unsigned long));
		for (int i = 0; i < a.size; i++) {
			this->v[i] = a.v[i];
		}
		return *this;
	}

	VectorULong& operator+=(VectorULong& a) {
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] - a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = -a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}

	VectorULong& operator*=(unsigned long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] * value;
		}
		return *this;
	}

	VectorULong& operator/=(unsigned long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] / value;
		}
		return *this;
	}

	VectorULong& operator%=(unsigned long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] % value;
		}
		return *this;
	}

	VectorULong& operator|=(VectorULong& a) {
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
		for (int i = 0; i < new_size; i++) {
			if (i < this->size && i < a.size) {
				v_temp[i] = this->v[i] - a.v[i];
			}
			else if (i < this->size) {
				v_temp[i] = this->v[i];
			}
			else {
				v_temp[i] = -a.v[i];
			}
		}
		free(this->v);
		this->v = v_temp;
		this->size = new_size;
		return *this;
	}

	VectorULong& operator*(unsigned long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] * value;
		}
		return *this;
	}

	VectorULong& operator/(unsigned long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] / value;
		}
		return *this;
	}

	VectorULong& operator%(unsigned long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] % value;
		}
		return *this;
	}


	VectorULong& operator|(VectorULong& a) {
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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
		unsigned long* v_temp;
		unsigned long new_size = max(this->size, a.size);
		v_temp = (unsigned long*)calloc(new_size, sizeof(unsigned long));
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

	VectorULong& operator>>(unsigned long value) {
		for (int i = 0; i < size; i++) {
			this->v[i] = this->v[i] >> value ;
		}
		return *this;
	}

	VectorULong& operator<<(unsigned long value) {
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

	unsigned long& operator[](const int index) {
		if (size < index) {
			state = NotInRange;
			return v[size-1];
		}
		else {
			return v[index];
		}
	}
	
	unsigned long GetObjectWeight() {
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
};

int lab4() {
	cout << "Hello world!";
	return 0;
}