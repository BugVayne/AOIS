#include "BinaryMath.h"
#include"cmath"



BinaryMath BinaryMath::operator+ (BinaryMath _binary_number)
{
	BinaryForm a(*this);
	BinaryForm b(_binary_number);
	bool is_both_negative = 0;
	bool is_result_negative = 0;
	bool is_one_negative = 0;

	if (a.is_negative && b.is_negative)
		is_both_negative = 1;
	else if (a.is_negative)
	{
		is_one_negative = 1;
		a.EqualSize(b);
		a.ConvertToInverse();
		a.ConvertToAdditional(0);
		if (abs(a.number) > abs(b.number))
		{
			is_result_negative = 1;
		}
		a.PushTop(a.is_negative);
		b.PushTop(b.is_negative);

	}
	else if (b.is_negative)
	{
		is_one_negative = 1;
		b.EqualSize(a);
		b.ConvertToInverse();
		b.ConvertToAdditional(0);
		if (abs(b.number) > abs(a.number))
		{
			is_result_negative = 1;
		}
		b.PushTop(b.is_negative);
		a.PushTop(a.is_negative);

	}

	BinaryMath result;
	vector<bool> binary_sum;
	bool is_rank_up = 0;
	int i = a.binary_form.size() - 1;
	int j = b.binary_form.size() - 1;

	while (i >= 0 || j >= 0 || is_rank_up != 0) {
		int sum = is_rank_up;

		if (i >= 0)
		{
			sum += a.binary_form[i];
			i--;
		}
		if (j >= 0)
		{
			sum += b.binary_form[j];
			j--;
		}

		binary_sum.insert(binary_sum.begin(), sum % 2);
		is_rank_up = sum / 2;
	}
	if (binary_sum.size() > a.binary_form.size() && is_one_negative)
	{
		binary_sum.erase(binary_sum.begin());
	}
	if (is_both_negative)
		result.SetBinary(binary_sum, is_both_negative);
	else
		result.SetBinary(binary_sum, is_result_negative);
	if (is_result_negative && !is_both_negative)
	{
		result.ConvertToInverse();
		result.ConvertToAdditional(1);
	}

	return result;
}

BinaryMath BinaryMath::operator- (BinaryMath _binary_number)
{

	BinaryForm a(*this);
	BinaryForm b(_binary_number);
	BinaryMath result;
	if (a.number == b.number)
	{
		result.SetBinary({ 0 }, 0);
		return result;
	}
	if (b.is_negative)
		b.is_negative = 0;
	else
		b.is_negative = 1;


	bool is_both_negative = 0;
	bool is_result_negative = 0;
	bool is_one_negative = 0;

	if (a.is_negative && b.is_negative)
		is_both_negative = 1;
	else if (a.is_negative)
	{
		is_one_negative = 1;
		a.EqualSize(b);
		a.ConvertToInverse();
		a.ConvertToAdditional(0);
		if (abs(a.number) > abs(b.number))
		{
			is_result_negative = 1;
		}
		a.PushTop(a.is_negative);
		b.PushTop(b.is_negative);

	}
	else if (b.is_negative)
	{
		is_one_negative = 1;
		b.EqualSize(a);
		b.ConvertToInverse();
		b.ConvertToAdditional(0);
		if (abs(b.number) > abs(a.number))
		{
			is_result_negative = 1;
		}
		b.PushTop(b.is_negative);
		a.PushTop(a.is_negative);

	}

	vector<bool> binary_sum;
	bool is_rank_up = 0;
	int i = a.binary_form.size() - 1;
	int j = b.binary_form.size() - 1;

	while (i >= 0 || j >= 0 || is_rank_up != 0) {
		int sum = is_rank_up;

		if (i >= 0)
		{
			sum += a.binary_form[i];
			i--;
		}
		if (j >= 0)
		{
			sum += b.binary_form[j];
			j--;
		}

		binary_sum.insert(binary_sum.begin(), sum % 2);
		is_rank_up = sum / 2;
	}
	if (binary_sum.size() > a.binary_form.size() && is_one_negative)
	{
		binary_sum.erase(binary_sum.begin());
	}
	if (is_both_negative)
		result.SetBinary(binary_sum, is_both_negative);
	else
		result.SetBinary(binary_sum, is_result_negative);
	if (is_result_negative && !is_both_negative)
	{
		result.ConvertToInverse();
		result.ConvertToAdditional(1);
	}

	return result;
}

