#include "Minimization.h"

extern bool Implication(bool a, bool b)
{
    if (!b && a)
        return false;
    return true;
}
extern bool Conjuction(bool a, bool b)
{
    if (!a || !b)
        return false;
    return true;
}
extern bool Disjunction(bool a, bool b)
{
    if (!a && !b)
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



Minimization::Minimization(string _formula)
{
    SDNF = SKNF = index_form = "";
    columns = 0;
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
        this->index_form += to_string((this->sheet[i][columns - 1]));
    }
    this->CalculateSDNF();
    this->CalculateSKNF();
}

void Minimization::InitializeSubFormules()
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

void Minimization::CalculateSpreadSheet(){
    this->CalculateAtomarFormules();
    for (size_t i = 0; i < this->subformules.size(); i++)
    {

        this->CalculateSubFormule(*(this->subformules.begin() + i));
    }

}

void Minimization::CalculateAtomarFormules()
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


void Minimization::CalculateSubFormule(string _formule)
{
    bool is_for_denial = false;
    char a_op, b_op, operand;
    a_op = b_op = operand = '\0';
    for (size_t i = 1; i < _formule.size() - 1; i++)
    {
        if (_formule[i] == ' ')
            continue;
        else if (_formule[i] == '!')
        {
            is_for_denial = true;
            for (size_t j = 1; j < _formule.size() - i; j++)
            {
                if (_formule[i + j] != ' ')
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
    if (is_for_denial)
    {
        if (isalpha(a_op))
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

void Minimization::CalculateDenial(size_t _a, size_t _formule_index)
{
    for (size_t i = 0; i < this->rows; i++)
    {
        this->sheet[i][_formule_index] = Denial(this->sheet[i][_a]);
    }
}

void Minimization::FillTheTable(size_t _a_op, size_t _b_op, size_t _formule_index, char _operation)
{
    for (size_t i = 0; i < this->rows; i++)
    {
        this->sheet[i][_formule_index] = this->SwitchOperation(_operation, this->sheet[i][_a_op], this->sheet[i][_b_op]);
    }
}

bool Minimization::SwitchOperation(char _op, bool _a, bool _b)
{
    switch (_op)
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

        }
    }
}





size_t Minimization::FindAtomarFormuleIndex(char _formule)
{
    for (size_t i = 0; i < this->atomar_formules.size(); i++)
    {
        if (this->atomar_formules.at(i) == _formule)
            return i;
    }
    return -1;
}

size_t Minimization::FindSubFormuleIndex(string _formule)
{
    for (size_t i = 0; i < this->subformules.size(); i++)
    {
        if (this->subformules.at(i) == _formule)
            return i;
    }
    return -1;
}


void Minimization::PrintFormules()
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
    cout << "  SDNF: " << this->SDNF << "\n  SDNF numeral form: ";
    for (size_t i = 0; i < this->SDNFnumeral.size(); i++)
    {
        cout << this->SDNFnumeral.at(i)<<" ";
    }
    cout << "\n  SKNF: " << this->SKNF << "\n  SKNF numeral form: ";
    for (size_t i = 0; i < this->SKNFnumeral.size(); i++)
    {
        cout << this->SKNFnumeral.at(i) << " ";
    }
    cout << "\n  Index form : " << this->index_form << endl << endl;
}

bool Minimization::IsInAtomar(char _atomar)
{
    for (char atomar_formule : this->atomar_formules)
    {
        if (atomar_formule == _atomar)
            return true;
    }
    return false;
}

void  Minimization::Printsheet()
{
    for (size_t i = 0; i < this->atomar_formules.size(); i++)
    {
        cout << "  |  " << i;
    }
    for (size_t i = 0; i < this->subformules.size(); i++)
    {
        cout << "  |      " << i << "    ";
    }
    cout << "  |\n";

    for (char atomar_formule : this->atomar_formules)
    {
        cout << "  |  " << atomar_formule;
    }
    for (const auto & subformule : this->subformules)
    {
        cout << "  |  " << subformule;
    }
    cout << "  |" << endl << endl;
    for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < this->columns; j++)
        {
            if (j > this->atomar_formules.size() - 1)
                cout << "  |      " << this->sheet[i][j] << "    ";
            else
                cout << "  |  " << this->sheet[i][j];

        }
        cout << "  |" << endl;
    }
cout<<endl;
}

