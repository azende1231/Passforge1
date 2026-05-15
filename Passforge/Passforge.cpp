// Passforge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime> // this is for time
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> //This is to remove spaces
#include <cstdlib> //This is for rand and srand

using namespace std;
class User
{
private:
    string userID;
    string password;
    string fname;
    string lname;

public:
    User()
    {
        userID = "";
        password = "";
        fname = "";
        lname = "";
    }

    User(string id, string pwd, string f, string l)
    {
        userID = id;
        password = pwd;
        fname = f;
        lname = l;
    }

    string getUserID() { return userID; }
    string getPassword() { return password; }
    string getFname() { return fname; }
    string getLname() { return lname; }
};

void login(vector<User>& users, int& liu);
void login(vector<User>& users, int& liu)
{
    string entID = "";
    string entPwd = "";
    int numAttempts = 0;
    bool isValid = false;

    do
    {
        cout << "Enter User ID: ";
        cin >> entID;

        cout << "Enter Password: ";
        cin >> entPwd;

        for (int i = 0; i < users.size(); i++)
        {
            if ((entID == users.at(i).getUserID()) &&
                (entPwd == users.at(i).getPassword()))
            {
                isValid = true;
                liu = i;
            }
        }

        numAttempts++;

        if (!isValid)
        {
            cout << "Login Invalid, Try Again!" << endl;
        }

    } while ((numAttempts < 3) && (!isValid));

    if (!isValid)
    {
        cout << "Number of attempts exceeded, program terminated!" << endl;
        exit(0);
    }
    else
    {
        cout << "\nSuccessful Login!" << endl;
    }
}
/****************************************************************************************************
  questionaire ***************************************************************************8**********/

class Questionnaire {
private:
    vector<string> stringQuestions;
    vector<string> intQuestions;
    
    // Store the cleaned answers ready for the generator
    vector<string> cleanStringAnswers;
    vector<string> cleanIntAnswers;

public:
    // Constructor automatically seeds the random number generator
    Questionnaire() {
        srand(time(0)); 
    }

    // ==========================================
    // 1. Load Questions from Two Separate Files
    // ==========================================
    bool loadFiles(string stringFilename, string intFilename) {
        string line;

        // --- Load the String Questions ---
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

        // --- Load the Integer Questions ---
        ifstream iFile(intFilename); // <--- Use the generic variable here
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

        return true; // Successfully loaded both files
    }
// Helper function to check if files loaded correctly
    void debugPrintCount() {
        cout << "[SUCCESS] Loaded " << stringQuestions.size() << " String Questions and ";
        cout << intQuestions.size() << " Integer Questions." << endl;
    }

    // ==========================================
    // 2. Helper Function: Remove Spaces
    // ==========================================
    string removeSpaces(string input) {
        // Removes all spaces (e.g., "Stranger Things" -> "StrangerThings")
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
        return input;
    }

    // ==========================================
    // 3. Run the Survey
    // ==========================================
    void runSurvey() {
        cleanStringAnswers.clear();
        cleanIntAnswers.clear();

        cout << "\n=======================================" << endl;
        cout << "   PassForge Questionnaire Initialization   " << endl;
        cout << " Type 'skip' if you wish to bypass a question." << endl;
        cout << "=======================================\n" << endl;

        string answer;

        // --- NEW: Short term memory for String questions ---
        vector<int> usedStrings; 
        
        // Ask 3 Random String Questions
        for (int i = 0; i < 3; i++) {
            int randomIndex;
            
            // Keep picking a random number UNTIL we find one we haven't used
            do {
                randomIndex = rand() % stringQuestions.size();
            } while (count(usedStrings.begin(), usedStrings.end(), randomIndex) > 0);
            
            usedStrings.push_back(randomIndex); // Remember it for next time!

            cout << stringQuestions[randomIndex] << " ";
            getline(cin >> ws, answer); 

            if (answer != "skip" && answer != "Skip") {
                cleanStringAnswers.push_back(removeSpaces(answer));
            }
        }

        // --- NEW: Short term memory for Integer questions ---
        vector<int> usedInts;

        // Ask 2 Random Integer Questions
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
        }

        // Ask 2 Random Integer Questions
        for (int i = 0; i < 2; i++) {
            int randomIndex = rand() % intQuestions.size();
            cout << intQuestions[randomIndex] << " ";
            
            getline(cin >> ws, answer);

            if (answer != "skip" && answer != "Skip") {
                // We keep it as a string so the Generator can easily shuffle the characters later
                cleanIntAnswers.push_back(removeSpaces(answer));
            }
        }
        
