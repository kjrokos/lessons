#include <iostream>

using namespace std;

int main()
{
  int birthYear;
  int birthMonth;
  int currentYear;
  int currentMonth;
  float age;

  cout << "Enter the year you were born" << endl;
  cin >> birthYear;
  cout << "Enter the month you were born" << endl;
  cin >> birthMonth;

  cout << "Enter the current year" << endl;
  cin >> currentYear;
  cout << "Enter the current month" << endl;
  cin >> currentMonth;

  //figure out how to compute age
  age = currentYear-birthYear+(currentMonth-birthMonth)/12.f; 

  cout << "You are " << age << " years old!" << endl;

  return 0;
}

