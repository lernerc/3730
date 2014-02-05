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
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <bitset>
using namespace std;

// found online at http://www.cplusplus.com/forum/articles/7312/
void PressEnterToContinue() {
   int c;
   cout << "Press ENTER to continue... ";
   fflush( stdout );
   do c = getchar(); while ((c != '\n') && (c != EOF));
}

// converted all the tables to be 0-based

const int IP[64] = {57, 49, 41, 33, 25, 17,  9,  1, 
		    59, 51, 43, 35, 27, 19, 11,  3, 
		    61, 53, 45, 37, 29, 21, 13,  5, 
		    63, 55, 47, 39, 31, 23, 15,  7, 
		    56, 48, 40, 32, 24, 16,  8,  0, 
		    58, 50, 42, 34, 26, 18, 10,  2, 
		    60, 52, 44, 36, 28, 20, 12,  4, 
		    62, 54, 46, 38, 30, 22, 14,  6};

const int IP_inverse[64] = {39,  7, 47, 15, 55, 23, 63, 31, 
			    38,  6, 46, 14, 54, 22, 62, 30, 
			    37,  5, 45, 13, 53, 21, 61, 29, 
			    36,  4, 44, 12, 52, 20, 60, 28, 
			    35,  3, 43, 11, 51, 19, 59, 27, 
			    34,  2, 42, 10, 50, 18, 58, 26, 
			    33,  1, 41,  9, 49, 17, 57, 25, 
			    32,  0, 40,  8, 48, 16, 56, 24};

const int E[] = {31,  0,  1,  2,  3,  4, 
		 3,   4,  5,  6,  7,  8, 
		 7,   8,  9, 10, 11, 12, 
		 11, 12, 13, 14, 15, 16, 
		 15, 16, 17, 18, 19, 20, 
		 19, 20, 21, 22, 23, 24, 
		 23, 24, 25, 26, 27, 28, 
		 27, 28, 29, 30, 31,  0};

const int P[] = {15,  6, 19, 20, 
		 28, 11, 27, 16, 
		 0, 14, 22, 25, 
		 4, 17, 30,  9, 
		 1,  7, 23, 13, 
		 31, 26,  2,  8, 
		 18, 12, 29,  5, 
		 21, 10,  3, 24};