        cout << "\n[SUCCESS] Questionnaire Complete. Data cleaned and prepared for PassForge." << endl;
    }

    // ==========================================
    // 4. Getters for the Generator Class
    // ==========================================
    vector<string> getStringAnswers() { 
        return cleanStringAnswers; 
    }
    
    vector<string> getIntAnswers() { 
        return cleanIntAnswers; 
    }
};
// ==========================================
// PassForge Password Generator Class
// ==========================================
class PasswordGenerator {
private:
    string generatedPassword;
    string specialChars = "!@#$%^&*";

public:
   // This function takes the cleaned answers from the Questionnaire
    void forgePassword(vector<string> stringAnswers, vector<string> intAnswers) {
        
        // --- The Fallback Safety Net ---
        // If they skipped all string questions, force a default word
        if (stringAnswers.empty()) {
            stringAnswers.push_back("Passforge"); 
        }
        
        // If they skipped all integer questions, force a random 4-digit number
        if (intAnswers.empty()) {
            intAnswers.push_back(to_string(rand() % 9000 + 1000)); 
        }
        // ------------------------------------

        // Create a digital backpack to hold our 3 password options
        vector<string> passwordOptions;

        // Loop 3 times to generate 3 unique options
        for (int i = 0; i < 3; i++) {
            string baseWord = "";
            string numberPart = "";
            
            // 1. Pick one random word
            if (!stringAnswers.empty()) {
                int randStringIdx = rand() % stringAnswers.size();
                baseWord = stringAnswers[randStringIdx];
            }

            // 2. Pick one random number
            if (!intAnswers.empty()) {
                int randIntIdx = rand() % intAnswers.size();
                numberPart = intAnswers[randIntIdx];
            }

            // 3. Pick a random special character
            char specialChar = specialChars[rand() % specialChars.length()];

            // 4. MASH THEM TOGETHER
            string tempPassword = baseWord + numberPart + specialChar;

            // 5. SIZE CONTROL
            if (tempPassword.length() > 16) {
                tempPassword = tempPassword.substr(0, 16);
                tempPassword[15] = specialChar; 
            } 
            else if (tempPassword.length() < 8) {
                while (tempPassword.length() < 8) {
                    tempPassword += to_string(rand() % 10); 
                }
            }

            // Save this newly generated password to our options list
            passwordOptions.push_back(tempPassword);
        }

        // ==========================================
        // The Selection Menu
        // ==========================================
        cout << "\n==================================================" << endl;
        cout << "   [PASSFORGE] Password Generation Complete" << endl;
        cout << "==================================================" << endl;
        cout << "Please select one of the following secure passwords:\n" << endl;

        // Print the 3 options to the screen
        for (int i = 0; i < passwordOptions.size(); i++) {
            cout << "  " << (i + 1) << ". " << passwordOptions[i] << endl;
        }

        int choice = 0;
        
        // This 'while' loop forces the user to pick 1, 2, or 3. 
        // It won't let them crash the program by typing letters or wrong numbers!
        while (true) {
            cout << "\nEnter your choice (1, 2, or 3): ";
            cin >> choice;

            // Safety check: Did they type a letter or a number out of range?
            if (cin.fail() || choice < 1 || choice > 3) {
                cin.clear();             // Clear the error state
                cin.ignore(10000, '\n'); // Throw away whatever garbage they typed
                cout << "[ERROR] Invalid input. Please enter 1, 2, or 3." << endl;
            } else {
                break; // They picked a valid number, break out of the loop!
            }
        }

        // Save their final choice to the official class variable
        // We subtract 1 because vectors start counting at 0! (Choice 1 = Index 0)
        generatedPassword = passwordOptions[choice - 1];

        cout << "\n[SUCCESS] You have selected: " << generatedPassword << endl;
// ==========================================
    // Save Password to a Text File
    // ==========================================
    void savePassword() {
        char choice;
        cout << "\nWould you like to save this password to your vault? (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            string accountName;
            cout << "What account is this password for? (e.g., Gmail, Steam): ";
            
            // cin >> ws clears the buffer so getline doesn't accidentally skip!
            getline(cin >> ws, accountName); 

            // 'ios::app' stands for Append. It adds to the bottom of the file 
            // instead of deleting your old passwords every time it saves!
            ofstream outFile("MyPasswords.txt", ios::app); 

            if (outFile.is_open()) {
                outFile << "Account: " << accountName << " | Password: " << generatedPassword << endl;
                outFile.close();
                cout << "[SUCCESS] Password safely encrypted in MyPasswords.txt!" << endl;
            } else {
                cout << "[ERROR] System could not open the vault file." << endl;
            }
        } else {
            cout << "[INFO] Password discarded. Stay safe!" << endl;
        }
    }
    }

int main()
{
    vector<User> users;
    int liu = -1; // logged in user index

    users.push_back(User("215", "Family123", "Dom", "Toretto"));
    users.push_back(User("U1002", "CatLover_22", "John", "Brown"));

    login(users, liu);

    cout << "Welcome to the system, "
         << users.at(liu).getFname() << " "
         << users.at(liu).getLname() << "!" << endl;
Questionnaire q;
    
    if (q.loadFiles("Questions_string", "Questionsint")) {
        q.debugPrintCount();
        q.runSurvey(); 

    PasswordGenerator pg;
        pg.forgePassword(q.getStringAnswers(), q.getIntAnswers());
// NEW: Ask the user if they want to save it!
        pg.savePassword();
        
    }

    return 0;
}
