#include "SpreadsheetOfTruth.h"

extern bool Implication(bool a, bool b)
{
	if (b == false && a == true)
		return false;
	return true;
}
extern bool Conjuction(bool a, bool b)
{
	if (a == false || b == false)
		return false;
	return true;
}
extern bool Disjunction(bool a, bool b)
{
	if (a == false && b == false)
		return false;
	return true;
}
extern bool Equivalence(bool a, bool b)
{
	if (a == b)
		return true;
	return false;
}
extern bool Denial(bool a)
{
	if (a)
		return false;
	return true;
}



SpreadsheetOfTruth::SpreadsheetOfTruth(string _formula)
{
	SDNF = SKNF = SKNFnumeral = SDNFnumeral = "";
	index_form = 0;
	rows, columns = 0;
	this->formula = _formula;
	this->atomar_formules = {};
	for (size_t i = 0; i < formula.length(); i++)
	{
		if (isalpha(formula[i]) && !this->IsInAtomar(formula[i]))
		{
			this->atomar_formules.push_back(formula[i]);
		}
	}
	this->InitializeSubFormules();
	this->CalculateSpreadSheet();
	for (size_t i = 0; i < rows; i++)
	{
		this->index_form+=((this->sheet[i][columns - 1])*pow(2, rows-i-1));
	}
	this->CalculateSDNF();
	this->CalculateSKNF();
}

void SpreadsheetOfTruth::InitializeSubFormules()
{
	stack<char> stack;
	for (size_t i = 0; i < this->formula.length(); i++)
	{
		stack.push(this->formula.at(i));
		if (this->formula.at(i) == ')')
		{
			string subformule = "";
			while (stack.top() != '(')
			{
				subformule += stack.top();
				stack.pop();
			}
			subformule += stack.top();
			stack.pop();
			reverse(subformule.begin(), subformule.end());
			this->subformules.push_back(subformule);
			stack.push(static_cast<char>((this->subformules.size() - 1) + '0'));
		}
	}
	this->columns += this->subformules.size();
	this->columns += this->atomar_formules.size();
	this->rows = static_cast<size_t>(pow(2, this->atomar_formules.size()));

	this->sheet.resize(this->rows, vector<bool>(this->columns));
}

void SpreadsheetOfTruth::CalculateSpreadSheet()//----------------
{
	this->CalculateAtomarFormules();
	for (size_t i = 0; i < this->subformules.size(); i++)
	{

	this->CalculateSubFormule(*(this->subformules.begin()+i));
	}

}

void SpreadsheetOfTruth::CalculateAtomarFormules()
{
	size_t counter;
	for (size_t i = 0; i < this->atomar_formules.size(); i++)
	{
		if (i == this->atomar_formules.size() - 1)
			counter = 2;
		else
			counter = pow(2, this->atomar_formules.size() - i);
		for (size_t j = 0; j < rows; j++) {
			if (counter == 0)
				if (i != this->atomar_formules.size() - 1)
					counter = pow(2, this->atomar_formules.size() - i);
				else
					counter = 2;

			if (counter > (pow(2, this->atomar_formules.size() - i) / 2) && i != this->atomar_formules.size() - 1)
				this->sheet[j][i] = 0;
			else if (i != this->atomar_formules.size() - 1)
				this->sheet[j][i] = 1;
			else if (counter > 1)
				this->sheet[j][i] = 0;
			else
				this->sheet[j][i] = 1;

			counter--;
		}
	}

}


void SpreadsheetOfTruth::CalculateSubFormule(string _formule)
{
	bool is_for_denial = false;
	char a_op, b_op, operand ;
	a_op = b_op = operand = '\0';
	for (size_t i = 1; i < _formule.size() - 1; i++)
	{
		if (_formule[i] == ' ')
			continue;
		else if (_formule[i] == '!')
		{
			is_for_denial = true;
			for (size_t j = 1; j < _formule.size()-i; j++)
			{
				if (_formule[i+j]!=' ')
				{
					a_op = _formule[i + j];
					break;
				}
			}
			break;
		}
		else
		{
			if (a_op == '\0')
				a_op = _formule[i];
			else if (operand == '\0')
				operand = _formule[i];
			else if (b_op == '\0')
				b_op = _formule[i];

		}
	}
	size_t a_op_index, b_op_index, formule_index;
	formule_index = this->FindSubFormuleIndex(_formule) + this->atomar_formules.size();
	if (is_for_denial)//for denial
	{
		if(isalpha(a_op))
		{
			a_op_index = this->FindAtomarFormuleIndex(a_op);
		}
		else
		{
			a_op_index = stoi(string(1, a_op));
			a_op_index = a_op_index + this->atomar_formules.size();
		}
		this->CalculateDenial(a_op_index, formule_index);
		return;
	}
	if (isalpha(a_op))
	{
		a_op_index = this->FindAtomarFormuleIndex(a_op);
	}
	else {
		a_op_index = stoi(string(1, a_op));
		a_op_index = a_op_index + this->atomar_formules.size();
	}
	if (isalpha(b_op))
	{
		b_op_index = this->FindAtomarFormuleIndex(b_op);
	}
	else {
		b_op_index = stoi(string(1, b_op));
		b_op_index = b_op_index + this->atomar_formules.size();

	}
	this->FillTheTable(a_op_index, b_op_index, formule_index, operand);

}
void SpreadsheetOfTruth::CalculateDenial(size_t _a, size_t _formule_index)
{
	for (size_t i = 0; i < this->rows; i++)
	{
		this->sheet[i][_formule_index] = Denial(this->sheet[i][_a]);
	}
}

