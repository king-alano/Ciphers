/*
  file: Cipher.cpp
  auth: AJ Boyd, aboyd3@umbc.edu, Section 11
  date: 4/7/22
  desc: implimentation for the Caesar class which is a child of the Cipher class
*/

#include <iostream>
#include <string>
#include "Caesar.h"
using namespace std;

//defualt constructor
Caesar::Caesar(){
  m_shift = 3;
}
//overloaded constructor
Caesar::Caesar(string message, bool encrypted, int shift){
  SetMessage(message);

  //if the parent cipher does not equal the passed boolean, toggle the cipher
  if(GetIsEncrypted() != encrypted){
    ToggleEncrypted();
  }
  m_shift = shift;
}
//destructor
Caesar::~Caesar(){
  //cout << "Caesar cipher destroyed." << endl;
}

//public functions that are virutal in parent class
void Caesar::Encrypt(){
  //code to encrypt a Caesar Cipher
  int LEN = GetMessage().length();
  string code;
  
  for(int i = 0; i < LEN; i++){
    char letter = GetMessage()[i]; //gets the current character in the message
    int ascii = int(letter); //converts that character to an integer ascii value
    
    if((ascii >= 'A' && ascii <= 'Z') || (ascii >= 'a' && ascii <= 'z')){
      //if the character is a letter, shift it by m_shift
      ascii += m_shift;
      
      if((ascii >= 'A' && ascii <= 'Z') || (ascii >= 'a' && ascii <= 'z')){
	//if the shifted letter is still in the range of A-Z or a-z, print it as is
        //cout << char(ascii);
	code += char(ascii);
      }else{
	//if the shifted letter goes OUT of range of A-Z or a-z, handle the overflow
        //i.e. if you shift 'y' by 4, you get 'y'->'}' by defualt
        //instead, make it so 'y'->'c'
	ascii -= m_shift;
	
	if(isupper(char(ascii))){
          //if the letter is uppercase, base the ascii at 'A'(65)
          int overflow = m_shift - 90 % ascii;
          ascii = 64 + overflow;
        }else{
          //if the letter is lowercase, base the ascii at 'a'(97)
	  int overflow = m_shift - 122 % ascii;
          ascii = 96 + overflow;
        }
        //cout << char(ascii);
	code += char(ascii);
      }
    }else{
      //if the character is a special character, do not shift it; print it as is
      //cout << letter;
      code += letter;
    }
  }
  SetMessage(code);
}
void Caesar::Decrypt(){
  //code to decrypt Caesar Cipher
  int LEN = GetMessage().length();
  string plaintext;

  for(int i = 0; i < LEN; i++){
    char letter = GetMessage()[i]; //gets the current character in the message
    int ascii = int(letter); //converts that character to an integer ascii value

    if((ascii >= 'A' && ascii <= 'Z') || (ascii >= 'a' && ascii <= 'z')){
      //if the character is a letter, shift it to the left by m_shift
      ascii -= m_shift;

      if((ascii >= 'A' && ascii <= 'Z') || (ascii >= 'a' && ascii <= 'z')){
        //if the shifted letter is still in the range of A-Z or a-z, print it as is
        //cout << char(ascii);
        plaintext += char(ascii);
      }else{
        //if the shifted letter goes OUT of range of A-Z or a-z, handle the overflow
        //i.e. if you shift 'c' by 4, you get 'c'->'_' by defualt
        //instead, make it so 'c'->'y'
        ascii += m_shift;

        if(isupper(char(ascii))){
          //if the letter is uppercase, base the ascii at 'Z'(90)
          int overflow = m_shift - ascii % 65;
          ascii = 91 - overflow;
        }else{
          //if the letter is lowercase, base the ascii at 'z'(122)
          int overflow = m_shift - ascii % 97;
          ascii = 123 - overflow;
        }
        //cout << char(ascii);
        plaintext += char(ascii);
      }
    }else{
      //if the character is a special character, do not shift it; print it as is
      //cout << letter;
      plaintext += letter;
    }
  }
  SetMessage(plaintext);
}
string Caesar::ToString(){
  return "(Caesar)";
}
string Caesar::FormatOutput(){
  string type = "c";
  string enc = (GetIsEncrypted() ? "1" : "0");
  stringstream ss;
  
  ss << type << "|" << enc << "|" << GetMessage() << "|" << to_string(m_shift);
  return ss.str();  
}



