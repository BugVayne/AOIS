#include "Matrix.h"

Matrix::Matrix() {
    cout<<" 1 - random words\n 2 - all words are 0\n";
    bool is_random = true;
    if(cin.get()=='2')
        is_random = false;
    this->matrix.resize(16, vector<bool>(16, false));
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if(is_random)
                this->matrix.at(i).at(j)=rand()%2;
            else
                this->matrix.at(i).at(j)=false;
        }
    }
}

void Matrix::ShowMatrix() {
    cout<<"\n \t\t---   MATRIX   ---\n\n";
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j)
            cout<<"  "<<this->matrix.at(i).at(j);
        cout<<endl;
    }
}

void Matrix::SetWord(int index, vector<bool> word) {
    for (int i = index; i < 16; ++i) {
        this->matrix[i][index] = *word.begin();
        word.erase(word.begin());
    }
    for (int i = 0; i < index; ++i) {
        this->matrix[i][index] = *word.begin();
        word.erase(word.begin());
    }

}

vector<bool> Matrix::GetWord(int index) {
    vector<bool> result;
    result.reserve(16);
    for (int i = index; i < 16; ++i)
        result.push_back(this->matrix[i][index]);
    for (int i = 0; i < index; ++i)
        result.push_back(this->matrix[i][index]);
    return result;}

vector<bool> Matrix::GetAdressColumn(int index) {
    vector<bool> result;
    result.reserve(16);

    for (int i = 0; i < 16-index; ++i) {
        result.push_back(this->matrix[i+index][i]);
    }
    for (int i = 16-index; i < 16; ++i) {
        result.push_back(this->matrix[i+index-16][i]);
    }

    return result;}

void Matrix::Disparity(int i1, int i2, int i3) {
    vector<bool> vec1 = this->GetWord(i1);
    vector<bool> vec2 = this->GetWord(i2);
    vector<bool> result(16, false);
    for (int i = 0; i < 16; ++i)
        if(vec1[i]!=vec2[i])
            result.at(i)=true;
    this->SetWord(i3, result);
}

void Matrix::Equivalence(int i1, int i2, int i3) {
    vector<bool> vec1 = this->GetWord(i1);
    vector<bool> vec2 = this->GetWord(i2);
    vector<bool> result(16, false);
    for (int i = 0; i < 16; ++i)
        if(vec1[i]==vec2[i])
            result.at(i)=true;
    this->SetWord(i3, result);
}

void Matrix::DenialForSecond(int i1, int i2, int i3) {
    vector<bool> vec1 = this->GetWord(i1);
    vector<bool> vec2 = this->GetWord(i2);
    vector<bool> result(16, false);
    for (int i = 0; i < 16; ++i)
        if(!vec2[i])
            result.at(i)=true;
    this->SetWord(i3, result);
}

void Matrix::Implication(int i1, int i2, int i3) {
    vector<bool> vec1 = this->GetWord(i1);
    vector<bool> vec2 = this->GetWord(i2);
    vector<bool> result(16, false);
    for (int i = 0; i < 16; ++i)
        if(!(vec2[i] && !vec1[i]))
            result.at(i)=true;
    this->SetWord(i3, result);
}

void Matrix::Addition(const string& V) {

    cout<<" found V at ";
    for (int i = 0; i < 16; ++i) {
        vector<bool> word = this->GetWord(i);
        string temp_string;
        for (int j = 0; j < 3; ++j)
            temp_string+=to_string(word.at(j));
        if(V==temp_string) {
            this->OperAdd(i);
            cout << i << ", ";
        }
    }
    cout<<endl;
}

void Matrix::OperAdd(int index) {
    vector<bool> new_vector = this->GetWord(index);
    int is_next_rank = 0;
    for (int i = 6; i > 2; --i) {
        int sum = new_vector.at(i)+new_vector.at(i+4);
        sum+=is_next_rank;
        new_vector.at(i+9)=sum%2;
        if(sum == 3 || sum == 2)
            is_next_rank = 1;
        else
            is_next_rank = 0;
    }
        new_vector.at(11) = is_next_rank;
    this->SetWord(index, new_vector);
}

void Matrix::ShowWords() {
    cout<<"\n\t\t---   WORDS   ---\n\n";
    for (int i = 0; i < 16; ++i) {
        cout<<" ["<<i<<"]: ";
        Matrix::PrintVector(this->GetWord(i));
        cout<<endl;
    }
}

int Matrix::IndexInput() {
    cout<<" - Enter index: \n";
    int index;
    string input;
    while (true){
        getline(cin, input);
        if (input.empty()) {
            cout << " - Input is empty, try again:\n";
            continue;
        }
        try {
            size_t pos;
            index = stoi(input, &pos);
            if (pos != input.size())
                throw invalid_argument("pos != size");
            if (index < 0 || index > 15)
                throw invalid_argument("out of matrix size");
        }
        catch (const std::invalid_argument &e) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n\tERROR: " << e.what() <<", try again:\n"<< endl;
            SetConsoleTextAttribute(hConsole, 7);
            continue;}
        break;}
    return index;
}

