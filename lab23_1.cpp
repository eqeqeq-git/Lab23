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

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades) {
    ifstream source;
    source.open(filename);
    string textline;
    char format[] = "%[^:]: %d %d %d";
    char name[100];
    int s1, s2, s3;
    while (getline(source,textline)) {        
        sscanf(textline.c_str(), format, name, &s1, &s2, &s3);
        names.push_back(name);
        scores.push_back(s1 + s2 + s3);
        grades.push_back(score2grade(s1 + s2 + s3));
    }
    source.close();
}


void getCommand(string &command,string &key){
    cout << "Please input your command: " << endl;
    string textline;
    getline(cin,textline);
    char format[] = "%s %[^\n]";
    char a[100];
    char b[100];
    sscanf(textline.c_str(),format,a,b);
    command = a;
    key = b;
}

void searchName(vector<string> name, vector<int> scores, vector<char> grades, string key) {
    bool checker = false;
        cout << "---------------------------------" << endl;
    for (unsigned int i = 0; i < name.size(); i++) {
        if (key == toUpperStr(name[i])) {
            checker = true;
            cout << name[i] << "'s score = " << scores[i] << endl;
            cout << name[i] << "'s grade = " << grades[i] << endl;
        }
    }
    if (checker == false) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}


void searchGrade(vector<string> name, vector<int> scores, vector<char> grades, string key) {
    bool checker = false;
    cout << "---------------------------------" << endl;
    for (unsigned int i = 0; i < grades.size(); i++) {
        if (key[0] == grades[i]) {
            checker = true;
            cout << name[i] << " " << "(" << scores[i] << ")" << endl;
        }
    }
    if (checker == false) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
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