void BinaryMath::ExpandNumberToLeft(size_t estimated_size)
{
	size_t i = estimated_size - this->binary_form.size();
	for (i; i > 0; i--)
	{
		this->binary_form.push_back(0);
	}
}

BinaryMath BinaryMath::operator* (BinaryMath _binary_number)
{
	BinaryMath a(*this);
	BinaryMath b(_binary_number);
	bool is_result_negative = 0;
	if (a.is_negative ^ b.is_negative)
		is_result_negative = 1;
	a.EqualSize(b);
	size_t base_size = a.binary_form.size();
	BinaryMath mult;
	mult.SetBinary(vector<bool> {}, 0);
	for (size_t i = 0; i < base_size; i++)
	{
		if (a.binary_form.at(base_size - i - 1) == 1)
		{
			b.ExpandNumberToLeft(base_size + i);
			mult = mult + b;
		}
	}
	mult.SetBinary(mult.binary_form, is_result_negative);
	return mult;
}

BinaryMath BinaryMath::operator/ (BinaryMath _binary_number)
{
	if (_binary_number.number == 0)
	{
		cout << "  impossible to divide on zero\n  The result is empty number\n";
		BinaryMath empty_number;
		return empty_number;
	}
	BinaryMath divident(*this);
	BinaryMath divisor(_binary_number);
	bool is_result_negative = 0;
	if (divident.is_negative ^ divisor.is_negative)
		is_result_negative = 1;
	size_t divident_size = divident.binary_form.size();
	size_t divisor_size = divisor.binary_form.size();
	BinaryMath result;
	BinaryMath iter_divident;
	BinaryMath ostatok;
	bool for_push = 0;
	bool is_after_point = 0;
	bool is_first_iteration = 1;
	if (divident.number == divisor.number)
	{
		result.SetBinary({ 1 }, is_result_negative);
		return result;
	}
	int gh = 0;
	while (gh < 10)
	{
		if ((divident.binary_form.empty() || divident.IsVectorOnlyNull()) && ostatok.IsVectorOnlyNull() && !is_first_iteration)
		{
			for (size_t i = 0; !divident.binary_form.empty(); i++)
			{
				result.binary_form.push_back(0);
				divident.binary_form.erase(divident.binary_form.begin());
			}
			break;
		}
		iter_divident.binary_form = ostatok.binary_form;
		ostatok.binary_form = {};
		for (size_t i = 0; iter_divident < divisor; i++)
		{

			if (!divident.binary_form.empty())
			{
				if (i > 0)
					if (!is_after_point)
						result.binary_form.push_back(0);
					else
						result.after_point_precision.push_back(0);
				for_push = divident.binary_form.at(0);
				divident.binary_form.erase(divident.binary_form.begin());
			}
			else {
				if (i > 0)
					if (!is_after_point)
						result.binary_form.push_back(0);
					else
						result.after_point_precision.push_back(0);
				for_push = 0;
				is_after_point = 1;
			}
			iter_divident.binary_form.push_back(for_push);

		}

		if (!is_after_point)
		{
			ostatok = iter_divident - divisor;
			result.binary_form.push_back(1);
		}
		else
		{
			ostatok = iter_divident - divisor;
			result.after_point_precision.push_back(1);
		}

		is_first_iteration = 0;
		gh++;
	}

	double int_part;
	double n = static_cast<double>(this->number) / _binary_number.number;
	double frac_part = modf(n, &int_part);
	vector<bool> binary;
	while (frac_part != 0 && binary.size() < 5)
	{
		frac_part = frac_part * 2;
		if (frac_part < 1)
			binary.push_back(0);
		else
		{
			binary.push_back(1);
			frac_part -= 1.0;
		}

	}
	BinaryForm num1;
	num1.SetDecimal(int(int_part));
	BinaryForm num2;
	num2.SetBinary(binary, 0);
	while (num2.binary_form.size() > 5)
	{
		num2.binary_form.pop_back();
	}
	result.after_point_precision = num2.binary_form;
	result.binary_form = num1.binary_form;

	result.is_negative = is_result_negative;
	return result;
}

int getDigitsAfterDecimal(double number) {
	string numberString = to_string(number);
	size_t decimalPosition = numberString.find('.');
	if (decimalPosition != string::npos) {

		size_t digitsAfterDecimal = numberString.size() - decimalPosition - 1;
		return static_cast<int>(digitsAfterDecimal);
	}
	return 0;
}