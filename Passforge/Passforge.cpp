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

    // Helper function to check if files loaded correctly
    void debugPrintCount() {
        cout << "[SUCCESS] Loaded " << stringQuestions.size() << " String Questions and ";
        cout << intQuestions.size() << " Integer Questions." << endl;
    }

    // ==========================================
    // 2. Helper Function: Remove Spaces
    // ==========================================
    string removeSpaces(string input) {
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

        // --- Short term memory for String questions ---
        vector<int> usedStrings; 
        
        // Ask 3 Random String Questions
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

        // --- Short term memory for Integer questions ---
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
        if (stringAnswers.empty()) {
            stringAnswers.push_back("Passforge"); 
        }
        
        if (intAnswers.empty()) {
            intAnswers.push_back(to_string(rand() % 9000 + 1000)); 
        }
        // ------------------------------------

        vector<string> passwordOptions;

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

            passwordOptions.push_back(tempPassword);
        }

        // ==========================================
        // The Selection Menu
        // ==========================================
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
        
    } // <--- THIS WAS THE MISSING BRACE!

    // ==========================================
    // Save Password to a CSV File
    // ==========================================
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
