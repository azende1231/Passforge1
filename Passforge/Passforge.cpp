#include <iostream>
#include <vector>
#include <string>

// Include your custom header files
#include "User.h"
#include "Questionnaire.h"
#include "PasswordGenerator.h"

using namespace std;

// ==========================================
// PASSFORGE TITLE SCREEN
// ==========================================
void welcome() {
    cout << "Welcome to the PassForge System!\n\n" << endl;

   cout << ".----------.  .----------.  .------------.  .------------.  .-----------.  .-----------.  .------------.  .-----------.  .----------." << endl;
cout << "| .--------. || .--------. || .----------. || .----------. || .---------. || .---------. || .---------. || .---------. || .--------. |" << endl;
cout << "| | PPPPPP | || |   AAA  | || | SSSSSSS  | || | SSSSSSS  | || | FFFFFF  | || | OOOOOOO | || | RRRRRR | || | GGGGGGG | || | EEEEEE | |" << endl;
cout << "| | PP  PP | || |  AA AA | || | SS       | || | SS       | || | FF      | || | OO   OO | || | RR  RR | || | GG      | || | EE     | |" << endl;
cout << "| | PPPPPP | || | AAAAAA | || | SSSSSS   | || | SSSSSS   | || | FFFFF   | || | OO   OO | || | RRRRRR | || | GG GGG  | || | EEEEE  | |" << endl;
cout << "| | PP     | || | AA  AA | || |      SS  | || |      SS  | || | FF      | || | OO   OO | || | RR  RR | || | GG  GG  | || | EE     | |" << endl;
cout << "| | PP     | || | AA  AA | || | SSSSSSS  | || | SSSSSSS  | || | FF      | || | OOOOOOO | || | RR   RR| || | GGGGGG  | || | EEEEEE | |" << endl;
cout << "| .--------. || .--------. || .----------. || .----------. || .---------. || .---------. || .---------. || .---------. || .--------. |" << endl;
cout << ".----------.  .----------.  .------------.  .------------.  .-----------.  .-----------.  .------------.  .-----------.  .----------." << endl;

    cout << "\n";
}

// ==========================================
// Login Function
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
// Main Execution
// ==========================================
int main() {
    vector<User> users;
    int liu = -1; 

    // Hardcoded test accounts
    users.push_back(User("215", "Family123", "Dom", "Toretto"));
    users.push_back(User("184", "1upshroom", "Mario", "Bennet"));
    users.push_back(User("237", "JohnnyWhiskey1977", "Jack", "Torrance"));
    users.push_back(User("267", "lawyer456", "Mike", "Ross"));
    users.push_back(User("517", "Ranch517", "John", "Dutton"));
    users.push_back(User("192", "goku2007pink", "Jane", "Steves"));

    // 1. Title Screen
    welcome();

    // 2. Login
    login(users, liu);

    cout << "Welcome to the system, "
         << users.at(liu).getFname() << " "
         << users.at(liu).getLname() << "!" << endl;

    // 3. Questionnaire
    Questionnaire q;
    
    if (q.loadFiles("Questions_string", "Questionsint")) {
        q.debugPrintCount();
        q.runSurvey(); 

        // 4. Password Generator & Save
        PasswordGenerator pg;
        pg.forgePassword(q.getStringAnswers(), q.getIntAnswers());
        pg.savePassword();

        // 4. Run Again Loop
        char runAgain;
        do {
            PasswordGenerator pg;
            pg.forgePassword(q.getStringAnswers(), q.getIntAnswers());
            pg.savePassword();

            // Ask the user if they want to keep going
            cout << "\n--------------------------------------------------" << endl;
            cout << "Would you like to generate another password? (Y/N): ";
            cin >> runAgain;
            
        } while (runAgain == 'Y' || runAgain == 'y');
        
        // A nice goodbye message when they finally type 'N'
        cout << "\n[INFO] Thank you for using PassForge. Stay secure!\n" << endl;
    }

    return 0;
}
    }

    return 0;
}
