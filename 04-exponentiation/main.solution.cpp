#include<iostream>
#include<cmath>

using namespace std;

float power(float base, int exponent)
{
  float answer = 1;
  for(int i=0; i<exponent; i++)
    answer = answer * base;
  return answer;
}

int main(int argc, char ** argv)
{
  float base;
  int exponent;
  float answer;

  cout << "Enter the base number: ";
  cin >> base;
  cout << "Enter the exponent: ";
  cin >> exponent;

  answer = power(base, exponent);

  cout << base << "^" << exponent << " = " << answer << endl;
}
