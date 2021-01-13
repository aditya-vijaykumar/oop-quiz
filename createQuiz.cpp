#include <fstream>
#include <iostream>
#include<string.h>
#include <conio.h>
#include <cstdio>
using namespace std;

class Question
{
public:
    string question;
    string op1;
    string op2;
    string op3;
    string op4;
    string correct_answer;

    void enter(){
       cout << "Enter question :";
        getline(cin, question, '$');

        cout <<"Enter option a :";
        getline(cin, op1, '$');

        cout<< "Enter option b : ";
        getline(cin, op2, '$');

        cout<< "Enter option c : ";
        getline(cin, op3, '$');

        cout << "Enter option d : ";
        cin >> op4;
        getline(cin, op4, '$');

        cout << "Enter correct answer : ";
        getline(cin, correct_answer, '$');

    }
};

int main(){
    char filename[200];
    int n;
    cout << "Enter number of questions : ";
    cin >> n;
    cout << "Enter the Quiz Name (it will also be the file name)";
    cin >> filename;
    Question q[n];
    for(int i=0; i<n; i++)
        q[i].enter();
    
    int i =0;
    while(filename[i]!= '\0')
        i++;

    filename[i] = '.';
    filename[i+1] = 't';
    filename[i+2] = 'x';
    filename[i+3] = 't';
    filename[i+4] = '\0';

    ofstream fout(filename, ios::out);
    if(!fout)
    {   
        cout << "Error in opening file";   
        return -1;
    }
     for(int i=0; i<n; i++){
        fout << q[i].question;
        fout << q[i].op1;
        fout << q[i].op2;
        fout << q[i].op3;
        fout << q[i].op4;
        fout << q[i].correct_answer;
    }
    fout.close();
    
    return 0;
}