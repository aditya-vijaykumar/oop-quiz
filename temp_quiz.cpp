#include <iostream> 
#include <string.h>
#include <string>

#define easyScoreFile "Easy_Score.dat"
#define hardScoreFile "Hard_Score.dat"
#define easyFile "Easy_Questions.dat"
#define hardFile "Hard_Questions.dat"
#define n 10 

using namespace std;

char guess; //Answer user inputs for question.
int total;  //Total score.


class Player            //Player class 
{
    string name;
    int score;
public:
    Player(){
        score = 0;
    }
    void setName(string currentName){
        strcpy(name, currentName);
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

//Inserts Player score with name in decreasing order according to score
void insertScore(char* filename, Player newPlayer){
    Player temp;
    bool copied = false;
    fstream fin(filename, ios::in | ios::binary);
    fstream fout("temp.dat", ios::out | ios::binary);
    if(!fin || !fout)
    {
        cout << "Error in opening file ";
        return;
    }
    while(fin.read((char *)&temp, sizeof(Player))){
        if(temp.getScore < newPlayer.getScore && !copied){
            fout.write((char *)&newPlayer, sizeof(Player));
            copied = true;
        }
        fout.write((char *)&temp, sizeof(Player));
    }
    if(!copied)
        fout.write((char *) &newPlayer, sizeof(Player));
    fout.close();
    fin.close();
    remove(filename);
    rename("temp.dat", filename);
}

//Displays the content of the binary file containing all the scores 
void displayScore(char* filename)
{
    Player temp;
    ifstream fin(filename, ios::in | ios::binary);
    if(!fin){
        cout << "Error in opening file";
        return;
    }
    cout << "Name" << '\t' << "Score" << '\n';
    while(fin.read((char *) &temp, sizeof(Player)))
        cout << temp.getName() << '\t' << temp.getScore() << '\n';

    fin.close();
}

//4 possible answers, correct answer and question score.
class Question{
public:
    void askQuestion(); 

private:
    string Question_Text;
    string answer_1;
    string answer_2;
    string answer_3;
    string answer_4;
    char correct_answer;
};

//Format for possible answers displayed when program executes. 
void Question::askQuestion()
{
    cout << "\n";
    cout << Question_Text << "\n";
    cout << "a. " << answer_1 << "\n";
    cout << "b. " << answer_2 << "\n";
    cout << "c. " << answer_3 << "\n";
    cout << "d. " << answer_4 << "\n";
    cout << "\n";

    //User enters their answer.
    cout << "What is your answer?" << "\n";
    cin >> guess;
    //If their answer is correct, message is displayed and 4 points are added to their score.
    if (guess == correct_answer) {
        cout << "\n";
        cout << "Correct!" << "\n";
        total++;
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
        cout << "The correct answer is " << correct_answer << "." << "\n";
        cout << "\n";
        cout << "Press enter to continue." << "\n";
        cin.get();
        cin.ignore();
    }
}

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
    if (!strcmpi(respond, "yes")) {
        cout << "\n";
        cout << "Good luck!\n";
        cout << "\n";
        cout << "Press enter to continue.";
        cin.get();
        cin.ignore();
    }else{
        cout << "\n";
        cout << "Goodbye!\n";
        cin.get();
        cin.ignore();
        return 0;
    }//Else, quiz ends.

    ifstream fin(easyFile, ios::in | ios::binary);
    if(!fin){
        cout << "Error in opening file ";
        return -1;
    }
    Question q[n];
    for(int i=0; i<n; i++){
        fin.read((char *) &q[i], sizeof(Question));
        q[i].askQuestion();
    }
    

    //Final score displayed when user finishes quiz.
    cout << "Your Total Score is " << total << " out of 100!\n";
    cout << "\n";
    Player newPlayer;
    newPlayer.setName(name);
    newPlayer.setScore(total);
    insertScore(easyScoreFile, newPlayer);
    displayScore(easyScoreFile);
    return 0;
}

