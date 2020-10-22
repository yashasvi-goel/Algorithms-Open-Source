#include <iostream>
 using namespace std;

 int main()
 {

     string str;
     char checkCharacter ;
     int count = 0;

     cout<<"Enter a string";
     cin>>str;
     cout<<"Enter a charcter whose frequency you want to find ";
     cin>>checkCharacter;

     for (int i = 0; i < str.size(); i++)
     {
         if (str[i] ==  checkCharacter)
         {
             ++ count;
         }
     }

     cout << "Number of " << checkCharacter << " = " << count;

     return 0;
 }
