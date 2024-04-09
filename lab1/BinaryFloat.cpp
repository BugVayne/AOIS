#include "BinaryFloat.h"

void BinaryFloat::CalculateMantissAndExp()
{
	double decimal = this->number;
	double int_part;
	double frac_part = modf(decimal, &int_part);
	this->CalcBinary(int_part);
	this->shift = this->exp.size() - 1;
	this->CalcMantiss(frac_part);
	for (size_t i = this->exp.size() - 1; i > 0; i--)
	{
		this->mantiss.insert(mantiss.begin(), exp.at(i));
		if (this->mantiss.size() > this->mantiss_size)
			this->mantiss.pop_back();
	}
	this->CalcBinary(127 + this->exp.size() - 1);
	cout << "number - \n";
	this->PrintBinary();
}

void BinaryFloat::CalcBinary(double _number)
{
	int num = static_cast<int>(_number);
	vector<bool> binary;
	while (num > 0)
	{
		binary.insert(binary.begin(), num % 2);
		num = num / 2;
	}
	this->exp = binary;
}

void BinaryFloat::CalcMantiss(double _number)
{
	double num = _number;
	vector<bool> binary;
	while (num != 0 && binary.size() < this->mantiss_size)
	{
		num = num * 2;
		if (num < 1)
			binary.push_back(0);
		else
		{
			binary.push_back(1);
			num -= 1.0;
		}

	}
	while (binary.size() < this->mantiss_size)
		binary.push_back(0);
	this->mantiss = binary;
}

void BinaryFloat::PrintBinary()
{
	cout << " Binary with float point: \n";
	for (size_t i = 0; i < exp.size(); i++)
	{
		cout << this->exp.at(i) << " ";
	}
	cout << ". ";
	for (size_t i = 0; i < mantiss.size(); i++)
	{
		if ((i + 1) % 4 == 0)
			cout << " ";
		cout << this->mantiss.at(i) << " ";
	}
	cout << endl;
}

BinaryFloat BinaryFloat::operator+(BinaryFloat _number)
{
	BinaryFloat a = *this;
	BinaryFloat b = _number;
	BinaryFloat result;
	size_t shift_for_mantiss = 0;
	bool is_a_bigger_shift = 0;
	if (a.shift > b.shift)
	{
		is_a_bigger_shift = 1;
		shift_for_mantiss = a.shift - b.shift;
	}
	else if (a.shift < b.shift)
	{
		shift_for_mantiss = b.shift - a.shift;
	}
	if (is_a_bigger_shift && shift_for_mantiss != 0)
	{
		b.ShiftMantiss(shift_for_mantiss);
		b.exp = a.exp;
	}
	else if (shift_for_mantiss != 0)
	{
		a.ShiftMantiss(shift_for_mantiss);
		a.exp = b.exp;
	}
	bool exp_is_plus_rank = 0;
	result.mantiss = a.MantissSum(b);
	if (result.mantiss.size() > result.mantiss_size)
	{
		exp_is_plus_rank = 1;
	}
	result.exp = a.exp;

	if (exp_is_plus_rank)
	{
		bool is_next_rank = true;
		for (size_t i = result.exp.size() - 1; i >= 0 && is_next_rank == true; --i)
		{
			if (result.exp.at(i) == 1)
			{
				result.exp.at(i) = 0;
			}
			else
			{
				result.exp.at(i) = 1;
				is_next_rank = false;
			}
		}
		result.mantiss.pop_back();
	}
	/*if (result.mantiss.at(0) == 1)
		result.mantiss.at(0) = 0;*/
	return result;
}
void BinaryFloat::ShiftMantiss(size_t _shift)
{
	bool for_insert = 1;
	for (size_t i = 0; i < _shift; i++)
	{
		this->mantiss.insert(this->mantiss.begin(), for_insert);
		if (this->mantiss.size() > this->mantiss_size)
			this->mantiss.pop_back();
		for_insert = 0;
	}
}
vector<bool> BinaryFloat::MantissSum(BinaryFloat _number)
{
	vector<bool> binary_sum;
	bool is_rank_up = 0;
	int i = this->mantiss.size() - 1;
	int j = _number.mantiss.size() - 1;

	while (i >= 0 || j >= 0 || is_rank_up != 0) {
		int sum = is_rank_up;

		if (i >= 0)
		{
			sum += this->mantiss[i];
			i--;
		}
		if (j >= 0)
		{
			sum += _number.mantiss[j];
			j--;
		}

		binary_sum.insert(binary_sum.begin(), sum % 2);
		is_rank_up = sum / 2;
	}
	if (is_rank_up)
		binary_sum.insert(binary_sum.begin(), 1);


	return binary_sum;
}
