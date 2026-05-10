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
        // Clear previous answers in case the user hit "redo"
        cleanStringAnswers.clear();
        cleanIntAnswers.clear();

        cout << "\n=======================================" << endl;
        cout << "   PassForge Questionnaire Initialization   " << endl;
        cout << " Type 'skip' if you wish to bypass a question." << endl;
        cout << "=======================================\n" << endl;

        string answer;

        // Ask 3 Random String Questions
        for (int i = 0; i < 3; i++) {
            int randomIndex = rand() % stringQuestions.size();
            cout << stringQuestions[randomIndex] << " ";
            
            // 'ws' clears any leftover newlines in the input buffer
            getline(cin >> ws, answer); 

            if (answer != "skip" && answer != "Skip") {
                cleanStringAnswers.push_back(removeSpaces(answer));
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
        
        string baseWord = "";
        string numberPart = "";
        
        // 1. Pick one random word from their survey answers
        if (!stringAnswers.empty()) {
            int randStringIdx = rand() % stringAnswers.size();
            baseWord = stringAnswers[randStringIdx];
        }

        // 2. Pick one random number from their integer answers
        if (!intAnswers.empty()) {
            int randIntIdx = rand() % intAnswers.size();
            numberPart = intAnswers[randIntIdx];
        }

        // 3. Pick a random special character
        char specialChar = specialChars[rand() % specialChars.length()];

        // 4. MASH THEM TOGETHER (e.g., "Harrypotter" + "2009" + "!")
        generatedPassword = baseWord + numberPart + specialChar;

        // 5. SIZE CONTROL (Must be 8 to 16 characters)
        if (generatedPassword.length() > 16) {
            // If it's too long, chop it down to exactly 16 characters
            generatedPassword = generatedPassword.substr(0, 16);
            
            // Force the last character to be the special character for security
            generatedPassword[15] = specialChar; 
        } 
        else if (generatedPassword.length() < 8) {
            // If it's too short, pad it with extra random numbers until it reaches 8
            while (generatedPassword.length() < 8) {
                generatedPassword += to_string(rand() % 10); 
            }
        }

        // 6. Print the final result!
        cout << "\n==================================================" << endl;
        cout << " [PASSFORGE] Your custom secure password is: " << generatedPassword << endl;
        cout << "==================================================\n" << endl;
    }
};

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
    }

    return 0;
}
