
#ifndef BIGINT_H
#define BIGINT_H

//俱计
class BigInt {
    // () default: ㏕﹚(100) 俱计
    // () ヴ種俱计


public:

    BigInt();								        	// default constructor, value = 0, capacity = 100, numDigits = 0
    BigInt(const int value, const int size = 100);		// assign an integer value and capacity = size
    BigInt(const char* const, const int size = 100);		// assign a string 
    BigInt(const BigInt&);				  				// copy constructor
    ~BigInt();												// destructor

    void Zero();
    void Add(const BigInt&);
    void Add(const int);
    void Add(const char* const);
    void PrintValue();

private:
    int* _digits;							 // Array: array–俱计计 俱计筁ㄓ璸衡ゑ耕よ獽(array材计 array材计 ...)
    int _capacity;               			 // Array  癘拘砰甧秖 
    int _numDigits;							 // 俱计Τ碭计
//		int sign;							 // 耎Θす砛タ璽计ㄏノ
};


#endif