const int S[8][64] = {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0,  15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
    4,   1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3,  13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0,  14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1,  10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   {7,  13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3,  15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   {2,  12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9, 
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6, 
    4,   2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14, 
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11, 
    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8, 
    9,  14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6, 
    4,   3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   {4,  11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1, 
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6, 
    1,   4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2, 
    6,  11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7, 
    1,  15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2, 
    7,  11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8, 
    2,   1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}};

const int PC1[] = {56, 48, 40, 32, 24, 16,  8, 
		   0,  57, 49, 41, 33, 25, 17, 
		   9,   1, 58, 50, 42, 34, 26, 
		   18, 10,  2, 59, 51, 43, 35, 
		   
		   62, 54, 46, 38, 30, 22, 14, 
		   6,  61, 53, 45, 37, 29, 21, 
		   13,  5, 60, 52, 44, 36, 28, 
		   20, 12,  4, 27, 19, 11,  3};

const int PC2[] = {13, 16, 10, 23,  0,  4, 
		   2,  27, 14,  5, 20,  9, 
		   22, 18, 11,  3, 25,  7, 
		   15,  6, 26, 19, 12,  1, 
		   40, 51, 30, 36, 46, 54, 
		   29, 39, 50, 44, 32, 47, 
		   43, 48, 38, 55, 33, 52, 
		   45, 41, 49, 35, 28, 31};

const int left_shift[] =
{1,  1,  2,  2,  2,  2,  2,  2,  1,  2,  2,  2,  2,  2,  2,  1};

// guaranted positive shift number
void leftShift(int array[], const int &size, const int &shift) {
   int *tmp = new int[size];
   copy(array, array + size, tmp);
   for(int i = 0; i < size; i++) {
      array[i] = tmp[(i + shift) % size];
   }
   delete [] tmp;
}

void convert(const string& hex, int bin[], const int size) {

   istringstream iss(hex);
   for(int i = 0; i < (int)hex.size() && i+3 < size; i++) {
      char a;
      iss >> a;
      int tmp;
      if(a - '0' < 10) {
	 tmp = a - '0';
      } else if(a - 'A' < 6) {
	 tmp = a - 'A' + 10;
      } else if(a - 'a' < 6) {
	 tmp = a - 'a' + 10;
      } else {
	 cerr << "problem with input" << endl;
      }
      
      for(int j = 3; j >=0; j--) {
	 bin[i*4+j] = tmp%2;
	 tmp/=2;
      }
   }
}

class DES {
public:
   DES(const string & m ="", const string &k = "") {
      convert(m, message, 64);
      convert(k, key, 64);
   }
   void inputMessage(const string &m) {
      convert(m, message, 64);
   }
   void inputKey(const string &k) {
      convert(k, key, 64);
   }
   void calculate();
private:
   void output(int [], int);
   void output(int [17][56], int, int);
   void output(int [17][32], int, int);
   void round(int);
   void IP_calc();
   void IP_inverse_calc();
   void initialize_K();
   void E_calc(int);
   void K_calc(int);
   void S_box(int);
   void f(int);
   string calc_hex(int [64]);

   // input message and key
   int message[64];
   int key[64];
   // L and R values at each step
   int L[17][32], R[17][32];
   // C and D at each step
   int C[17][28], D[17][28];
   int K[17][56];
   string ciphertext;
   int E_i[48];
   int s_box[32];
   int answer[64];
   string hexAnswer;
};

void DES::output(int array[], int size) {
   for(int i = 0; i < size; i++) {
      cout << array[i];
   }
   cout << endl;
}

void DES::output(int array[17][56], int index, int size) {
   for(int i = 0; i < size; i++) {
      cout << array[index][i];
   }
   cout << endl;
}

void DES::output(int array[17][32], int index, int size) {
   for(int i = 0; i < size; i++) {
      cout << array[index][i];
   }
   cout << endl;
}

void DES::round(int r) {
   copy(R[r-1], R[r-1] + 32, L[r]);

   // output E(R_(i-1))
   E_calc(r);
   cout << "E(R_" << left << setw(2) << r << "): ";
   output(E_i, 48);
      
   // output K_i
   K_calc(r);
   cout << "K_" << left << setw(2) << r << ": ";
   output(K, r, 48);
      
   // output E(R_(i-1) XOR K_i
   cout << "E(R_" << left << setw(2) << r-1 << ") XOR K_" << setw(2) << r
	<< ": " << endl;
   for(int i = 0; i < 48; i++) {
      E_i[i] = E_i[i] ^ K[r][i];
   }
   output(E_i, 48);
      
   // output S-box output
   S_box(r);
   cout << "S-box output:" << endl;
   output(s_box, 32);
      
   // output f(R_(i-1), K_i)
   f(r);
   cout << "f(R_" << left << setw(2) << r-1 << ", K_" << setw(2) << r 
	<< "): ";
   output(s_box, 32);
      
   // output L_i and R_i
   if(r != 16)
      cout << "L_" << setw(2) << r+1 << " = ";
   cout << "R_" << setw(2) << r << ": ";
   for(int i = 0; i < 48; i++) {
      R[r][i] = s_box[i] ^ L[r - 1][i];
   }
   copy(E_i, E_i + 32, L[r + 1]);
   output(R, r, 32);
}

void DES::calculate() {
   IP_calc();
   // output L0 and R0
   cout << "L_0: ";
   output(L[0], 32);

   cout << "L_1 = R_0: ";
   copy(R[0], R[0] + 32, L[1]);
   output(R, 0, 32);

   initialize_K();
  
   cin.get();
   for(int r = 1; r <= 16; r++) {
      round(r);
      
      //pause
      if(r != 16)
	 PressEnterToContinue();
   }
   
   // IP_inverse
   IP_inverse_calc();
   hexAnswer = calc_hex(answer);
   cout << "ciphertext: " <<  hexAnswer << endl; 
   // convert to the hex string
}

string DES::calc_hex(int array[64]) {
   string a;
   int tmp = 0;
   for(int i = 0; i < 16; i++) {
      tmp = 0;
      for(int j = 0; j < 4; j++) {
	 tmp *= 2;
	 tmp += array[i*4+j];
      }
      if(tmp < 10) {
	 a += tmp + '0';
      } else if(tmp >= 10) {
	 a += tmp + 'A' - 10;
      }
   }
   return a;
}

void DES::IP_calc() {
   for(int i = 0; i < 32; i++) {
      L[0][i] = message[IP[i]];
      R[0][i] = message[IP[i+32]];
   }

}

void DES::IP_inverse_calc() {
   // assumes that the swap is not done
   for(int i = 0; i < 64; i++) {
      answer[i] = IP_inverse[i] < 32 ?
	 R[16][IP_inverse[i]] : L[16][IP_inverse[i] - 32];
   }
}

void DES::initialize_K() {

   cout << "key without the parity check" << endl;
   for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 7; j++) {
	 cout << key[i*8 + j];
      }
   }
   cout << endl;
   for(int i = 0; i < 28; i++) {
      C[0][i] = key[PC1[i]];
   }
   for(int i = 0; i < 28; i++) {
      D[0][i] = key[PC1[i + 28]];
   }
}

void DES::E_calc(int r) {

   for(int i = 0; i < 48; i++) {
      E_i[i] = R[r - 1][E[i]];
   }
}

void DES::K_calc(int r) {
   // next C and D are the previous C and D after the left shifts
   copy(C[r-1], C[r-1] + 28, C[r]);
   copy(D[r-1], D[r-1] + 28, D[r]);
   // do left shifts to C and D
   leftShift(C[r], 28, left_shift[r-1]);
   leftShift(D[r], 28, left_shift[r-1]);
   
   // perform PC2 on combined C and D
   int tmp[56];
   copy(C[r], C[r] + 28, tmp);
   copy(D[r], D[r] + 28, tmp + 28);

   for(int i = 0; i < 48; i++) {
      K[r][i] = tmp[PC2[i]];
   }
}

void DES::S_box(int r) {
   long long number = 0;
   int row, col;
   for(int s = 0; s < 8; s++) {
      row = E_i[s*6]*2 +E_i[s*6+5];
      col = E_i[s*6+1]*8 + E_i[s*6+2]*4 + E_i[s*6+3]*2 + E_i[s*6+4];
      number *= 16;
      number += S[s][row*16 + col];
   }
   for(int i = 31; i >= 0; i--) {
      s_box[i] = number % 2;
      number /= 2;
   }
}

void DES::f(int r) {
   int tmp[32];
   copy(s_box, s_box + 32, tmp); 
   for(int i = 0; i < 32; i++) {
      s_box[i] = tmp[P[i]];
   }
}

int main() {

   string M, K;
   while(cin >> M >> K) {
      DES answer(M, K);
      answer.calculate();
   }
   return 0;
}
