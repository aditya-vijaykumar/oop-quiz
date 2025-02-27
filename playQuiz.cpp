#include <iostream> 
#include <string>
#include <string.h>
#include <fstream>

char easyScoreFile[256] = "Easy_Score.dat";
char hardScoreFile[256] = "Hard_Score.dat";
char easyFile[256] = "Easy_Questions.txt";
char hardFile[256] = "Hard_Questions.txt";

#define n 5

using namespace std;

class Player            //Player class 
{
    string name;
    int score;
    int wrong;
    int correct;
public:
    Player(){
        score = 0;
        wrong = 0;
        correct = 0;
    }
    void setName(string currentName){
        name = currentName;
    }
    void setScore(int newScore){
        score = newScore;
    }
    string getName(){
        return name;
    }
    int getScore(){
        return score;
    }
};

class Difficulty {
    public:
        int total; //Total score.
        char file[256]; 
        char score[256];
        virtual void updateScore(bool ans) = 0;
        Difficulty(){
            total = 0;
        }  
};

class Easy: public Difficulty{
    public:
        Easy(){
            strcpy(file, easyFile);
            strcpy(score, easyScoreFile);
        }
        void updateScore(bool ans){
            if(ans)
                total+=4;
            return;
        }
};

class Hard: public Difficulty{
    public:
        Hard(){
            strcpy(file, hardFile);
            strcpy(score, hardScoreFile);
        }
        void updateScore(bool ans){
            if(ans)
                total+=4;
            else{
                total-=1;
            }
        }
};

struct Question{
public:
    string question;
    string op1;
    string op2;
    string op3;
    string op4;
    string correct_answer;

    void askQuestion();
};


//Inserts Player score with name in decreasing order according to score
void insertScore(char* filename, Player p){
    Player temp;
    bool copied = false;
    fstream fin(filename, ios::in | ios::binary);
    fstream fout("temp", ios::out | ios::binary);
    if(!fin || !fout)
    {
        cout << "insert Error in opening file ";
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
    rename("temp", filename);
}

//Displays the content of the binary file containing all the scores 
void displayScore(char* filename)
{
    Player temp;
    ifstream fin(filename, ios::in | ios::binary);
    if(!fin){
        cout << " display Error in opening file";
        return;
    }
    cout << "Name" << '\t' << "Score" << '\n';
    while(fin.read((char *) &temp, sizeof(Player)))
        cout << temp.getName() << '\t' << temp.getScore() << '\n';

    fin.close();
}

Difficulty *ptr; //Base class pointer for virtualization
string guess; //Answer user inputs for question.


int main()
{
    system("cls");

    cout << "Press enter to start...\n";
    cin.get();

    //Get the user's name.
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
    }else{
        cout << "\n";
        cout << "Goodbye!\n";
        cin.get();
        cin.ignore();
        return 0;
    }//Else, quiz ends.4

    Easy easy;
    Hard hard;

    cout << "Enter 'Easy' for easy level and 'Hard' for Hard level.\n";
    cin >> respond;
    
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

    ifstream loadQ(ptr->file);

    //Loading the questions
    Question q[n];
    string str;
    for(int i=0; i<n; i++){
        getline(loadQ, q[i].question);
        getline(loadQ, q[i].op1);
        getline(loadQ, q[i].op2);
        getline(loadQ, q[i].op3);
        getline(loadQ, q[i].op4);
        getline(loadQ, q[i].correct_answer);
   
        q[i].askQuestion();
   }

    //Final score displayed when user finishes quiz.
    cout << "Your Total Score is " << ptr->total << " out of 20!\n";
    cout << "\n";

    Player newPlayer;
    newPlayer.setName(name);
    newPlayer.setScore(ptr->total);
    insertScore(ptr->score, newPlayer);
    displayScore(ptr->score);
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