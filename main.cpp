#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdio>
using namespace std;

class Question
{
   char question[256];
    char op1[256];
    char op2[256];
    char op3[256];
    char op4[256];
    char correct_answer;
public:
    void enter(){
        cout << "Enter question :";
        cin>>question;
        
        cout <<"Enter option a :";
        gets(op1);
       
        cout<< "Enter option b : ";
        gets(op2);

        cout<< "Enter option c : ";
        gets(op3);

        cout << "Enter option d : ";
        gets(op4);

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