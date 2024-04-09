#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<cctype>
#include<cmath>
using namespace std;




class SpreadsheetOfTruth
{
private:
	vector<vector<bool>> sheet;
	string formula;
	size_t rows, columns;
	vector<char> atomar_formules;
	vector<string> subformules;
	string SKNF;
	string SDNF;
	string SDNFnumeral;
	string SKNFnumeral;
	double index_form;
	void InitializeSubFormules();
	void CalculateSpreadSheet();
	bool IsInAtomar(char _atomar);
	void CalculateAtomarFormules();
	void CalculateSubFormule(string _formule);
	size_t FindAtomarFormuleIndex(char _formule);
	bool IsOnlyAtomarFormules(string _formule);
	size_t FindSubFormuleIndex(string _formule);
	void FillTheTable(size_t _a_op, size_t _b_op, size_t _formule_index, char _operation);
	bool SwitchOperation(char _op, bool _a, bool _b);
	void CalculateDenial(size_t _a, size_t _formule_index);
	void CalculateSDNF();
	void CalculateSKNF();
public:
	SpreadsheetOfTruth(string _formula);
	void PrintFormules();	
	void Printsheet();
};

