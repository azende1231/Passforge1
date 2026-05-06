// Passforge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime> // this is for time
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithim> //This is to remove spaces
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

    return 0;
}

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
int main() {
    Questionnaire q;
    
    if (q.loadFiles("Questions.csv", "Questionsint.csv")) {
        q.debugPrintCount();
        q.runSurvey(); 
    }

    return 0;
}


