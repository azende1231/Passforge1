#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class PasswordGenerator {
private:
    string generatedPassword;
    string specialChars = "!@#$%^&*";

public:
    void forgePassword(vector<string> stringAnswers, vector<string> intAnswers) {
        
        if (stringAnswers.empty()) {
            stringAnswers.push_back("Passforge"); 
        }
        
        if (intAnswers.empty()) {
            intAnswers.push_back(to_string(rand() % 9000 + 1000)); 
        }

        vector<string> passwordOptions;

        for (int i = 0; i < 3; i++) {
            string baseWord = "";
            string numberPart = "";
            
            if (!stringAnswers.empty()) {
                int randStringIdx = rand() % stringAnswers.size();
                baseWord = stringAnswers[randStringIdx];
            }

            if (!intAnswers.empty()) {
                int randIntIdx = rand() % intAnswers.size();
                numberPart = intAnswers[randIntIdx];
            }

            char specialChar = specialChars[rand() % specialChars.length()];
            string tempPassword = baseWord + numberPart + specialChar;

            if (tempPassword.length() > 16) {
                tempPassword = tempPassword.substr(0, 16);
                tempPassword[15] = specialChar; 
            } 
            else if (tempPassword.length() < 8) {
                while (tempPassword.length() < 8) {
                    tempPassword += to_string(rand() % 10); 
                }
            }

            passwordOptions.push_back(tempPassword);
        }

        cout << "\n==================================================" << endl;
        cout << "   [PASSFORGE] Password Generation Complete" << endl;
        cout << "==================================================" << endl;
        cout << "Please select one of the following secure passwords:\n" << endl;

        for (int i = 0; i < passwordOptions.size(); i++) {
            cout << "  " << (i + 1) << ". " << passwordOptions[i] << endl;
        }

        int choice = 0;
        
        while (true) {
            cout << "\nEnter your choice (1, 2, or 3): ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                cin.clear();             
                cin.ignore(10000, '\n'); 
                cout << "[ERROR] Invalid input. Please enter 1, 2, or 3." << endl;
            } else {
                break; 
            }
        }

        generatedPassword = passwordOptions[choice - 1];
        cout << "\n[SUCCESS] You have selected: " << generatedPassword << endl;
    } 

    void savePassword() {
        char choice;
        cout << "\nWould you like to save this password to your CSV vault? (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            string accountName;
            cout << "What account is this password for? (e.g., Gmail, Steam): ";
            
            getline(cin >> ws, accountName); 

            ifstream checkFile("MyPasswords.csv");
            bool isNewFile = !checkFile.is_open(); 
            if (!isNewFile) checkFile.close(); 

            ofstream outFile("MyPasswords.csv", ios::app); 

            if (outFile.is_open()) {
                if (isNewFile) {
                    outFile << "Account,Password\n"; 
                }
                
                outFile << accountName << "," << generatedPassword << "\n";
                outFile.close();
                cout << "[SUCCESS] Password safely logged in MyPasswords.csv!" << endl;
            } else {
                cout << "[ERROR] System could not open the CSV vault." << endl;
            }
        } else {
            cout << "[INFO] Password discarded. Stay safe!" << endl;
        }
    }
};