void SpreadsheetOfTruth::FillTheTable(size_t _a_op, size_t _b_op, size_t _formule_index, char _operation)
{
		for (size_t i = 0; i < this->rows; i++)
		{
			this->sheet[i][_formule_index] = this->SwitchOperation(_operation, this->sheet[i][_a_op], this->sheet[i][_b_op]);
		}
}

bool SpreadsheetOfTruth::SwitchOperation(char _op, bool _a, bool _b)
{
	switch(_op)
	{
		case '&':
		{
			return Conjuction(_a, _b);
			break;
		}
		case '|':
		{
			return Disjunction(_a, _b);
			break;
		}
		case '>':
		{
			return Implication(_a, _b);
			break;
		}
		case '~':
		{
			return Equivalence(_a, _b);
			break;
		}
		default:
		{
			cout << "ERROR in trying to switch operation\n";
			exit(0);
			break;
		}
	}
	return false;
}


bool SpreadsheetOfTruth::IsOnlyAtomarFormules(string _formule)
{
	for (size_t i = 0; i < _formule.length(); i++)
	{
		if (!isalpha(_formule[i]))
			return false;
	}
	return true;
}


size_t SpreadsheetOfTruth::FindAtomarFormuleIndex(char _formule)
{
	for (size_t i = 0; i < this->atomar_formules.size(); i++)
	{
		if (this->atomar_formules.at(i) == _formule)
			return i;
	}
	return -1;
}

size_t SpreadsheetOfTruth::FindSubFormuleIndex(string _formule)
{
	for (size_t i = 0; i < this->subformules.size(); i++)
	{
		if (this->subformules.at(i) == _formule)
			return i;
	}
	return -1;
}


void SpreadsheetOfTruth::PrintFormules()
{
	cout << "  Formule: " << this->formula << endl;
	cout << "  Atomar formules:  ";
	for (size_t i = 0; i < this->atomar_formules.size(); i++)
	{
		cout << this->atomar_formules.at(i) << "  ";
	}
	cout << endl;
	cout << "  Subformules:   ";
	for (size_t i = 0; i < this->subformules.size(); i++)
	{
		cout << this->subformules.at(i) << "  ";
	}
	cout << endl;
	cout << "  rows: " << rows << "\tcolumns: " << columns << endl;
	cout << "  SDNF: " << this->SDNF << endl;
	cout << "  SDNF numeral form : " << this->SDNFnumeral << endl;
	cout << "  SKNF: " << this->SKNF << endl;
	cout << "  SKNF numeral form : " << this->SKNFnumeral << endl;
	cout << "  Index form : " << this->index_form << endl << endl;
}

bool SpreadsheetOfTruth::IsInAtomar(char _atomar)
{
	for (size_t i = 0; i < this->atomar_formules.size(); i++)
	{
		if (this->atomar_formules.at(i) == _atomar)
			return true;
	}
	return false;
}

void  SpreadsheetOfTruth::Printsheet()
{
	for (size_t i = 0; i < this->atomar_formules.size(); i++)
	{
		cout << "  |  " << i ;
	}
	for (size_t i = 0; i < this->subformules.size(); i++)
	{
		cout << "  |      " << i << "    ";
	}
	cout << "  |\n";

	for (size_t i = 0; i < this->atomar_formules.size(); i++)
	{
		cout << "  |  " << this->atomar_formules.at(i);
	}
	for (size_t i = 0; i < this->subformules.size(); i++)
	{
		cout << "  |  " << this->subformules.at(i);
	}
	cout << "  |  " << endl << endl;
	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->columns; j++)
		{
			if (j > this->atomar_formules.size() - 1)
				cout << "  |      " << this->sheet[i][j] << "    ";
			else
				cout << "  |  " << this->sheet[i][j];

		}
		cout << "  |  " << endl;
	}

}

void  SpreadsheetOfTruth::CalculateSDNF()
{

	for (size_t i = 0; i < rows; i++)
	{
		if(this->sheet[i][columns-1]==true)
		{
			this->SDNFnumeral += to_string( i);
			this->SDNF += "( ";
			for (size_t j = 0; j < this->atomar_formules.size(); j++)
			{
				if (this->sheet[i][j] == false)
				{
					this->SDNF += "(!";
					this->SDNF += string(1, this->atomar_formules.at(j));
					this->SDNF += ")";
				}
				else
				{
					this->SDNF += string(1, this->atomar_formules.at(j));
				}
				if(j!=this->atomar_formules.size()-1)
					this->SDNF += " & ";
			}
			this->SDNF += " )";
			if(i!= rows-1)
				this->SDNF += " | ";
		}
	}
	

}
void SpreadsheetOfTruth::CalculateSKNF()
{
	for (size_t i = 0; i < rows; i++)
	{
		if (this->sheet[i][columns - 1] == false)
		{
			this->SKNFnumeral += to_string( i);
			this->SKNF += " ( ";
			for (size_t j = 0; j < this->atomar_formules.size(); j++)
			{
				if (this->sheet[i][j] == true)
				{
					this->SKNF += "(!";
					this->SKNF += string(1, this->atomar_formules.at(j));
					this->SKNF += ")";
				}
				else
				{
					this->SKNF += string(1, this->atomar_formules.at(j));
				}
				if (j != this->atomar_formules.size() - 1)
					this->SKNF += " | ";
			}
			this->SKNF += " )";
			if (i != rows - 1)
				this->SKNF += " &";
		}
	}
}
