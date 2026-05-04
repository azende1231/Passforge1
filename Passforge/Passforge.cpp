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

class Questionaire{

private:
  vector <string> stringQuestions;
  vector <string> intquestions;
  vector <string> cleanStringAnswers;
  vector <string> cleanIntAnswers;

public:

