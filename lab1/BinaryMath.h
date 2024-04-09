#pragma once
#include"BinaryForm.h"
#include<string>


class BinaryMath : public BinaryForm
{
private:


public:
	BinaryMath() { }
	BinaryMath operator+ (BinaryMath _binary_number);
	BinaryMath operator- (BinaryMath _binary_number);
	BinaryMath operator* (BinaryMath _binary_number);
	void ExpandNumberToLeft(size_t estimated_size);
	BinaryMath operator/ (BinaryMath _binary_number);
	bool operator< (BinaryMath _binary_number) {
		this->ConvertToDecimal();
		_binary_number.ConvertToDecimal();
		if (this->number < _binary_number.number)
			return true;
		else
			return false;
	}
	bool IsVectorOnlyNull()
	{
		vector<bool> _vector = this->binary_form;
		bool is_null = 1;
		for (size_t i = 0; i < _vector.size(); i++)
		{
			if (_vector.at(i) == 1)
				is_null = 0;
		}
		return is_null;
	}
};

int getDigitsAfterDecimal(double number);
