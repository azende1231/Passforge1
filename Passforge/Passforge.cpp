// Passforge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithim> //This is to remove spaceces
#include <cstdlib> //This is for rand() and srand()
#include <ctime>

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
/****************************************************
  questionaire *******************/
class Questionaire{

private:
  vector <string> stringQuestions;
  vector <string> intquestions;
  vector <string> cleanStringAnswers;
  vector <string> cleanIntAnswers;

public:

