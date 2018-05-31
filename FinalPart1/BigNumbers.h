#pragma once
#include <vector>

using namespace std;

	class BigNumbers
	{
	private:
		//constant value to control maximum number of digits stored in bigNumber
		int const maxSize = 10000;

		//vector that can store int values
		vector<int> bigNumber = vector<int>();

		void setNumberSecret(vector<int> newNumber);

	public:
		//default constructor
		BigNumbers();

		//normal constructor
		BigNumbers(int startingValue);

		//copy constructor
		BigNumbers(const BigNumbers &copy);

		//a mutator function for the big number value being stored in bigNumber
		void setNumber(int newNumber);

		//a second  mutator function for the big number value being stored in bigNumber
		void setNumber2(BigNumbers newNumber);

		//an accessor function that returns the vector bigNumber
		vector<int> getNumber();

		//a function that prints out the contents of bigNumber
		void printNumber();

		//a clean-up function that removes any zeroes present before the actual value being stored in bigNumber
		void removeExtraneousZeroes();

		//operator overloads for +, -, *, /, and %
		BigNumbers operator + (const BigNumbers &);
		BigNumbers operator - (const BigNumbers &);
		BigNumbers operator * (const BigNumbers &);
		BigNumbers operator / (const BigNumbers &);
		BigNumbers operator % (const BigNumbers &);

	};