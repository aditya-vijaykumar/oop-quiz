#include <iostream> 
#include <string>
#include <fstream>

#define easyScoreFile "Easy_Score.dat"
#define hardScoreFile "Hard_Score.dat"
#define easyFile "Easy_Questions.dat"
#define hardFile "Hard_Questions.dat"
 
using namespace std;

Difficulty *ptr;
char guess; //Answer user inputs for question.


class Player  { //Player class 
    string name;
    int score;
public:
    Player(){
        score = 0;
    }
    void setScore(int newScore){
        score = newScore;
    }
    int getScore(){
        return score;
    }
};

class Difficulty {
    public:
        int total; //Total score.
        virtual void updateScore(bool ans) = 0;
        Difficulty(){
            total = 0;
        }  
};

class Easy: public Difficulty{
    public:
        void updateScore(bool ans){
            if(ans)
                total+=4;
        }
};

class Hard: public Difficulty{
    public:
        void updateScore(bool ans){
            if(ans)
                total+=4;
            else{
                total-=1;
            }
        }
};

class Question{
private:
    string question;
    string op1;
    string op2;
    string op3;
    string op4;
    char correct_answer;
public:
    void askQuestion();
};

//Inserts Player score with name in decreasing order according to score
void insertScore(char* filename, Player p){
    Player temp;
    bool copied = false;
    fstream fin(filename, ios::in | ios::binary);
    fstream fout("temp.dat", ios::out | ios::binary);
    if(!fin || !fout)
    {
        cout << "Error in opening file ";
        return;
    }
    while(fin.read((char *)&temp, sizeof(Player) ) ){
        if(temp.getScore() < p.getScore() && !copied){
            fout.write((char *)&p, sizeof(Player));
            copied = true;
        }
        fout.write((char *)&temp, sizeof(Player));
    }
    if(!copied)
        fout.write((char *) &p, sizeof(Player));
    fout.close();
    fin.close();
    remove(filename);
    rename("temp.dat", filename);
}

int main()
{
    //Loading the questions
    ifstream loadQ("Easy_Questions.dat", ios::in | ios::binary);
    if(!loadQ) {
        cout << "Cannot open file.\n";
        return 1;
    }
    Question q[3];
    for(int i = 0; i<3; i++)
        loadQ.read((char *) &q[i], sizeof(Question));
    

    cout << "Press enter to start...\n";
    cin.get();

    //User's name
    string name;
    cout << "What's your name?\n";
    cin >> name;
    cout << "\n";

    //Ask if user wants to start quiz.
    string respond;
    cout << "Are you ready to start the quiz, " << name << "? Yes/No.\n";
    cin >> respond;

    //If user says yes, the quiz begins.
    if (respond == "Yes" || respond == "yes") {
        cout << "\n";
        cout << "Good luck!\n";
        cout << "\n";
        cout << "Press enter to continue.";
        cin.get();
        cin.ignore();
    }else{
        cout << "\n";
        cout << "Goodbye!\n";
        cin.ignore();
        cin.get();
        return 0;
    }

    string respond;
    cout << "Enter 'Easy' for easy level and 'Hard' for Hard level.\n";
    cin >> respond;
    Easy easy;
    Hard hard;

    if (respond == "Easy" || respond == "easy") {
        ptr = &easy;
        cout << "\n";
        cout << "Good luck!\n";
        cout << "\n";
        cout << "Press enter to continue.";
        cin.get();
        cin.ignore();
    }else if(respond == "Hard" || respond == "hard"){
        ptr = &hard;
        cout << "\n";
        cout << "Good luck!\n";
        cout << "\n";
        cout << "Press enter to continue.";
        cin.get();
        cin.ignore();
    }
    else{
        cout << "\n";
        cout << "Goodbye!\n";
        cin.ignore();
        cin.get();
        return 0;
    }

    for(int i = 0; i<3; i++)
        q[i].askQuestion();

    //Final score displayed when user finishes quiz.
    cout << "Your Total Score is " << ptr->total << " out of 100!\n";
    cout << "\n";

    //User scores above a 60, user passes the quiz.
    if (ptr->total > 60) {
        cout << R"(

__  __               ____                           ____
\ \/ /___  __  __   / __ \____ ______________  ____/ / /
 \  / __ \/ / / /  / /_/ / __ `/ ___/ ___/ _ \/ __  / / 
 / / /_/ / /_/ /  / ____/ /_/ (__  |__  )  __/ /_/ /_/  
/_/\____/\__,_/  /_/    \__,_/____/____/\___/\__,_(_)   

    )" << "\n";
        cout << "\n";
        cin.get();
        cin.ignore();
        return 0;
    }
    else
    {
        cout << "You failed... Sorry, better luck next time.\n";
        cout << "\n";
    }
    cin.get();
    cin.ignore();
    return 0;
}

void Question::askQuestion(){
    cout << "\n";
    cout << question << "\n";
    cout << "a. " << op1 << "\n";
    cout << "b. " << op2 << "\n";
    cout << "c. " << op3 << "\n";
    cout << "d. " << op4 << "\n";
    cout << "\n";

    //User enters their answer.
    cout << "What is your answer?" << "\n";
    cin >> guess;
    //If their answer is correct, message is displayed and 4 points are added to their score.
    if (guess == correct_answer) {
        cout << "\n";
        cout << "Correct!" << "\n";
        ptr->updateScore(true);
        cout << "\n";
        cout << "Press enter to continue." << "\n";
        cin.get();
        cin.ignore();
    }
    else //If their answer is incorrect, message is displayed, no points added. 
         //Correct answer displayed. 
    {
        cout << "\n";
        cout << "Sorry, you're wrong..." << "\n";
        ptr->updateScore(false);
        cout << "The correct answer is " << correct_answer << "." << "\n";
        cout << "\n";
        cout << "Press enter to continue." << "\n";
        cin.get();
        cin.ignore();
    }
} 