void  Minimization::CalculateSDNF()
{

    for (size_t i = 0; i < rows; i++)
    {
        if (this->sheet[i][columns - 1] == true)
        {
            this->SDNFnumeral.push_back(i);
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
                if (j != this->atomar_formules.size() - 1)
                    this->SDNF += " & ";
            }
            this->SDNF += " )";
            if (i != rows - 1)
                this->SDNF += " | ";
        }
    }


}

void Minimization::CalculateSKNF()
{
    for (size_t i = 0; i < rows; i++)
    {
        if (this->sheet[i][columns - 1] == false)
        {
            this->SKNFnumeral.push_back(i);
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

vector<vector<string>> Minimization::SKNFParser()
{
    vector<vector<string>> vectorSKNF;
    vector<string> SKNFvector;
    string for_push = "";
    for (size_t i = 0; i < this->SKNF.length(); i++)
    {
        if (i == this->SKNF.length() - 1)
        {
            for_push += this->SKNF[i];
            SKNFvector.push_back(for_push);
            break;
        }
        if (this->SKNF[i] != '&')
            for_push += this->SKNF[i];
        else
        {
            SKNFvector.push_back(for_push);
            for_push = "";
        }
    }
    for_push = "";
    vector<string> vfor_push;
    for (size_t i = 0; i < SKNFvector.size(); i++)
    {
        for (size_t j = 0; j < SKNFvector.at(i).length(); j++)
        {
            if (j == SKNFvector.at(i).length() - 1)
            {
                vfor_push.push_back(for_push);
                for_push = "";
                break;
            }
            if (SKNFvector.at(i)[j] == '(' || SKNFvector.at(i)[j] == ')' || SKNFvector.at(i)[j] == ' ')
                continue;

            if (SKNFvector.at(i)[j] != '|')
            {
                for_push += SKNFvector.at(i)[j];
            }
            else
            {
                vfor_push.push_back(for_push);
                for_push = "";
            }
        }
        vectorSKNF.push_back(vfor_push);
        vfor_push = {};
    }
    return vectorSKNF;
}

vector<vector<string>>Minimization::SDNFParser()
{
    vector<vector<string>> vectorSDNF;
    vector<string> SDNFvector;
    string for_push = "";
    for (size_t i = 0; i < this->SDNF.length(); i++)
    {
        if (i == this->SDNF.length() - 1)
        {
            for_push += this->SDNF[i];
            SDNFvector.push_back(for_push);
            break;
        }
        if (this->SDNF[i] != '|')
            for_push += this->SDNF[i];
        else
        {
            SDNFvector.push_back(for_push);
            for_push = "";
        }
    }
    for_push = "";
    vector<string> vfor_push;
    for (size_t i = 0; i < SDNFvector.size(); i++) {
        for (size_t j = 0; j < SDNFvector.at(i).length(); j++) {
            if (j == SDNFvector.at(i).length() - 1) {
                vfor_push.push_back(for_push);
                for_push = "";
                break;
            }
            if (SDNFvector.at(i)[j] == '(' || SDNFvector.at(i)[j] == ')' || SDNFvector.at(i)[j] == ' ')
                continue;

            if (SDNFvector.at(i)[j] != '&') {
                for_push += SDNFvector.at(i)[j];
            } else {
                vfor_push.push_back(for_push);
                for_push = "";
            }
        }
        vectorSDNF.push_back(vfor_push);
        vfor_push = {};
    }
    return vectorSDNF;
}

pair<set<vector<string>>, bool> Minimization::GlueingFormules(vector<vector<std::string>> _formule_parsed) {
    set<vector<string>> glued_formula;
    vector<vector<string>> formule = std::move(_formule_parsed);
    vector<string> for_push;
    vector<int> index;
    cout<<"  ---  Gluing process  ---   \n";
    for (int i = 0; i < size(formule); ++i) {
        for (int j = i+1; j < size(formule); ++j) {
            for_push = this->CompareFormules(formule[i], formule[j]);
            if(!for_push.empty()) {
                index.push_back(i);
                index.push_back(j);
                cout << " ";
                Minimization::PrintVector(formule[i]);
                cout << " & ";
                Minimization::PrintVector(formule[j]);
                cout << " -> ";
                Minimization::PrintVector(for_push);
                cout << endl;
                glued_formula.insert(for_push);
            }
        }
    }

    for(int i = 0; i < formule.size(); i++){
        bool flag = true;
        for(int j : index){
            if(i == j) flag = false;
        }
        if(flag) glued_formula.insert(formule[i]);
    }

    cout<<"  ---  Result:  \n";
    for (const auto& element: glued_formula) {
        Minimization::PrintVector(element);
        cout<<" - ";
    }
    cout<<endl;
    return make_pair(glued_formula, true);
}

vector<string> Minimization::CompareFormules(vector<string> _formule1, vector<string> _formule2) {
    vector<string> result;
    if(_formule1.size() == _formule2.size()) {
        int count = 0; int index = -1;
        for (int i = 0; i < size(_formule1); ++i) {
            for (auto & j : _formule2) {
                if (_formule1[i].size() > 1) {
                    if (j.size() == 1) {
                        if (_formule1[i][1] == j[0]) {
                            index = i;
                        }
                    }
                }
                if (_formule1[i] != j) continue;
                else count ++;
            }
        }
        if(index!=-1){
            if(count == _formule1.size()-1){
                for(int i = 0; i < _formule1.size(); i++){
                    if(i!=index)
                        result.push_back(_formule1[i]);
                }
            }
        }
    }
    return result;
}
void Minimization::PrintVector(const vector<string>& _vector) {
    for (const auto & i : _vector) {
        cout<<i<<" ";
    }
}

set<vector<string>> Minimization::Minimize(bool is_sdnf) {
    pair<set<vector<string>>, bool> pair;
    set<vector<string>> glued;
    if(is_sdnf)
        pair = this->GlueingFormules(this->SDNFParser());
    else
        pair = this->GlueingFormules(this->SKNFParser());
    glued = pair.first;
    bool flag = true;
    for(const auto& element : glued){
        if(element.size() == 1){
            flag = false;
        }
    }

    while(flag && !this->IsAllGlued(pair.first)) {
        pair = this->GlueingFormules(vector<vector<string>>(glued.begin(), glued.end()));
        glued = pair.first;

        for(const auto& element : glued){
            if(element.size() == 1){
                flag = false;
            }
        }
    }



    return glued;
}



void Minimization::TableMethod(const set<vector<string>>& glued_formula, vector<vector<string>> _initial_formule) {
    vector<vector<string>> glued_vector =  vector<vector<string>>(glued_formula.begin(), glued_formula.end());
    vector<vector<bool>> table;
    table.resize(glued_formula.size(), vector<bool>(_initial_formule.size()));
    for (int i = 0; i < glued_vector.size(); ++i) {
        for (int j = 0; j < _initial_formule.size(); ++j) {
            if (Minimization::IsAinB(glued_vector.at(i), _initial_formule.at(j)))
                table[i][j] = true;
            else
                table[i][j] = false;

        }
    }

    cout<<"      ";
    for (const auto & i : _initial_formule) {
        Minimization::PrintVector(i);
        cout<<" | ";
    }
    cout<<endl;
    for (int i = 0; i < table.size(); ++i) {
        Minimization::PrintVector(glued_vector.at(i));
        for (int j = 4-Minimization::StrLengthInVector(glued_vector.at(i)); j > 0; --j) {
            cout<<" ";

        }
        if(glued_vector.at(i).size()==1)
            cout<<" ";
        cout<<"|   ";
        for (auto && j : table.at(i)) {
            cout<<j<<"    |    ";
        }
        cout<<endl;
    }
    cout<<endl;


    cout<<"\n   -- Deleting odd implicant ---\n\n";
    vector<size_t> rows_to_delete = this->DelteOddRowsFromTable(table);

    vector<vector<string>> vec_glued_formula (glued_formula.begin(), glued_formula.end());
    cout<<"Minimized formula :   ";
    for (int i = 0; i < vec_glued_formula.size(); ++i) {
        if(!rows_to_delete.empty()) {
            if (i == rows_to_delete.at(0))
                continue;
            else
            {
                cout << "  -  ";
                this->PrintVector(vec_glued_formula.at(i));
            }
        }
        else {
            cout << "  -  ";
            this->PrintVector(vec_glued_formula.at(i));
        }
    }
    cout<<endl<<endl;




}

bool Minimization::IsAinB(const vector<string>& A, const vector<string>& B){
    std::unordered_set<std::string> setB(B.begin(), B.end());

    for (const auto& element : A) {
        if (setB.find(element) == setB.end()) {
            return false;
        }
    }

    return true;
}

int Minimization::StrLengthInVector(const vector<string>& _vec)
{
    int size = 0;
    for (const auto & i : _vec)
        size+=i.length();
    return size;
}

void Minimization::PrintTableMethod() {
    cout<<"\n  ------------------  Table method for SDNF -------------------------\n";
    this->TableMethod(this->Minimize(true), this->SDNFParser());
    cout<<"\n  ------------------  Table method for SKNF -------------------------\n";
    this->TableMethod(this->Minimize(false), this->SKNFParser());
}

bool Minimization::IsAllGlued(const set<vector<std::string>> &_set) {
    set<vector<std::string>> initial_vector = _set;
    set<vector<std::string>> result_vector = this->GlueingFormules(vector<vector<string>>(initial_vector.begin(), initial_vector.end())).first;
    if (initial_vector.size() != result_vector.size()) {
        return false;
    }

    for (const auto& element : initial_vector) {
        if (result_vector.find(element) == result_vector.end()) {
            return false;
        }
    }

    for (const auto& element : result_vector) {
        if (initial_vector.find(element) == initial_vector.end()) {
            return false;
        }
    }
    return true;

}

vector<size_t> Minimization::DelteOddRowsFromTable(vector<vector<bool>> _vector) {
    vector<size_t> rows_to_delete;
    for (int i = 0; i <_vector.size() ; ++i) {
        vector<bool> is_to_delete (_vector.at(i).size(), false);
        for (int j = 0; j < _vector.at(i).size(); ++j) {
            if(!_vector.at(i).at(j)) {
                is_to_delete.at(j) = true;
                continue;
            }
            else
            {
                for (int k = 0; k < _vector.size(); ++k) {
                    if(_vector.at(k).at(j) && k!=i) {
                        is_to_delete.at(j) = true;
                        break;
                    }
                }
            }
            
            
        }
        bool to_delete = true;
        for (int j = 0; j < is_to_delete.size(); ++j) {
            if(!is_to_delete.at(j)) {
                to_delete = false;
                break;
            }
        }
        if(to_delete) {
            cout<<" Deleted "<<i<<" row\n";
            rows_to_delete.push_back(i);
            break;
        }
        
    }


    return rows_to_delete;

}

void Minimization::CalculateMethod(const set<vector<string>> &glued_formula, vector<vector<string>> _initial_formule) {
    vector<vector<string>> glued_vector =  vector<vector<string>>(glued_formula.begin(), glued_formula.end());
    vector<vector<bool>> table;
    table.resize(glued_formula.size(), vector<bool>(_initial_formule.size()));
    for (int i = 0; i < glued_vector.size(); ++i) {
        for (int j = 0; j < _initial_formule.size(); ++j) {
            if (Minimization::IsAinB(glued_vector.at(i), _initial_formule.at(j)))
                table[i][j] = true;
            else
                table[i][j] = false;

        }
    }
    cout<<"\n odd implicants solved\n";
    vector<size_t> rows_to_delete = this->DelteOddRowsFromTable(table);

    vector<vector<string>> vec_glued_formula (glued_formula.begin(), glued_formula.end());
    cout<<"Minimized formula :   ";
    for (int i = 0; i < vec_glued_formula.size(); ++i) {
        if(!rows_to_delete.empty()) {
            if (i == rows_to_delete.at(0))
                continue;
            else
            {
                cout << "  -  ";
                this->PrintVector(vec_glued_formula.at(i));
            }
        }
        else {
            cout << "  -  ";
            this->PrintVector(vec_glued_formula.at(i));
        }
    }
    cout<<endl<<endl;

}

void Minimization::PrintCalcMethod() {
    cout<<"\n  ------------------  Calculation method for SDNF -------------------------\n";
    this->CalculateMethod(this->Minimize(true), this->SDNFParser());
    cout<<"\n  ------------------  Calculation method for SKNF -------------------------\n";
    this->CalculateMethod(this->Minimize(false), this->SKNFParser());
}




void Minimization::FillKarnoMap() {
    if(atomar_formules.size()==2)
    {
        this->VHeaders = this->HHeaders = vector<pair<int, string>>{make_pair(0, "0"), make_pair(1, "1")};
        this->KarnoMap.resize(2, vector<pair<string,bool>>(2));
    }
    else if (atomar_formules.size()==3)
    {
        this->HHeaders = vector<pair<int, string>>{make_pair(0, "00"), make_pair(1, "01"), make_pair(2, "11"), make_pair(3, "10")};
        this->VHeaders = vector<pair<int, string>>{make_pair(0, "0"), make_pair(1, "1")};
        this->KarnoMap.resize(2, vector<pair<string,bool>>(4));
    } else if (atomar_formules.size() == 4)
    {
        this->HHeaders = this->VHeaders = vector<pair<int, string>>{make_pair(0, "00"), make_pair(1, "01"), make_pair(2, "11"), make_pair(3, "10")};
        this->KarnoMap.resize(4, vector<pair<string,bool>>(4));
    }
    else
    {
        cerr<<"Unexpected amount of atomar formulas";
        exit(-1);
    }



    if(this->atomar_formules.size()==2) {
        for (int i = 0; i < this->rows; ++i) {
            int a_index, b_index;
            bool result = false;
            if(this->sheet[i][0])
                a_index = 1;
            else
                a_index = 0;
            if(this->sheet[i][1])
                b_index = 1;
            else
                b_index = 0;

            if(this->sheet[i][columns-1])
                result = true;

            this->KarnoMap[b_index][a_index].second = result;
            this->KarnoMap[b_index][a_index].first = to_string(a_index) + to_string(b_index);

        }
    }
    else if (this->atomar_formules.size()==3)
    {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 4; ++j) {
                string implicant_index = this->VHeaders.at(i).second + this->HHeaders.at(j).second;
                bool result = false;
                bool is_found = false;
                for (int k = 0; k < rows; ++k) {
                    for (int l = 0; l < 3; ++l) {
                        if(this->sheet[k][l]==(implicant_index[l]-'0')) {
                           is_found = true;
                        }else
                        {
                            is_found = false;
                            break;
                        }
                    }
                    if(is_found) {
                        result = sheet[k][this->columns - 1];
                        this->KarnoMap[i][j].second = result;
                        this->KarnoMap[i][j].first = implicant_index;
                        break;
                    }

                }
            }
        }
    }
    else if (this->atomar_formules.size()==4)
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                string implicant_index = this->VHeaders.at(i).second + this->HHeaders.at(j).second;
                bool result = false;
                bool is_found = false;
                for (int k = 0; k < rows; ++k) {
                    for (int l = 0; l < 4; ++l) {
                        if(this->sheet[k][l]==(implicant_index[l]-'0')) {
                            is_found = true;
                        }else
                        {
                            is_found = false;
                            break;
                        }
                    }
                    if(is_found) {
                        result = sheet[k][this->columns - 1];
                        this->KarnoMap[i][j].second = result;
                        this->KarnoMap[i][j].first = implicant_index;
                        break;
                    }

                }
            }
        }
    }else
    {
        cerr<<"Unexpected amount of atomar formulas";
        exit(-1);
    }

}


