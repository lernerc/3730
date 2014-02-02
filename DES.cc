//*****************************************************************************
// Name: Camara Lerner
// SN: 001150339
// Class: CPSC 3730
// The implimentation of the DES algorithm
//*****************************************************************************

/*
  
Implement the DES algorithm. 
Let the user input the key and plaintext. (100 marks) 

You can use any language to implement it.
Both encryption and decryption are required. 



Key and Plaintext are hexadecimal numbers. 

Output the following values (Binary numbers) for each round: 

E(R_(i-1)), K_i, E(R_(i-1_) XOR K_i, S-box output, f(R_(i-1), K_i), L_i, R_i  
 
Make a pause for each round output.  
 */
#include <iostream>
#include <algorithm>
using namespace std;

class DES {
public:
   DES(const int & m = 0, const int &k = 0) : message(m), key(k) {}
   void inputMessage(int m) {message = m}
   void inputKey(int k) {message = k}
   void calculate();
private:
   void IP();
   void IP_inverse();
   void round();
   void E(int);
   void K(int);
   void S_box();
   void f(int, int);

   // input message and key
   int message;
   int key;
   // previous L, and R
   int L_p, R_p;
   //current L and R
   int L, R;
   //previous C and D
   int C_p, D_p;
   // current C and D
   int C, D;
   
};

void DES::calculate() {

}

void DES::IP() {

}

void DES::IP_inverse() {

}

void DES::round() {

}

void DES::E(int) {

}

void DES::K(int) {

}

void DES::S_box() {

}

void DES::f(int, int) {

}

int main() {

   return 0;
}
