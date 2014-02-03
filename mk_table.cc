#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

// reads in 1-based numbers seperated by spaces and outputs them as 0-based numbers and then seperates them by commas

int main() {
   string line;
   while(getline(cin, line)) {
      int tmp;
      istringstream iss(line);
      while(iss >> tmp && tmp >= 0) {
	 cout << setw(2) << tmp-1 << ", ";
      }
      cout << endl;
   }
   
   return 0;
}
