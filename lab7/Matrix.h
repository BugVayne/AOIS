#include<iostream>
#include<vector>
#include <windows.h>
#include<algorithm>
using namespace std;

class Matrix {
private:
    vector<vector<bool>> matrix;
public:
    vector<bool> GetAdressColumn(int index);
    void SetWord(int index, vector<bool> word);
    void Disparity(int i1, int i2, int i3);// или - или
    void Equivalence(int i1, int i2, int i3);// и - и
    void DenialForSecond(int i1, int i2, int i3);// нет
    void Implication(int i1, int i2, int i3);//нет - не
    void OperAdd(int index);
    template <typename T>
    static void PrintVector(vector<T> vec){ for (const auto& elem : vec) cout << "  "<< elem;};
    vector<bool> GetWord(int index);
    void Addition(const string& V);
    static int IndexInput();
    static vector<bool> WordInput();
    static bool Comparison(const vector<bool>& word1, const vector<bool>& word2);
    void Sort();
    void ShowWords();
    void ShowMatrix();


    void Menu();
    Matrix();
};

