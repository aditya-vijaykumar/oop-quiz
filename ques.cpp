#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Question
{
    string question;
    string op1;
    string op2;
    string op3;
    string op4;
    char correct_answer;
public:
    void enter(){
        cout << "Enter question : ";
        cin >> question;
        cout << "Enter option a : ";
        cin >> op1;
        // getch();
        cout << "Enter option b : ";
        cin >> op2;
        cout << "Enter option c : ";
        cin >> op3;
        cout << "Enter option d : ";
        cin >> op4;
        cout << "Enter correct answer : ";
        cin >> correct_answer;
    }
    void disp(){
        cout << question << endl << op1 << endl << op2 << endl << op3 << endl << op4 << endl << correct_answer << endl;
    }
};

int main(){
    string filename = "Easy_Questions.dat";
    int n;
    cout << "Enter number of questions : ";
    cin >> n;
    Question q[n];
    for(int i=0; i<n; i++)
        q[i].enter();
    // for(int i=0; i<n; i++)
    //     q[i].disp();        
    ofstream fout(filename, ios::binary | ios::out);
    if(!fout)
    {   
        cout << "Error in opening file";   
        return -1;
    }
    for(int i=0; i<n; i++)
        fout.write((char *) &q[i], sizeof(Question));
    fout.close();
    return 0;
}