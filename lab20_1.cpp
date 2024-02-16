#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string my,vector<string>& waifu, vector<int>& so, vector<char>& cute){
    ifstream souced(my);
    string havetext;
    char format[]={"%[^:]: %d %d %d"};
    char names[100],e;
    int a,b,c,d;
    while (getline(souced,havetext))
    {
        sscanf(havetext.c_str(), format, names, &a, &b, &c);
        d = a+b+c;
        waifu.push_back(names);
        so.push_back(d);
        e = score2grade(d);
        cute.push_back(e);
    }
}

void getCommand(string& command, string& key){
    cout << "Please input your command: ";
    cin >> command ;
    if(toUpperStr(command) == "EXIT" || toUpperStr(command) =="NAME" || toUpperStr(command) == "GRADE"){
        cin.ignore();
        getline(cin,key);
    } 
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<names.size();i++){
        if(toUpperStr(key) == toUpperStr(names[i])){
            cout << names[i] <<"'s" << " score = " << scores[i] <<"\n";
            cout << names[i] <<"'s" << " grade = " << grades[i] <<"\n";
            break;
        }
        else{
            if(i == names.size()-1)
            cout << "Cannot found." <<"\n";
        }
    }
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key) {
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i = 0; i < names.size(); i++) {
        if (key.c_str()[0] == grades[i]) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Cannot found." <<"\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