// Function to check if a sub-array of size (rows x cols) starting at (r, c) is valid and contains only `value` elements
bool isValidRectangle(const vector<vector<pair<string, bool>>>& KarnoMap, int r, int c, int rows, int cols, bool value) {
    int maxRows = KarnoMap.size();
    int maxCols = KarnoMap[0].size();
    if (r + rows > maxRows || c + cols > maxCols) return false;
    for (int i = r; i < r + rows; ++i) {
        for (int j = c; j < c + cols; ++j) {
            if (KarnoMap[i][j].second != value) return false;
        }
    }
    return true;
}

// Function to find all valid rectangles of specified sizes and store them in the result vector
void findRectangles(const vector<vector<pair<string, bool>>>& KarnoMap, vector<vector<pair<string, bool>>>& result, bool searchValue) {
    int rows = KarnoMap.size();
    if (rows == 0) return;
    int cols = KarnoMap[0].size();

    // Iterate over all possible sizes 2^n x 2^n, 1 x 2^n, 2^n x 1, 2 x 4, and 4 x 2
    for (int size = 0; (1 << size) <= max(rows, cols); ++size) {
        int sz = 1 << size;

        // Check for squares of size 2^n x 2^n
        if (sz <= min(rows, cols)) {
            for (int r = 0; r <= rows - sz; ++r) {
                for (int c = 0; c <= cols - sz; ++c) {
                    if (isValidRectangle(KarnoMap, r, c, sz, sz, searchValue)) {
                        vector<pair<string, bool>> square;
                        for (int i = r; i < r + sz; ++i) {
                            for (int j = c; j < c + sz; ++j) {
                                square.push_back(KarnoMap[i][j]);
                            }
                        }
                        result.push_back(square);
                    }
                }
            }
        }

        // Check for rectangles of size 1 x 2^n
        if (sz <= cols) {
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c <= cols - sz; ++c) {
                    if (isValidRectangle(KarnoMap, r, c, 1, sz, searchValue)) {
                        vector<pair<string, bool>> rectangle;
                        for (int j = c; j < c + sz; ++j) {
                            rectangle.push_back(KarnoMap[r][j]);
                        }
                        result.push_back(rectangle);
                    }
                }
            }
        }

        // Check for rectangles of size 2^n x 1
        if (sz <= rows) {
            for (int r = 0; r <= rows - sz; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (isValidRectangle(KarnoMap, r, c, sz, 1, searchValue)) {
                        vector<pair<string, bool>> rectangle;
                        for (int i = r; i < r + sz; ++i) {
                            rectangle.push_back(KarnoMap[i][c]);
                        }
                        result.push_back(rectangle);
                    }
                }
            }
        }
    }

    // Check for rectangles of size 2 x 4
    if (rows >= 2 && cols >= 4) {
        for (int r = 0; r <= rows - 2; ++r) {
            for (int c = 0; c <= cols - 4; ++c) {
                if (isValidRectangle(KarnoMap, r, c, 2, 4, searchValue)) {
                    vector<pair<string, bool>> rectangle;
                    for (int i = r; i < r + 2; ++i) {
                        for (int j = c; j < c + 4; ++j) {
                            rectangle.push_back(KarnoMap[i][j]);
                        }
                    }
                    result.push_back(rectangle);
                }
            }
        }
    }

    // Check for rectangles of size 4 x 2
    if (rows >= 4 && cols >= 2) {
        for (int r = 0; r <= rows - 4; ++r) {
            for (int c = 0; c <= cols - 2; ++c) {
                if (isValidRectangle(KarnoMap, r, c, 4, 2, searchValue)) {
                    vector<pair<string, bool>> rectangle;
                    for (int i = r; i < r + 4; ++i) {
                        for (int j = c; j < c + 2; ++j) {
                            rectangle.push_back(KarnoMap[i][j]);
                        }
                    }
                    result.push_back(rectangle);
                }
            }
        }
    }

    // Check for rectangles of size 4 x 4
    if (rows >= 4 && cols >= 4) {
        for (int r = 0; r <= rows - 4; ++r) {
            for (int c = 0; c <= cols - 4; ++c) {
                if (isValidRectangle(KarnoMap, r, c, 4, 4, searchValue)) {
                    vector<pair<string, bool>> rectangle;
                    for (int i = r; i < r + 4; ++i) {
                        for (int j = c; j < c + 4; ++j) {
                            rectangle.push_back(KarnoMap[i][j]);
                        }
                    }
                    result.push_back(rectangle);
                }
            }
        }
    }
}


