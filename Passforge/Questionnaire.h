#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <cstdlib> 
#include <ctime>

using namespace std;

class Questionnaire {
private:
    vector<string> stringQuestions;
    vector<string> intQuestions;
    
    vector<string> cleanStringAnswers;
    vector<string> cleanIntAnswers;

public:
    Questionnaire() {
        srand(time(0)); 
    }

    bool loadFiles(string stringFilename, string intFilename) {
        string line;

        ifstream sFile(stringFilename);
        if (sFile.is_open()) {
            while (getline(sFile, line)) {
                if (!line.empty()) {
                    stringQuestions.push_back(line);
                }
            }
            sFile.close();
        } else {
            cout << "[ERROR] Could not open " << stringFilename << endl;
            return false; 
        }

        ifstream iFile(intFilename); 
        if (iFile.is_open()) {
            while (getline(iFile, line)) {
                if (!line.empty()) {
                    intQuestions.push_back(line);
                }
            }
            iFile.close();
        } else {
            cout << "[ERROR] Could not open " << intFilename << endl;
            return false;
        }

        return true; 
    }

    void debugPrintCount() {
        cout << "[SUCCESS] Loaded " << stringQuestions.size() << " String Questions and ";
        cout << intQuestions.size() << " Integer Questions." << endl;
    }

    string removeSpaces(string input) {
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
        return input;
    }

    void runSurvey() {
        cleanStringAnswers.clear();
        cleanIntAnswers.clear();

        cout << "\n=======================================" << endl;
        cout << "   PassForge Questionnaire Initialization   " << endl;
        cout << " Type 'skip' if you wish to bypass a question." << endl;
        cout << "=======================================\n" << endl;

        string answer;
        vector<int> usedStrings; 
        
        for (int i = 0; i < 3; i++) {
            int randomIndex;
            
            do {
                randomIndex = rand() % stringQuestions.size();
            } while (count(usedStrings.begin(), usedStrings.end(), randomIndex) > 0);
            
            usedStrings.push_back(randomIndex); 

            cout << stringQuestions[randomIndex] << " ";
            getline(cin >> ws, answer); 

            if (answer != "skip" && answer != "Skip") {
                cleanStringAnswers.push_back(removeSpaces(answer));
            }
        }

        vector<int> usedInts;

        for (int i = 0; i < 2; i++) {
            int randomIndex;
            
            do {
                randomIndex = rand() % intQuestions.size();
            } while (count(usedInts.begin(), usedInts.end(), randomIndex) > 0);
            
            usedInts.push_back(randomIndex);

            cout << intQuestions[randomIndex] << " ";
            getline(cin >> ws, answer);

            if (answer != "skip" && answer != "Skip") {
                cleanIntAnswers.push_back(removeSpaces(answer));
            }
        }
        
        cout << "\n[SUCCESS] Questionnaire Complete. Data cleaned and prepared for PassForge." << endl;
    } 

    vector<string> getStringAnswers() { return cleanStringAnswers; }
    vector<string> getIntAnswers() { return cleanIntAnswers; }
};
