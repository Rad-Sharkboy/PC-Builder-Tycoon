//  SAVE FILE FORMAT (save.txt):
//    Line 1 — money
//    Line 2 — highScore
//    Line 3 — number of scores stored (0–10) [History]

#ifndef SAVESYSTEMPLUS_H
#define SAVESYSTEMPLUS_H

#include <fstream>
#include <iostream>

const char SAVE_FILE_PLUS[]="gamedataplus.txt";
const int  MAX_SCORES = 10;

class SaveSystemPlus{
    int scoreHistory[MAX_SCORES]; 
    int scoreCount; //How many scores are stored (0–10)

    public:
    SaveSystemPlus()
    {
        scoreCount = 0;
        for (int i = 0; i < MAX_SCORES; i++)
            scoreHistory[i]=0;
    }


    //Pushes a new score into the history array.
    //If 10 scores are already stored, the oldest one is dropped (everyone shifts left) to make room
    void addScore(int score){
        if (scoreCount<MAX_SCORES)
        {
            scoreHistory[scoreCount]=score;
            scoreCount++;
        }
        else
        {
            //Array is full — shift everything left (drop index 0)
            for (int i = 0; i<MAX_SCORES-1; i++) scoreHistory[i] = scoreHistory[i+1];

            //Place the new score at the end
            scoreHistory[MAX_SCORES-1]=score;
        }
    }

    const int* getScoreHistory() const {return scoreHistory;}
    int getScoreCount() const {return scoreCount;}


    //Writes money, highScore, AND the full score history to save.txt so nothing is lost between sessions.
    void saveGame(int money, int highScore){
        ofstream outFile(SAVE_FILE_PLUS);
        if (!outFile.is_open())
        {
            cout<<"[SaveSystemPlus.h] ERROR: Could not open "<<SAVE_FILE_PLUS<<" for writing.\n";
            return;
        }

        outFile <<money<< "\n";
        outFile <<highScore<< "\n";
        outFile <<scoreCount<< "\n";

        for (int i = 0; i<scoreCount; i++)
            outFile <<scoreHistory[i]<<"\n";
        outFile.close();
        cout <<"[SaveSystemPlus.h] Game saved successfully to "<<SAVE_FILE_PLUS<<".\n";
    }


    //Reads money, highScore, AND rebuilds the score history from gamedataplus.txt into the internal array.
    //[First-run safe: defaults if the file doesn't exist]

    void loadGame(int &money,int &highScore)
    {
        ifstream inFile(SAVE_FILE_PLUS);
        if (!inFile.is_open())
        {
            cout<<"[SaveSystemPlus.h] No save file found. Starting with default values.\n";
            money = 1000; //Default Money is Customizable
            highScore = 0;
            scoreCount = 0;
            return;
        }

        inFile>>money;
        inFile>>highScore;
        inFile>>scoreCount;

        //Guard against a corrupted/unexpected count value
        if (scoreCount<0) scoreCount=0;
        if (scoreCount>MAX_SCORES) scoreCount=MAX_SCORES;

        for (int i = 0; i<scoreCount; i++)
            inFile >> scoreHistory[i];

        inFile.close();
        cout <<"[SaveSystemPlus.h] Save file loaded successfully.\n";
    }

    void printScoreHistory()
    {
        cout <<"[SaveSystemPlus.h] Score History (" <<scoreCount<<" entries):\n";
        for (int i = 0; i<scoreCount; i++)
            cout <<"  #" <<(i+1)<<" -> "<<scoreHistory[i]<<"\n";

        if (scoreCount==0) cout<<"  (no scores yet)\n";
    }
};

#endif