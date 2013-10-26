#include <iostream>

using namespace std;

// a year is a leap year if:
//   it is divisible by 400 or
//   it is divisible by 4 and not divisible by 100

int main()
{
  int year;
  cout << "Enter a year" << endl;
  cin >> year;

  if(year % 400 == 0)
  {
    cout << year << " is a leap year" << endl;
  }
  else if(year % 100 == 0)
  {
    cout << year << " is not a leap year" << endl;
  }
  else if(year % 4 == 0)
  {
    cout << year << " is a leap year" << endl;
  }
  else
  {
    cout << year << " is not a leap year" << endl;
  }
}