void Minimization::FindBlocks(bool is_SDNF) {

    vector<vector<pair<string, bool>>> expanded_karno= this->ExpandKarno();



    findRectangles(expanded_karno, blocks, is_SDNF);

// -----------  PRINT RECTANGLES ---------
//    cout << "Rectangles:" << endl;
//    for (const auto &rectangle: blocks) {
//        if(rectangle.size()==1)
//            continue;
//        cout<<"\n { ";
//        for (const auto & i : rectangle) {
//            cout<<" [" << i.first << "] ";
//        }
//        cout<<" } ";
//    }

    SetVecPair set(blocks.begin(), blocks.end());

    removeSubsets(set);

    removeDoubledRectangles(set);

    blocks = vector<VecPair>(set.begin(), set.end());

    cout<<"\n\n ----------- FOUND RECTANGLES ----------\n\n";
    for (const auto &rectangle: blocks) {
        cout<<"\n { ";
        for (const auto & i : rectangle) {
            cout<<" [" << i.first << "] ";
        }
        cout<<" } ";
    }
}

using VecPair = std::vector<std::pair<std::string, bool>>;
using SetVecPair = std::set<VecPair>;

// Helper function to check if vector a is a subset of vector b
bool isSubset(const VecPair& a, const VecPair& b) {
    if(a.size()>b.size())
        return false;
    return std::all_of(a.begin(), a.end(), [&b](const std::pair<std::string, bool>& p) {
        return std::find(b.begin(), b.end(), p) != b.end();
    });
}

