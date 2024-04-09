#include<iostream>
#include<vector>
#include<utility>
using namespace std;
class BinaryForm
{
private:
	enum type_of_code {
		STRAIGHT,
		INVERSE,
		ADDITIONAL
	};
	type_of_code type = STRAIGHT;
	vector<bool> GetBinaryForm() { return this->binary_form; }
	void ConvertToBinary();

public:
	void ConvertToDecimal();
	vector<bool> after_point_precision;
	bool is_negative;
	vector<bool> binary_form;
	void PushTop(bool _element);
	int number;
	void EqualSize(BinaryForm& b);
	void SetDecimal(int _a) { this->number = _a; this->ConvertToBinary(); }
	void ConvertToAdditional(bool _is_to_straight);
	void ConvertToInverse();
	BinaryForm() :number(0), is_negative(0), binary_form({}), type(STRAIGHT), after_point_precision({}) {};
	BinaryForm(BinaryForm& a) { this->binary_form = a.binary_form; this->is_negative = a.is_negative; this->number = a.number; this->type = a.type; this->after_point_precision = a.after_point_precision; };
	void SetBinary(vector<bool> _binar, bool _is_negative) { this->binary_form = _binar; this->is_negative = _is_negative; this->ConvertToDecimal(); }
	void PrintBinaryForm();
	void PrintDecimalForm();
	void PrintAfterPoint();
};
