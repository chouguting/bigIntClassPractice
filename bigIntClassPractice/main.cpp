#include <malloc.h>
#include <iostream>
#include <string.h>
#include "bigInt.h"
#include <windows.h>

using namespace std;


void BigInt::PrintValue()
{
	if (_numDigits == 0)
		cout << '0';
	else
		for (int i = _numDigits - 1; i >= 0; i--)
			cout << _digits[i];
	cout << endl;
}

void BigInt::Zero()
{
	for (int i = 0; i < _capacity; i++)
		_digits[i] = 0;
	_numDigits = 0;
}

BigInt::BigInt()
{
	// default constructor, value = 0, capacity = 100, numDigits = 0
	_capacity = 100;
	_digits = static_cast<int*>(malloc(_capacity * sizeof(int)));
	Zero();
}

BigInt::~BigInt()
{
	// destructor
	free(_digits);
	_digits = nullptr;
	_capacity = _numDigits = 0;
}

//////////////////////////////////////////////////////////////////////////////
// BUG
//////////////////////////////////////////////////////////////////////////////

BigInt::BigInt(const char* const s, const int size)
{
	// assign a string 
	_digits = nullptr; // Array: 儲存整數
	_capacity = _numDigits = 0; // Array 大小 // 整數位數

	int strSize = strlen(s);
	if (strSize > size)
		return;

	_capacity = size;
	_digits = static_cast<int*>(malloc(_capacity * sizeof(int)));
	Zero();

	for (_numDigits = 0; _numDigits < strSize; _numDigits++)
	{
		if (s[_numDigits] < '0' || s[_numDigits] > '9')
			break;
		_digits[_numDigits] = s[strSize - _numDigits - 1] - 48;
	}


	while(_digits[_numDigits-1]==0)
	{
		_numDigits = _numDigits - 1;
	}
}


// assign an integer value and capacity = size
BigInt::BigInt(const int value, const int size)
{
	_numDigits = 0;
	int digitNum=0;

	int numTemp = value;
	int numTemp2 = value;
	while (numTemp > 0)
	{
		digitNum++;
		numTemp = numTemp / 10;
	}
	
	if(digitNum >size)
	{
		_capacity = digitNum;
	}else
	{
		_capacity = size;
	}
	_digits = static_cast<int*>(malloc(_capacity * sizeof(int))); // Array: 儲存整數
	
	Zero();

	_numDigits = digitNum;

	

	
	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = numTemp2 % 10;
		numTemp2 = numTemp2 / 10;
	}
}

// copy constructor
BigInt::BigInt(const BigInt& bi)
{
	_capacity = bi._capacity;
	_digits = static_cast<int*>(malloc(_capacity * sizeof(int))); // Array: 儲存整數
	Zero();
	_numDigits = bi._numDigits;
	
	for (int i = 0; i < _numDigits; i++)
	{
		_digits[i] = bi._digits[i];
	}
}

void BigInt::Add(const int addNum)
{
	BigInt temp2(addNum);
	Add(temp2);
}

void BigInt::Add(const char* const addchar)
{
	
	BigInt temp = (addchar);
	Add(temp);
}


void BigInt::Add(const BigInt& bi)
{
	int biSize;
	if(bi._numDigits+1>=_capacity)
	{
		BigInt temp(*this);
		free(_digits);
		_digits = (int*)malloc(sizeof(int) * (bi._numDigits + 1));
		_capacity = bi._numDigits + 1;
		Zero();
		_numDigits = 0;
		
		Add(temp);
	}

	
	if (bi._numDigits > _numDigits)
	{
		_numDigits = bi._numDigits;
		biSize = bi._numDigits;
	}else
	{
		biSize = _numDigits;
	}
	 
	
	

	int carry = 0;
	int i=0;
	while (i<biSize)
	{
		int addedThisRound;
		if(i<bi._numDigits)
		{
			addedThisRound = _digits[i] + bi._digits[i] + carry;
		}else
		{
			addedThisRound = _digits[i] + 0 + carry;
		}
		
		if (addedThisRound > 9)
		{
			addedThisRound = addedThisRound - 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		_digits[i] = addedThisRound;
		i++;
	}

	if (carry == 1)
	{
		if(i>=_capacity)
		{
			BigInt temp(*this);
			free(_digits);
			_digits = (int*)malloc(sizeof(int) * (i + 1));
			_capacity = i + 1;
			Zero();
			Add(temp);
		}
		
		_numDigits++;
		_digits[i] = _digits[i]+1;
	}
	
	
}


void main()
{
	//加法的計算邏輯可以用人計算的方法 
	BigInt x, y("1234"), z("000009876054321");

	cout << "x=";
	x.PrintValue();
	cout << "y=";
	y.PrintValue();
	cout << "z=";
	z.PrintValue();

	cout << "y+z=";
	y.Add(z);
	y.PrintValue();


	cout << "i=";
	BigInt i(444, 2);
	i.PrintValue();


	

	
	

	
	cout << "j=i=";
	BigInt j(i);
	j.PrintValue( );

	

	cout << "i+78=";
	i.Add(78);
	i.PrintValue( );

	cout << "i+98765=";
	i.Add("98765");
	i.PrintValue( );


	
	cout << "\tI:";
	i.PrintValue();
	cout << "\tJ:";
	j.PrintValue();
	cout << "i+j=";
	i.Add(j);
	i.PrintValue( );


	system("pause");
}