void Minimization::removeSubsets(SetVecPair& setA) {
    // Create a vector to hold vectors that are not subsets of any other vector
    SetVecPair result;

    for (const auto& vec : setA) {
        bool isSubsetOfAnother = false;
        for (const auto& other : setA) {
            if (vec != other && isSubset(vec, other)) {
                isSubsetOfAnother = true;
                break;
            }
        }
        if (!isSubsetOfAnother) {
            result.insert(vec);
        }
    }

    // Update the original set to hold only the vectors that are not subsets
    setA = std::move(result);
}



vector<vector<pair<string, bool>>> Minimization:: ExpandKarno() {
    vector<vector<pair<string, bool>>> table = KarnoMap;
    int originalRows = table.size();
    int originalCols = table[0].size();

    int newRows = originalRows * 2;
    int newCols = originalCols * 2;

    vector<vector<pair<string, bool>>> expandedTable(newRows, vector<pair<string, bool>>(newCols));

    for (int i = 0; i < originalRows; ++i) {
        for (int j = 0; j < originalCols; ++j) {
            expandedTable[i][j] = table[i][j];
            expandedTable[i + originalRows][j] = table[i][j];
            expandedTable[i][j + originalCols] = table[i][j];
            expandedTable[i + originalRows][j + originalCols] = table[i][j];
        }
    }
    return expandedTable;
}

