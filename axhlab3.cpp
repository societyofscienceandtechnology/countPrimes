#include <iostream>
using namespace std;
int main() 
{
 int primeLimit;
 cout << "enter a limit ";
 cin >> primeLimit;
 int sum = 0;
 int term=0;
 for(int i=0;i<primeLimit;i=1+2) {
     if(i%i==0) {
         sum+=i;
     }
    
 }
 cout << sum << endl; 
}
 
 
 
