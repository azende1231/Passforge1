#include <ctime> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <cstdlib> 

using namespace std;

// ==========================================
// PASSFORGE TITLE SCREEN
// ==========================================
void welcome()
{
    cout << "Welcome to the PassForge System!\n\n" << endl;

    cout << ".----------.  .----------.  .------------. .------------.  .-----------.  .-----------.  .------------." << endl;
    cout << "| .--------. || .--------. || .----------. || .----------. || .---------. || .---------. || .---------. |" << endl;
    cout << "| | PPPPPP | || |   AAA  | || | SSSSSSS  | || | SSSSSSS  | || | FFFFFF  | || | OOOOOOO | || | RRRRRR | |" << endl;
    cout << "| | PP  PP | || |  AA AA | || | SS       | || | SS       | || | FF      | || | OO   OO | || | RR  RR | |" << endl;
    cout << "| | PPPPPP | || | AAAAAA | || | SSSSSS   | || | SSSSSS   | || | FFFFF   | || | OO   OO | || | RRRRRR | |" << endl;
    cout << "| | PP     | || | AA  AA | || |      SS  | || |      SS  | || | FF      | || | OO   OO | || | RR  RR | |" << endl;
    cout << "| | PP     | || | AA  AA | || | SSSSSSS  | || | SSSSSSS  | || | FF      | || | OOOOOOO | || | RR   RR| |" << endl;
    cout << "| .--------. || .--------. || .----------. || .----------. || .---------. || .---------. || .---------. |" << endl;
    cout << ".----------.  .----------.  .------------. .------------.  .-----------.  .-----------.  .------------." << endl;

    cout << "\n";
}

// ==========================================
// 1. User Class
// ==========================================
class User {
private:
    string userID;
    string password;
    string fname;
    string lname;

public:
    User() {
        userID = "";
        password = "";
        fname = "";
        lname = "";
    }

    User(string id, string pwd, string f, string l) {
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

// ==========================================
// 2. Login Function
// ==========================================
void login(vector<User>& users, int& liu) {
    string entID = "";
    string entPwd = "";
    int numAttempts = 0;
    bool isValid = false;

    do {
        cout << "Enter User ID: ";
        cin >> entID;

        cout << "Enter Password: ";
        cin >> entPwd;

        for (int i = 0; i < users.size(); i++) {
            if ((entID == users.at(i).getUserID()) &&
                (entPwd == users.at(i).getPassword())) {
                isValid = true;
                liu = i;
            }
        }

        numAttempts++;

        if (!isValid) {
            cout << "Login Invalid, Try Again!" << endl;
        }

    } while ((numAttempts < 3) && (!isValid));

    if (!isValid) {
        cout << "Number of attempts exceeded, program terminated!" << endl;
        exit(0);
    } else {
        cout << "\nSuccessful Login!" << endl;
    }
}

// ==========================================
// 3. Questionnaire Class
// ==========================================
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

// ==========================================
// 4. Password Generator Class
// ==========================================
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

// ==========================================
// 5. Main
// ==========================================
int main() {
    vector<User> users;
    int liu = -1; 

    // Hardcoded test accounts
    users.push_back(User("215", "Family123", "Dom", "Toretto"));
    users.push_back(User("U1002", "CatLover_22", "John", "Brown"));

    // PASSFORGE TITLE SCREEN
    welcome();

    // Login
    login(users, liu);

    cout << "Welcome to the system, "
         << users.at(liu).getFname() << " "
         << users.at(liu).getLname() << "!" << endl;

    // Questionnaire
    Questionnaire q;
    
    if (q.loadFiles("Questions_string", "Questionsint")) {
        q.debugPrintCount();
        q.runSurvey(); 

        // Password Generator
        PasswordGenerator pg;
        pg.forgePassword(q.getStringAnswers(), q.getIntAnswers());

        // Save Password
        pg.savePassword();
    }

    return 0;
}
    return 0;
}