vector<bool> Matrix::WordInput() {
    vector<bool> word;
    cout<<" - Enter word:\n";
    string input;
    while(true)
    {
        getline(cin, input);
        for (int i = 0; i < input.length(); ++i) {
            if(input[i]==' ')
                input.erase(i, 1);
        }
        if (input.empty()) {
            cout << " - Input is empty, try again:\n";
            continue;
        }
        if(input.size()!=16)
        {
            cout<<" - not enough characters, try again:\n";
            continue;
        }
        try{
            size_t pos;
            stoll(input, &pos);
            if(pos!=input.size())
                throw invalid_argument("pos != size");
            for (char i : input) {
                if (!(i == '0' || i == '1'))
                    throw invalid_argument("only binary input");
                word.push_back(i-48);
            }
        }
        catch (const std::invalid_argument &e)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "\n\tERROR: " << e.what() <<", try again: \n"<< endl;
            SetConsoleTextAttribute(hConsole, 7);
            continue;}
        break;}
    return word;
}

void Matrix::Menu() {
    this->ShowMatrix();
    bool cont = true;
    while(cont)
    {
        cout<<"\n 1 - get word\n 2 - set word\n 3 - logic operation\n 4 - addition\n 5 - show matrix\n 6 - show all words\n 7 - get address column \n 8 - sort\n 9 - exit\n";
        switch(Matrix::IndexInput())
        {
            case 1:
            {
                Matrix::PrintVector(this->GetWord(Matrix::IndexInput()));
                cout<<endl;
                break;
            }
            case 2:
            {
                cout<<"case 2:";//-------
                this->SetWord(Matrix::IndexInput(), Matrix::WordInput());
                break;
            }
            case 3:
            {
                cout<<" 1 - disparity\n 2 - equivalence\n 3 - denial for second\n 4 - implication\n";
                switch(Matrix::IndexInput())
                {
                    case 1: {
                        cout << " enter 1 operand index, 2 operand index and index for result:\n";
                        this->Disparity(Matrix::IndexInput(), Matrix::IndexInput(), Matrix::IndexInput());
                        break;
                    }
                    case 2:
                    {
                        cout << " enter 1 operand index, 2 operand index and index for result:\n";
                        this->Equivalence(Matrix::IndexInput(), Matrix::IndexInput(), Matrix::IndexInput());
                        break;
                    }
                    case 3:
                    {
                        cout << " enter 1 operand index, 2 operand index and index for result:\n";
                        this->DenialForSecond(Matrix::IndexInput(), Matrix::IndexInput(), Matrix::IndexInput());
                        break;
                    }
                    case 4:
                    {
                        cout << " enter 1 operand index, 2 operand index and index for result:\n";
                        this->Implication(Matrix::IndexInput(), Matrix::IndexInput(), Matrix::IndexInput());
                        break;
                    }
                    default:
                    {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "\n\tWRONG CHOICE " << endl;
                        SetConsoleTextAttribute(hConsole, 7);
                        break;
                    }

                }
                break;
            }
            case 4:
            {
                cout<<" Enter V:\n";
                string V;
                getline(cin, V);
                this->Addition(V);
                break;
            }
            case 5:
            {
                this->ShowMatrix();
                break;
            }
            case 6:
            {
                this->ShowWords();
                break;
            }
            case 7:
            {
               Matrix::PrintVector(this->GetAdressColumn(Matrix::IndexInput()));
               cout<<endl;
               break;
            }
            case 8:
            {
                this->Sort();
                break;
            }
            default:
                cont = false;
                break;
        }
    }
    return;
}

bool Matrix::Comparison(const vector<bool>& word1, const vector<bool>& word2) {
    int g0, l0, g, l;
    g0 = l0 = 0;
    for (int i = 0; i < 16; ++i) {
        if (word1.at(i) == 0 && word2.at(i) == 1 && l0 == 0)
            g = 1;
        else if (g0 == 1)
            g = 1;
        else
            g = 0;
        if (word1.at(i) == 1 && word2.at(i) == 0 && g0 == 0)
            l = 1;
        else if(l0 == 1)
            l = 1;
        else
            l = 0;
        g0 = g;
        l0 = l;
    }

    if (g == 1 && l == 0)
        return false;
    if (g == 0 && l == 1)
        return true;
    if (g == 0 && l == 0)
        return false;
    return false;
}

void Matrix::Sort() {
    vector<vector<bool>> words;
    words.reserve(16);
    for (int i = 0; i < 16; ++i) {
        words.push_back(this->GetWord(i));
    }
    cout<<"\n\n\t   ---   INITIAL WORDS   ---\n\n";
    for (int i = 0; i < 16; ++i) {
        Matrix::PrintVector(words.at(i));
        cout<<endl;
    }
    cout<<"\n\n\t   ---   SORTED WORDS   ---\n\n";
    sort(words.begin(), words.end(), Matrix::Comparison);
    for (int i = 0; i < 16; ++i) {
        Matrix::PrintVector(words.at(i));
        cout<<endl;
    }

}