void Minimization::PrintKarno() {
    cout<<"  ";
    for (int i = 0; i < this->HHeaders.size(); ++i) {
        cout<<"   "<<HHeaders.at(i).second;
    }
    cout<<endl;
    for (int i = 0; i < KarnoMap.size(); ++i) {
        cout<<"   "<<VHeaders.at(i).second;
        for (auto & j : KarnoMap.at(i)) {
            cout<<"   "<<j.second;
        }
        cout<<endl;
    }
    cout<<endl;
}

void Minimization::removeDoubledRectangles(SetVecPair& setA) {
    for (auto it = setA.begin(); it != setA.end(); ) {
        VecPair& vec = const_cast<VecPair&>(*it);
        size_t n = vec.size();

        if (n % 2 == 0) {
            // Check if first half is identical to the second half
            auto first_half = vec.begin();
            auto second_half = vec.begin() + n / 2;

            if (std::equal(first_half, second_half, second_half)) {
                vec.erase(second_half, vec.end());
            }
        }

        ++it;
    }
}




void Minimization::KarnoMethod() {
    cout<<"\n\n -------- KARNO METHOD -----------------\n\n";

    FillKarnoMap();
    PrintKarno();
    cout<<"\n\n ------------ SDNF MINIMIZATION ----------\n\n";
    FindBlocks(true);
    CalculateNF(true);


    this->blocks.clear();
    cout<<"\n\n ------------ SKNF MINIMIZATION ----------\n\n";
    FindBlocks(false);
    CalculateNF(false);
}

void Minimization::CalculateNF(bool falg) {
    string NF;
    for (const auto & block : blocks) {
        vector<string> bytes = findConsistentBytes(block, falg);
        NF+=" ( ";
        for (auto byte : bytes) {
            for(auto byt : byte) {
                if (byt == '!') {
                    NF += "!";
                    continue;
                }
                if (byt =='0')
                    NF += "A ";
                else if (byt == '1')
                    NF += "B ";
                else if (byt == '2')
                    NF += "C ";
                else if (byt == '3')
                    NF += "D ";
            }
        }
        NF+=") ";
        if(falg)
            NF+=" || ";
        else
            NF+=" && ";
    }
    cout<<"\n -----------  NF: -------\n\n";
    cout<<NF<<endl<<endl;

}

vector<string> Minimization::findConsistentBytes(const vector<pair<string, bool>>& strings, bool flag) {
    if (strings.empty()) return {};

    // Determine the length of the strings (assuming they are all the same length)
    size_t length = strings[0].first.size();

    // Vector to store the indices of consistent bytes
    std::vector<string> consistentByteIndices;

    // Loop through each byte position
    for (size_t byteIndex = 0; byteIndex < length; ++byteIndex) {
        bool isConsistent = true;
        char firstByte = strings[0].first[byteIndex];

        // Compare the byte at the current index across all strings
        for (const auto& str : strings) {
            if (str.first[byteIndex] != firstByte) {
                isConsistent = false;
                break;
            }
        }

        // If the byte is consistent across all strings, record its index
        if (isConsistent) {
            if((flag && strings[0].first[byteIndex]=='0') || (!flag && strings[0].first[byteIndex]=='1'))
                consistentByteIndices.push_back("!"+to_string(byteIndex));
            else
                consistentByteIndices.push_back(to_string(byteIndex));

        }
    }

    return consistentByteIndices;
}