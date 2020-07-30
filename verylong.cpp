// verylong.cpp
// implements very long integer type

/* enhanced capabilities with error handling and data file handling*/

#include <fstream.h>
#include <string.h>  //for strlen(), etc.
#include <stdlib.h>  //for ltoa()
#include <conio.h>   //for clrscr(), getch()
#include <math.h>    //for floor(), log10() etc.

const long SZ = 5000;                  // maximum digits in verylongs
const long double pi = 3.14159265359;  // value of pi
const long double e = 2.71828182846;   // value of euler's constant

class verylong {
 private:
  char vlstr[SZ];                         // verylong number, as a string
  int vlen;                               // length of verylong string
  verylong multdigit(const int) const;    // prototypes for
  verylong mult10(const verylong) const;  // private functions

 public:
  verylong()
      : vlen(0)  // no-arg constructor
  {
    vlstr[0] = '\0';
  }
  verylong(const char s[SZ])  // one-arg constructor
  {
    strcpy(vlstr, s);
    vlen = strlen(s);
  }                                // for string
  verylong(const unsigned long n)  // one-arg constructor
  {                                // for long int
    ltoa(n, vlstr, 10);            // convert to string
    strrev(vlstr);                 // reverse it
    vlen = strlen(vlstr);          // find length
  }
  void putvl() const;                  // display verylong
  void getvl();                        // get verylong from user
  verylong operator+(const verylong);  // add verylongs
  verylong operator*(const verylong);  // multiply verylongs
};
//-------------------------------------------------------------
void verylong::putvl() const  // display verylong
{
  char temp[SZ];
  strcpy(temp, vlstr);                  // make copy
  cout << strrev(temp);                 // reverse the copy and display it
  ofstream fil;                         // open file in out mode
  fil.open("FACTORIAL.txt", ios::app);  // and append mode to enter factorial
  fil << temp;                          // save factorial in factorial.txt
  fil.close();                          // close file stream
}
//-------------------------------------------------------------
void verylong::getvl()  // get verylong from user
{
  cin >> vlstr;          // get string from user
  vlen = strlen(vlstr);  // find its length
  strrev(vlstr);         // reverse it
}
//-------------------------------------------------------------
verylong verylong::operator+(const verylong v)  // add verylongs
{
  char temp[SZ];
  int j;
  // find longest number
  int maxlen = (vlen > v.vlen) ? vlen : v.vlen;
  int carry = 0;                // set to 1 if sum >= 10
  for (j = 0; j < maxlen; j++)  // for each position
  {
    int d1 = (j > vlen - 1) ? 0 : vlstr[j] - '0';      // get digit
    int d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - '0';  // get digit
    int digitsum = d1 + d2 + carry;                    // add digits
    if (digitsum >= 10)                                // if there's a carry,
    {
      digitsum -= 10;
      carry = 1;
    }                          // decrease sum by 10,
    else                       // set carry to 1
      carry = 0;               // otherwise carry is 0
    temp[j] = digitsum + '0';  // insert char in string
  }
  if (carry == 1)         // if carry at end,
    temp[j++] = '1';      // last digit is 1
  temp[j] = '\0';         // terminate string
  return verylong(temp);  // return temp verylong
}
//-------------------------------------------------------------
verylong verylong::operator*(const verylong v)  // multiply
{                                               // verylongs
  verylong pprod;                               // product of one digit
  verylong tempsum;                             // running total
  for (int j = 0; j < v.vlen; j++)              // for each digit in arg
  {
    int digit = v.vlstr[j] - '0';  // get the digit
    pprod = multdigit(digit);      // multiply this by digit
    for (int k = 0; k < j; k++)    // multiply result by
      pprod = mult10(pprod);       //   power of 10
    tempsum = tempsum + pprod;     // add product to total
  }
  return tempsum;  // return total of prods
}
//-------------------------------------------------------------
verylong verylong::mult10(const verylong v) const  // multiply
{                                                  // arg by 10
  char temp[SZ];
  for (int j = v.vlen - 1; j >= 0; j--)  // move digits one
    temp[j + 1] = v.vlstr[j];            //   position higher
  temp[0] = '0';                         // put zero on low end
  temp[v.vlen + 1] = '\0';               // terminate string
  return verylong(temp);                 // return result
}
//-------------------------------------------------------------
verylong verylong::multdigit(const int d2) const {  // multiply this verylong
  char temp[SZ];                                    // by digit in argument
  int j, carry = 0;
  for (j = 0; j < vlen; j++)  // for each position
  {                           //   in this verylong
    int d1 = vlstr[j] - '0';  // get digit from this
    int digitprod = d1 * d2;  // multiply by that digit
    digitprod += carry;       // add old carry
    if (digitprod >= 10)      // if there’s a new carry,
    {
      carry = digitprod / 10;   // carry is high digit
      digitprod -= carry * 10;  // result is low digit
    } else
      carry = 0;                // otherwise carry is 0
    temp[j] = digitprod + '0';  // insert char in string
  }
  if (carry != 0)             // if carry at end,
    temp[j++] = carry + '0';  // it's last digit
  temp[j] = '\0';             // terminate string
  return verylong(temp);      // return verylong
}
//-------------------------------------------------------------
void fact()  // function too calculate factorial
{
  clrscr();
  ofstream fil;  // opening file stream in out mode
  fil.open("FACTORIAL.txt",
           ios::app);             // open file factorial.txt in append mode
  unsigned long numb, j, digits;  // only positive values accepted
  verylong fact = 1;              // initialize verylong
  cout << "\n\nEnter number: ";
  cin >> numb;  // input a long integer

  digits = floor((0.5 * log10(2 * pi * numb)) + (numb * log10(numb / e)) + 1);
  // Stirling's Approximation of the magnitude of factorial of a number

  cout << "Number of Digits in The factorial of the Number: " << digits << endl;
  fil << "\n\nNumber: " << numb << "\
      \nDigits: "
      << digits << "\
      \nFactorial is: \n";  // storing in file
  fil.close();              // close file stream
  // Error Handling
  if (SZ < digits) {
    cout << "WARNING!!!! Insufficient amount of memory.\
\nChange size (SZ) to continue";  // look for const int SZ=xxxx;
    getch();
    exit(1);
  }
  cout << "\nCalculating.....";
  // Calculation of factorial
  for (j = numb; j > 0; j--)    // factorial is numb *
    fact = fact * j;            //   numb-1 * numb-2 *
  cout << "\n\nFactorial is ";  //   numb-3 and so on
  fact.putvl();                 // display factorial
  cout << endl << "Done!";
}
//-------------------------------------------------------------
void main() {
  clrscr();
  char ch = 'y';
  int ch1 = 0;
  while (ch == 'y' || ch == 'Y')  // loop begins
  {
    cout << "\n\tMENU\t\n";
    cout << "1. Factorial Calculator\n";
    /*
Add more Functions or Operations
*/
    cout << "Choose (1-xx): ";
    cin >> ch1;
    switch (ch1)  // switch begins
    {
      case 1:
        fact();
        break;
      default:
        cout << "Wrong Input!";
        getch();
        continue;
    }  // switch ends
    cout << "\nMore? (y/n): ";
    cin >> ch;
  }  // while loop ends
  clrscr();
  cout << endl << "Thank You" << endl;  // roll credits
  cout << "Made by Mrinmay Dhar";
  getch();
  clrscr();  // smoother experience in DOS Shell
}
