#include<iostream>
#include <fstream>
#include <string>

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
    void disp(){
        cout << question << endl << op1 << endl << op2 << endl << op3 << endl << op4 << endl << correct_answer << endl;
    }
};
// int main(){
//   char line[256];
//   char line1[256];
//   // cout << "Enter line : ";
//   // gets(line);
//   // cin.getline(line, 256, '\n');
//   // cout << line;
//   cout << "Enter line 2 : ";
//   gets(line1);
//   puts(line1);

// }



int main ()
{
  Question q1, q2;
  ifstream file("input.txt");
  string str;

    getline(file, q1.question);
    getline(file, q1.op1);
    getline(file, q1.op2);
    getline(file, q1.op3);
    getline(file, q1.op4);
    getline(file, q1.correct_answer);
  
  q1.disp();

    getline(file, q2.question);
    getline(file, q2.op1);
    getline(file, q2.op2);
    getline(file, q2.op3);
    getline(file, q2.op4);
    getline(file, q2.correct_answer);

  q2.disp();

}