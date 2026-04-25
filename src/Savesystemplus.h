// ============================================================
//  SAVE FILE FORMAT (save.txt):
//    Line 1 — money
//    Line 2 — highScore
//    Line 3 — number of scores stored (0–10)
//    Lines 4 to 13 — one past score per line (oldest → newest)
// ============================================================
#ifndef SAVESYSTEMPLUS_H
#define SAVESYSTEMPLUS_H

#include <fstream>
#include <iostream>

const char SAVE_FILE_PLUS[] = "gamedataplus.txt";
const int  MAX_SCORES = 10;         // Rolling history limit

class SaveSystemPlus{
    int scoreHistory[MAX_SCORES]; 
    int scoreCount; // How many scores are stored (0–10)

    public:
    SaveSystemPlus()
    {
        scoreCount = 0;
        for (int i = 0; i < MAX_SCORES; i++)
            scoreHistory[i] = 0;
    }

    // --------------------------------------------------------
    //  addScore(int score)
    //
    //  Pushes a new score into the history array.
    //  If 10 scores are already stored, the oldest one is
    //  dropped (everyone shifts left) to make room]
    // --------------------------------------------------------
    void addScore(int score){
        if (scoreCount < MAX_SCORES)
        {
            // Still have free slots — just append
            scoreHistory[scoreCount] = score;
            scoreCount++;
        }
        else
        {
            // Array is full — shift everything left (drop index 0)
            for (int i = 0; i < MAX_SCORES - 1; i++)
                scoreHistory[i] = scoreHistory[i + 1];

            // Place the new score at the end
            scoreHistory[MAX_SCORES - 1] = score;
            // scoreCount stays at MAX_SCORES (still full)
        }
    }

    // --------------------------------------------------------
    //  getScoreHistory / getScoreCount
    //
    //  Usage:
    //    for (int i = 0; i < saver.getScoreCount(); i++)
    //        draw(saver.getScoreHistory()[i]);
    // --------------------------------------------------------
    const int* getScoreHistory() const { return scoreHistory; }
    int getScoreCount() const { return scoreCount;   }

    // --------------------------------------------------------
    //  saveGame(int money, int highScore)
    //
    //  Writes money, highScore, AND the full score history
    //  to save.txt so nothing is lost between sessions.
    // --------------------------------------------------------
    void saveGame(int money, int highScore){
        std::ofstream outFile(SAVE_FILE_PLUS);
        if (!outFile.is_open())
        {
            std::cout << "[SaveSystemPlus] ERROR: Could not open " << SAVE_FILE_PLUS
                      << " for writing.\n";
            return;
        }

        outFile <<money<< "\n";
        outFile <<highScore<< "\n";
        outFile <<scoreCount<< "\n";              // how many scores follow

        for (int i = 0; i < scoreCount; i++)
            outFile << scoreHistory[i] << "\n";
        outFile.close();
        std::cout << "[SaveSystemPlus] Game saved successfully to "
                  << SAVE_FILE_PLUS << ".\n";
    }

    // --------------------------------------------------------
    //  loadGame(int &money, int &highScore)
    //
    //  Reads money, highScore, AND rebuilds the score history
    //  from gamedataplus.txt into the internal array.
    //  First-run safe: defaults if the file doesn't exist.
    // --------------------------------------------------------
    void loadGame(int &money, int &highScore)
    {
        std::ifstream inFile(SAVE_FILE_PLUS);
        if (!inFile.is_open())
        {
            std::cout << "[SaveSystemPlus] No save file found. "
                      << "Starting with default values.\n";
            money      = 1000;
            highScore  = 0;
            scoreCount = 0;
            return;
        }

        inFile >> money;
        inFile >> highScore;
        inFile >> scoreCount;

        // Guard against a corrupted/unexpected count value
        if (scoreCount < 0)          scoreCount = 0;
        if (scoreCount > MAX_SCORES) scoreCount = MAX_SCORES;

        for (int i = 0; i < scoreCount; i++)
            inFile >> scoreHistory[i];

        inFile.close();
        std::cout << "[SaveSystemPlus] Save file loaded successfully.\n";
    }

    // --------------------------------------------------------
    //  printScoreHistory()
    //  Quick debug helper — prints all stored scores to console.
    // --------------------------------------------------------
    void printScoreHistory()
    {
        std::cout << "[SaveSystemPlus] Score History (" << scoreCount << " entries):\n";
        for (int i = 0; i < scoreCount; i++)
            std::cout << "  #" << (i + 1) << " -> " << scoreHistory[i] << "\n";

        if (scoreCount == 0)
            std::cout << "  (no scores yet)\n";
    }
};

#endif // SAVESYSTEMPLUS_H