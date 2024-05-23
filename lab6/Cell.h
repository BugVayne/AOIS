#include<iostream>
#include <utility>
#include<vector>
#include<regex>

using namespace std;

class Cell {
public:
    Cell():key("empty"), value("empty"){};
    Cell(string  _key, string  _val): key(std::move(_key)), value(std::move(_val)){};
    string key;
    string value;
};

class Table{
private:
    int step;
    int size;
    vector<Cell> sheet;
public:
    [[nodiscard]] int HashFunc(const string& _str) const;
    explicit Table(int _size, int _step): size(_size), step(_step){sheet.resize(size);}
    void Add(const string& _key, const string& _value);
    void Find(const string& _key);
    void Update(const string& _key, const string& _new_val);
    void Delete(const string& _key);
    void ShowSheet() const;
    void Menu();
};
