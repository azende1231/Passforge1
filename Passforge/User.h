#pragma once
#include <string>

using namespace std;

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
