#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<set>
#include<unordered_set>
#include<utility>


using namespace std;

class Minimization
{
protected:
    vector<vector<bool>> sheet;
    string formula;
    size_t rows, columns;
    vector<char> atomar_formules;
    vector<string> subformules;
    string SKNF;
    string SDNF;
    vector<int> SDNFnumeral;
    vector<int> SKNFnumeral;
private:
    void InitializeSubFormules();
    void CalculateSpreadSheet();
    bool IsInAtomar(char _atomar);
    void CalculateAtomarFormules();
    void CalculateSubFormule(string _formule);
    size_t FindAtomarFormuleIndex(char _formule);
    size_t FindSubFormuleIndex(string _formule);
    void FillTheTable(size_t _a_op, size_t _b_op, size_t _formule_index, char _operation);
    bool SwitchOperation(char _op, bool _a, bool _b);
    void CalculateDenial(size_t _a, size_t _formule_index);
    void CalculateSDNF();
    void CalculateSKNF();


    vector<vector<string>> SDNFParser();
    vector<vector<string>> SKNFParser();
    vector<string> CompareFormules(vector<string> _formule1, vector<string> _formule2);
    static void PrintVector(const vector<string>& _vector);
    pair<set<vector<std::string>>, bool> GlueingFormules(vector<vector<std::string>> _formule_parsed);
    bool IsAllGlued(const set<vector<string>>& _set);
    set<vector<string>> Minimize(bool is_sdnf);
    static bool IsAinB(const vector<string>& A, const vector<string>& B);
    void TableMethod(const set<vector<string>>& glued_formula, vector<vector<string>> _initial_formule);
    vector<size_t> DelteOddRowsFromTable(vector<vector<bool>> _vector);
    void CalculateMethod(const set<vector<string>>& glued_formula, vector<vector<string>> _initial_formule);
    static int StrLengthInVector(const vector<string> &_vec);


    vector<vector<pair<string, bool>>> KarnoMap;
    vector<pair<int, string>> HHeaders;
    vector<pair<int, string>> VHeaders;

    vector<vector<pair<string, bool>>> blocks;

public:
    //--------- KARNO -------------

    using VecPair = std::vector<std::pair<std::string, bool>>;
    using SetVecPair = std::set<VecPair>;

    void FillKarnoMap();
    void removeSubsets(SetVecPair & setA);
    void removeDoubledRectangles(SetVecPair & setA);
    void FindBlocks(bool is_SDNF);
    vector<vector<pair<string, bool>>> ExpandKarno();
    void KarnoMethod();
    void CalculateNF(bool falg);
    vector<string> findConsistentBytes(const vector<pair<string, bool>>& strings, bool flag);





    string index_form;
    Minimization(string _formula);
    void PrintFormules();
    void Printsheet();
    void PrintTableMethod();
    void PrintCalcMethod();
    void PrintKarno();
};