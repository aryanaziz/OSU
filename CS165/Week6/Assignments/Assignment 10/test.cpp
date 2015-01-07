#include <iostream>
#include <string>
using namespace std;

bool TestPalindrome (string sentence,int first,int last);
bool TestPalindrome (string sentence,int first,int last)
{

if (last<=1)
return true;
else
if (sentence[first]==sentence[last - 1])
return TestPalindrome(sentence,first+1,last-1);

else return false;
}

int main()
{
string sentance;
getline (cin, sentance);
int last=sentance.length();

TestPalindrome (sentance,0,last);
if (TestPalindrome(sentance,0,last))
cout<<"It is a Palindrome"<<endl;
else
cout<<"It is not a palindrome"<<endl;
return 0;
}