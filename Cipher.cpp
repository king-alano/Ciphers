/*
  file: Cipher.cpp
  auth: AJ Boyd, aboyd3@umbc.edu, Section 11
  date: 4/7/22
*/

#include <iostream>
#include <string>
#include "Cipher.h"
using namespace std;

//defualt constructor
Cipher::Cipher(){
  m_message = "";
  m_isEncrypted = false;
}
//overloaded constructor
Cipher::Cipher(string message, bool encrypted){
  m_message = message;
  m_isEncrypted = encrypted;
}
//virtual distructor
Cipher::~Cipher(){
  //cout << "cipher desturctor called." << endl;
}
//setters and getters
string Cipher::GetMessage(){
  return m_message;
}
bool Cipher::GetIsEncrypted(){
  return m_isEncrypted;
}
void Cipher::SetMessage(string message){
  m_message = message;
}
void Cipher::ToggleEncrypted(){
  //switches the m_isEncrypted bool variable. if it's encrypted->decrypted vice-versa
  if(m_isEncrypted){
    m_isEncrypted = false;
  }else{
    m_isEncrypted = true;
  }
}
//overloaded output operator
ostream &operator<<(ostream &output, Cipher &C){
  //string s = C.m_isEncrypted ? "encrypted" : "plaintext";
  output << "\"" << C.m_message << "\" " << C.ToString(); //<< "(" << s << ")";
  return output;
}


//virutal functions implimented in child classes
