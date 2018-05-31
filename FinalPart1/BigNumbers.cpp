#include "stdafx.h"
#include <cstdlib>
#include "BigNumbers.h"
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

	//default constructor
	//this constructor initalizes and sets bigNumber to be completely empty
	BigNumbers::BigNumbers()
	{
		bigNumber.push_back(0);
		bigNumber.clear();
	}

	//normal constructor
	//this constructor takes an int value, and breaks it down so that it can be stored digit by digit in bigNumber
	//the removeExtraneousZeroes function is then called
	BigNumbers::BigNumbers(int startingValue)
	{
		if (startingValue < 0)
		{
			startingValue = abs(startingValue);
		}
		bigNumber.push_back(0);
		bigNumber.clear();
		while (startingValue > 0)
		{
			int addValue = startingValue % 10;
			int newStart = startingValue / 10;
			bigNumber.push_back(addValue);
			startingValue = newStart;
		}
		removeExtraneousZeroes();
	}

	//copy constructor
	//this constructor takes another BigNumber object, and copies each digit of its own bigNumber into this one
	//the removeExtraneousZeroes function is then called
	BigNumbers::BigNumbers(const BigNumbers &copy)
	{
		bigNumber.push_back(0);
		bigNumber.clear();
		for (int x = 0; x < copy.bigNumber.size(); x++)
		{
			bigNumber.push_back(copy.bigNumber.at(x));
		}
		removeExtraneousZeroes();
	}

	//a mutator function for the big number value being stored in bigNumber
	//this function takes an int value, and breaks it down so that it can be stored digit by digit in bigNumber
	//the removeExtraneousZeroes function is then called
	void BigNumbers::setNumber(int newNumber)
	{
		if (newNumber < 0)
		{
			newNumber = abs(newNumber);
		}
		bigNumber.clear();
		while (newNumber > 0)
		{
			int addValue = newNumber % 10;
			int newStart = newNumber / 10;
			bigNumber.push_back(addValue);
			newNumber = newStart;
		}
		removeExtraneousZeroes();
	}

	//a second  mutator function for the big number value being stored in bigNumber
	//this function takes another bigNumber vector, and copies each digit of its own  into this one
	//the removeExtraneousZeroes function is then called
	void BigNumbers::setNumber2(BigNumbers newNumber)
	{
		bigNumber.clear();
		for (int x = 0; x < newNumber.getNumber().size(); x++)
		{
			bigNumber.push_back(newNumber.getNumber().at(x));
		}
		removeExtraneousZeroes();
	}

	void BigNumbers::setNumberSecret(vector<int> newNumber)
	{
		bigNumber.clear();
		for (int x = 0; x < newNumber.size(); x++)
		{
			bigNumber.push_back(newNumber.at(x));
		}
		removeExtraneousZeroes();
	}

	//an accessor function that returns the vector bigNumber
	vector<int> BigNumbers::getNumber()
	{
		return bigNumber;
	}

	//a function that prints out the contents of bigNumber
	//this is accomplished by printing each individual item in bigNumber in reverse order
	//(as the first item in bigNumber is the least significant digit of the total number)
	void BigNumbers::printNumber()
	{
		if (bigNumber.size() == 0)
		{
			cout << "0";
		}
		for (int x = bigNumber.size() - 1; x >= 0; x--)
		{
			cout << bigNumber.at(x);
		}
		cout << endl;
	}

	//a clean-up function that removes any zeroes present before the actual value being stored in bigNumber
	//NOTE: this will leave a vector filled entirely with 0 values completely empty, which is accounted for throughout the library
	void BigNumbers::removeExtraneousZeroes()
	{
		while ((bigNumber.size() > 0) && (bigNumber.at(bigNumber.size() - 1) < 1))
		{
			bigNumber.pop_back();
		}
	}

	//operator overloads for +, -, *, /, and % - each takes another BigNumbers object
	//operator overload for +
	//can functionally add two BigNumbers up to 10000 digits in length, at which point all 10000 digits are 9
	//the removeExtraneousZeroes function is then called
	//NOTE: due to the nature of carry values in this operator, extraneous zeroes are intitially added if bigNumber's size
	//is less than that of the right BigNumbers vector. These are removed at the end of the operation
	BigNumbers BigNumbers::operator + (const BigNumbers &right)
	{
		BigNumbers temp;

		vector<int> storage = bigNumber;

		if (right.bigNumber.size() > storage.size())
		{
			while (right.bigNumber.size() > storage.size())
			{
				storage.push_back(0);
			}
		}

		for (int x = 0; x < storage.size(); x++)
		{
			if (x < right.bigNumber.size())
			{
				if ((storage.at(x) + right.bigNumber.at(x)) < 10)
				{
					storage.at(x) += right.bigNumber.at(x);
				}
				else
				{
					if ((storage.size() == maxSize) && (x == (storage.size() - 1)))
					{
						for (int y = 0; y < storage.size(); y++)
						{
							storage.at(y) = 9;
						}
					}
					else if (x == (storage.size() - 1))
					{
						storage.at(x) += right.bigNumber.at(x);
						storage.at(x) -= 10;
						storage.push_back(1);
					}
					else
					{
						storage.at(x) += right.bigNumber.at(x);
						storage.at(x) -= 10;
						storage.at(x + 1)++;
					}
				}
			}
			else
			{
				if (storage.at(x) >= 10)
				{
					if ((storage.size() == maxSize) && (x == (storage.size() - 1)))
					{
						for (int y = 0; y < storage.size(); y++)
						{
							storage.at(y) = 9;
						}
					}
					else if (x == (storage.size() - 1))
					{
						storage.at(x) -= 10;
						storage.push_back(1);
					}
					else
					{
						storage.at(x) -= 10;
						storage.at(x + 1)++;
					}
				}
			}
		}

		temp.setNumberSecret(storage);

		return temp;
	}

	//operator overload for -
	//can functionally subtract two BigNumbers up to 10000 digits in length, and to a minimum of empty (a functional value of 0)
	//the removeExtraneousZeroes function is then called
	//NOTE: negative BigNumbers are not possible to create, with the minimum possible value being empty (a functional value of 0)
	BigNumbers BigNumbers::operator - (const BigNumbers &right)
	{
		BigNumbers temp;

		vector<int> storage = bigNumber;

		if (right.bigNumber.size() > storage.size())
		{
			for (int y = 0; y < storage.size(); y++)
			{
				storage.at(y) = 0;
			}
		}
		else
		{
			for (int x = 0; x < storage.size(); x++)
			{
				if (x < right.bigNumber.size())
				{
					if ((storage.at(x) - right.bigNumber.at(x)) >= 0)
					{
						storage.at(x) -= right.bigNumber.at(x);
					}
					else
					{
						if (x == (storage.size() - 1))
						{
							for (int y = 0; y < storage.size(); y++)
							{
								storage.at(y) = 0;
							}
						}
						else
						{
							storage.at(x) -= right.bigNumber.at(x);
							storage.at(x) += 10;
							storage.at(x + 1)--;
						}
					}
				}
				else
				{
					if (storage.at(x) < 0)
					{
						storage.at(x) += 10;
						storage.at(x + 1)--;
					}
				}
			}
		}

		temp.setNumberSecret(storage);

		return temp;
	}

	//operator overload for *
	//can functionally multiply two BigNumbers up to 10000 digits in length, at which point all 10000 digits are 9
	//the removeExtraneousZeroes function is then called
	BigNumbers BigNumbers::operator * (const BigNumbers &right)
	{
		BigNumbers temp;

		vector<int> storage1 = bigNumber;

		if (storage1.empty() || right.bigNumber.empty())
		{
			storage1.clear();
		}
		else
		{
			vector<int> storage2 = vector<int>(maxSize);

			for (int x = 0; x < storage1.size(); x++)
			{
				for (int y = 0; y < right.bigNumber.size(); x++)
				{
					if ((y + x) < storage2.size())
					{
						storage2.at(y + x) += (storage1.at(x) * right.bigNumber.at(y));
					}
					else
					{
						storage2.clear();
						for (int a = 0; a < maxSize; a++)
						{
							storage2.push_back(9);
						}
						y = right.bigNumber.size();
						x = storage1.size();
					}
				}
			}

			for (int x = 0; x < storage2.size(); x++)
			{
				if (storage2.at(x) >= 10)
				{
					if (x == (storage2.size() - 1))
					{
						for (int y = 0; y < storage2.size(); y++)
						{
							storage2.at(y) = 9;
						}
					}
					else
					{
						int carry = 0;
						while (storage2.at(x) >= 10)
						{
							storage2.at(x) -= 10;
							carry++;
						}
						storage2.at(x + 1) += carry;
					}
				}
			}

			storage1 = storage2;
		}

		temp.setNumberSecret(storage1);

		return temp;
	}

	//operator overload for /
	//can functionally divide two BigNumbers up to 10000 digits in length, and to a minimum of empty (a functional value of 0)
	//the removeExtraneousZeroes function is then called
	//NOTE: inputting an empty vector (with a functional value of 0) results in a divide by zero error,
	//causing an error message to be produced and the operation to not procede
	BigNumbers BigNumbers::operator / (const BigNumbers &right)
	{
		BigNumbers temp;

		vector<int> storage = bigNumber;
		int quotient = 0;
		bool failure = false;
		bool equal = true;
		bool less;

		if (right.bigNumber.empty())
		{
			failure = true;
			cout << "Warning! Divide by zero error detected! Please try again with a positive, non-zero value." << endl;
			storage.clear();
		}
		else if ((storage.empty()) || (right.bigNumber.size() > storage.size()))
		{
			less = true;
		}
		else if (right.bigNumber.size() == storage.size())
		{
			for (int x = 0; x < storage.size(); x++)
			{
				if (storage.at(x) != right.bigNumber.at(x))
				{
					equal = false;
					if (storage.at(x) < right.bigNumber.at(x))
					{
						less = true;
					}
					if (storage.at(x) > right.bigNumber.at(x))
					{
						less = false;
					}
				}
			}

			if (equal)
			{
				quotient = 1;
				storage.clear();
			}
			else if (less)
			{
				quotient = 0;
				storage.clear();
			}
		}

		if (!failure && ((right.bigNumber.size() < storage.size()) || !less))
		{
			while (!storage.empty())
			{
				for (int x = 0; x < storage.size(); x++)
				{
					if (x < right.bigNumber.size())
					{
						if ((storage.at(x) - right.bigNumber.at(x)) >= 0)
						{
							storage.at(x) -= right.bigNumber.at(x);
						}
						else
						{
							if (x == (storage.size() - 1))
							{
								for (int y = 0; y < storage.size(); y++)
								{
									storage.at(y) = 0;
								}
								quotient = -1;
							}
							else
							{
								storage.at(x) -= right.bigNumber.at(x);
								storage.at(x) += 10;
								storage.at(x + 1)--;
							}
						}
					}
					else
					{
						if (storage.at(x) < 0)
						{
							storage.at(x) += 10;
							storage.at(x + 1)--;
						}
					}
				}

				quotient++;
				
				while ((storage.size() > 0) && (storage.at(storage.size() - 1) < 1))
				{
					storage.pop_back();
				}
			}
		}

		if (!failure)
		{
			storage.clear();
			while (quotient > 0)
			{
				int value = quotient % 10;
				quotient = quotient / 10;
				storage.push_back(value);
			}
		}

		temp.setNumberSecret(storage);

		return temp;
	}

	//operator overload for %
	//can functionally modulo two BigNumbers up to 10000 digits in length, and to a minimum of empty (a functional value of 0)
	//the removeExtraneousZeroes function is then called
	//NOTE: inputting an empty vector (with a functional value of 0) results in a modulo by zero error,
	//causing an error message to be produced and the operation to not procede
	BigNumbers BigNumbers::operator % (const BigNumbers &right)
	{
		BigNumbers temp;

		vector<int> storage = bigNumber;
		vector<int> remainder = vector<int>();
		
		if (right.bigNumber.empty())
		{
			cout << "Warning! Modulo by zero error detected! Please try again with a positive, non-zero value." << endl;
		}
		else if (storage.empty())
		{
			//throw a party :D
		}
		else
		{
			while (!storage.empty())
			{
				if (storage.size() == right.bigNumber.size())
				{
					bool equal = true;
					bool less = false;

					for (int x = 0; x < storage.size(); x++)
					{
						if (storage.at(x) != right.bigNumber.at(x))
						{
							equal = false;
							if (storage.at(x) < right.bigNumber.at(x))
							{
								less = true;
							}
							if (storage.at(x) > right.bigNumber.at(x))
							{
								less = false;
							}
						}
					}

					if (equal || less)
					{
						for (int x = 0; x < storage.size(); x++)
						{
							remainder.push_back(storage.at(x));
						}
						storage.clear();
					}
				}
				else if (storage.size() < right.bigNumber.size())
				{
					for (int x = 0; x < storage.size(); x++)
					{
						remainder.push_back(storage.at(x));
					}
					storage.clear();
				}
				else
				{
					for (int x = 0; x < storage.size(); x++)
					{
						if (x < right.bigNumber.size())
						{
							if ((storage.at(x) - right.bigNumber.at(x)) >= 0)
							{
								storage.at(x) -= right.bigNumber.at(x);
							}
							else
							{
								if (x == (storage.size() - 1))
								{
									for (int y = 0; y < storage.size(); y++)
									{
										storage.at(y) = 0;
									}
								}
								else
								{
									storage.at(x) -= right.bigNumber.at(x);
									storage.at(x) += 10;
									storage.at(x + 1)--;
								}
							}
						}
						else
						{
							if (storage.at(x) < 0)
							{
								storage.at(x) += 10;
								storage.at(x + 1)--;
							}
						}
					}

					while ((storage.size() > 0) && (storage.at(storage.size() - 1) < 1))
					{
						storage.pop_back();
					}
				}
			}
		}

		temp.setNumberSecret(remainder);

		return temp;
	}