/*
  auth: AJ Boyd, aboyd3@umbc.edu, section 12
  date: 4/20/69
  file: Vingenere.h
  desc: implimentation of the extra credit vingenere cipher class header
*/

#ifndef VIGENERE_H
#define VIGENERE_H
#include "Cipher.h"
#include <iostream>
#include <string>
using namespace std;

class Vigenere: public Cipher{
public:
  Vigenere(); //defualt contsructor
  Vigenere(string, bool, string); //overloaded constructor passes message, encrypted, and keyword
  ~Vigenere(); //destructor

  //virtual functions in parent class
  void Encrypt();
  void Decrypt();
  string ToString();
  string FormatOutput();
private:
  string m_keyword; //keyword used for encryption/decryption
};
#endif
