#include "Cell.h"

int Table::HashFunc(const string &_str) const {
    if(_str.length()<2)
    {
        cerr<<"   ---   Key has not enough characters to calculate hash   ---   \n";
        return -1;
    }
    int hash = (tolower(_str[0]) - 'a' + 1) * 26 + (tolower(_str[1]) - 'a' + 1);
    return hash % this->size;
}

void Table::Add(const string& _key, const string& _value) {
    regex pattern("^[a-zA-Z]+$");
    if(!regex_match(_key, pattern))
    {
        cout<<"   ---   This key cannot be turned into hash   ---\n";
        return;
    }
    int id = this->HashFunc(_key);
    if(id == -1) {
        cerr << "   ---   Unresolved error   ---   \n";
        return;
    }
    bool is_second_try=false;
       while(this->sheet.at(id).key!="empty")
       {
           id+=this->step;
           if(id>this->size-1) {
               if(is_second_try)
               {
                   cout<<" --- ERROR ---\n - There is no place for element with value \""<<_value<<"\" in the sheet\n";
                   return;
               }
               id -= this->size;
               is_second_try=true;
           }

       }


       this->sheet.at(id) = Cell(_key, _value);

    cout<<" - Element with value \""<<_value<<"\" added to "<<id+1<<" place in sheet with key = \""<<_key<<"\""<<endl;
}

void Table::ShowSheet() const {
    cout<<"\n         ---   SHEET   ---   \n\n";
    cout<<"  |  #  |  KEY  | VALUE | \n";
    for (size_t i = 0; i < this->size ;++i) {
        if(i<9)
            cout<<"  |  "<<i+1<<"  | "<<this->sheet.at(i).key<<" | "<<this->sheet.at(i).value<<" | \n";
        else
            cout<<"  |  "<<i+1<<" | "<<this->sheet.at(i).key<<" | "<<this->sheet.at(i).value<<" | \n";

    }
    cout<<endl;
}

void Table::Find(const string &_key) {

    for (Cell & i : this->sheet) {
        if(i.key==_key) {
            cout << " - Value of element with key \"" << _key << "\" = \""<<i.value << "\" \n";
            return;
        }
    }
    cout<<" --- ERROR ---\n - Sheet does not contain element with this key \""<<_key<<"\""<<endl;
}

void Table::Update(const string &_key, const string &_new_val) {
    for (Cell & i : this->sheet) {
        if(i.key==_key) {
            i.value = _new_val;
            cout << " - New value of element with key \"" << _key << "\" = \""<<i.value << "\" \n";
            return;
        }
    }
}

void Table::Delete(const string &_key) {
    for (Cell & i : this->sheet) {
        if(i.key==_key) {
            i.value = "empty";
            i.key = "empty";
            cout << " - Element with key \"" << _key << "\" was removed\n";
            return;
        }
    }
}

void Table::Menu(){
    int choice;
    do{
        choice = 0;
        cout<<" 1 - add note\n 2 - delete note\n 3 - read note\n 4 - update note\n 5 - show sheet\n 0 - exit\n";
        cin>>choice;
        switch (choice) {
            case 1: {
                cout<<" enter key and value:\n";
                string key, value;
                cin>>key>>value;
                this->Add(key, value);
                break;
            }
            case 2:{
                cout<<" enter key:\n";
                string key;
                cin>>key;
                this->Delete(key);
                break;
            }
            case 3:{
                cout<<" enter key:\n";
                string key;
                cin>>key;
                this->Find(key);
                break;
            }
            case 4:{
                cout<<" enter key and value:\n";
                string key, value;
                cin>>key>>value;
                this->Update(key, value);
                break;
            }
            case 5:{
                this->ShowSheet();
                break;
            }
            default:
            {
                cout<<" choice error, try again\n";
                continue;
            }
        }
    }while(choice!=0);
}
