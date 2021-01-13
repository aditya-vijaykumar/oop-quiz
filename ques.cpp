#include <fstream>
#include <iostream>
// #include <char*>
#include<string.h>
#include <conio.h>
#include <cstdio>
using namespace std;

class Question
{
public:
    char correct_answer;
    char question[256];
    char op1[256];
    char op2[256];
    char op3[256];
    char op4[256];
    void enter(){
        cout << "Enter question : ";
        gets(question);
        
        cout <<"Enter option a : ";
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
        // cout << question << endl << op1 << endl << op2 << endl << op3 << endl << op4 << endl << correct_answer << endl;
        puts(question);
        puts(op1);
        puts(op2);
        puts(op3);
        puts(op4);
        cout << correct_answer;

    }
    void setValues(char* q, char* a1, char* a2, char* a3, char* a4, char ca)
    {
    // question = q;
    // op1 = a1;
    // op2 = a2;
    // op3 = a3;
    // op4 = a4;
    strcpy(question, q);
    strcpy(op1, a1);
    strcpy(op2, a2);
    strcpy(op3, a3);
    strcpy(op4, a4);
    correct_answer = ca;
    }
};

int main(){
    char filename[] = "Easy_Questions";
    int n;
    // cout << "Enter number of questions : ";
    // cin >> n;
    // Question q;
    // for(int i=0; i<n; i++)
    //     q.enter();

    // for(int i=0; i<n; i++)
    //     q[i].disp();      
    Question q1;
    Question q2;
    Question q3;
  

    //Calling the member function setValues. 
    //Question is set, 4 answer choices, the correct char answer, 4 points per question.
    strcpy(q1.question,"1. What command prints something to the screen?");
    strcpy(q1.op1, "cin");
    strcpy(q1.op2, "cin");
    strcpy(q1.op3, "cin");
    strcpy(q1.op4, "cin");
    q1.correct_answer = 'a';   

    strcpy(q2.question,"1. What command prints something to the screen?");
    strcpy(q2.op1, "cin");
    strcpy(q2.op2, "cin");
    strcpy(q2.op3, "cin");
    strcpy(q2.op4, "cin");
    q2.correct_answer = 'a';   
    
    
    //  strcpy(q2.question, q);
    // strcpy(q2.op1, a1);
    // strcpy(q2.op2, a2);
    // strcpy(q2.op3, a3);
    // strcpy(q2.op4, a4);
    // q2.correct_answer = ca;    
    
    // strcpy(q3.question, q);
    // strcpy(q3.op1, a1);
    // strcpy(q3.op2, a2);
    // strcpy(q3.op3, a3);
    // strcpy(q3.op4, a4);
    // q3.correct_answer = ca;
    // // q1.setValues("1. What command prints something to the screen?",
    //     "cin",
    //     "cout",
    //     "char",
    //     "print",
    //     'b');

    // q2.setValues("2. Which of the following categories does C++ belong to?",
    //     "Operating System",
    //     "High-level programming language",
    //     "low-level programming language",
    //     "Compiler",
    //     'b');

    // q3.setValues("3. Which command is correctly written?",
    //     "cout >>",
    //     "cin <<",
    //     "cout <>",
    //     "cin >>",
    //     'd');      
    ofstream fout(filename, ios::binary | ios::out);
    if(!fout)
    {   
        cout << "Error in opening file";   
        return -1;
    }
    // for(int i=0; i<n; i++)
        fout.write((char *) &q1, sizeof(Question));
        fout.write((char *) &q2, sizeof(Question));
        // fout.write((char *) &q3, sizeof(Question));

    fout.close();
    

     ifstream loadQ(filename, ios::in | ios::binary);
    if(!loadQ){
        cout << "Error in opening file ";
        return -1;
    }
    Question q[2];
   
for(int i=0; i<2; i++){
            loadQ.read((char *) &q[i], sizeof(Question));
        q[i].disp(); 
}
    return 0;
}