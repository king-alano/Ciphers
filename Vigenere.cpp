/*
  file: Vigenere.cpp
  auth: AJ Boyd, aboyd3@umbc.edu, Section 11
  date: 4/20/22
  desc: implimentation for the Vigenere class which is a child of the Cipher class
*/

#include <iostream>
#include <string>
#include "Vigenere.h"
using namespace std;

//default constructor
Vigenere::Vigenere(){
  m_keyword = "hello";
}
//overloaded constructor
Vigenere::Vigenere(string message, bool encrypted, string key){
  SetMessage(message);
  //if the parent cipher does not equal the passed boolean, toggle the cipher
  if(GetIsEncrypted() != encrypted){
    ToggleEncrypted();
  }
  m_keyword = key;
}
//destructor
Vigenere::~Vigenere(){
  //it's empty...
}

//virtual functions
void Vigenere::Encrypt(){
  string code, extendedKey;
  int LEN = GetMessage().length();
  int count = 0; //used to keep track of which letter in the keyword to use

  //for loop extends the key
  for(int i = 0; i < LEN; i++){
    int index = i % m_keyword.length();
    extendedKey += m_keyword[index];
  }
  //cout << "extended keyword: " << extendedKey << endl;
  
  //for loop runs for the length of the message
  for(int i = 0; i < LEN; i++){
    //variables that hold the current letter in the plaintext and extended key and their respective offset values
    char plainletter = GetMessage()[i];
    char keyletter = extendedKey[count];
    char encryptedLetter;
    int plOffset, klOffset, elOffset = 0;

    //basically, the offset of a letter is its position 0-25 where a=0 and z=25
    if((plainletter >= 'a' && plainletter <= 'z') || (plainletter >= 'A' && plainletter <= 'Z')){
      klOffset = int(keyletter) - 97;
      if(isupper(plainletter) == 0){//if plainletter is lowercase
	plOffset = int(plainletter) - 97;

	//formula for finding the encrypted letter offset: e=(p+k)%26
	elOffset = (plOffset + klOffset) % 26;
	encryptedLetter = char(elOffset + 97);
      }else{
	plOffset = int(plainletter) - 65;
	
	elOffset = (plOffset + klOffset) % 26;
	encryptedLetter = char(elOffset + 65);
      }

      //increment count
      count++;
    }else{
      //special characters are unaffected by the cipher
      encryptedLetter = plainletter;
    }    
    code += encryptedLetter;
  }
  SetMessage(code);
}
void Vigenere::Decrypt(){
  string plaintext, extendedKey;
  int LEN = GetMessage().length();
  int count = 0;

  //for loop extends the key
  for(int i = 0; i < LEN; i++){
    int index = i % m_keyword.length();
    extendedKey += m_keyword[index];
  }

  for(int i = 0; i < LEN; i++){
    //variables that hold the current letter in the plaintext and extended key and their respective offset values
    char encryptedLetter = GetMessage()[i];
    char keyletter = extendedKey[count];
    char plainletter;
    int plOffset, klOffset, elOffset = 0;
    
    if((encryptedLetter >= 'a' && encryptedLetter <= 'z') || (encryptedLetter >= 'A' && encryptedLetter <= 'Z')){
      klOffset = int(keyletter) - 97;
      if(isupper(encryptedLetter) == 0){
        elOffset = int(encryptedLetter) - 97;
	
        //formula for finding the encrypted letter offset: p=(e+k+26)%26
        plOffset = (elOffset - klOffset + 26) % 26;
        plainletter = char(plOffset + 97);
      }else{
        elOffset = int(encryptedLetter) - 65;

        plOffset = (elOffset - klOffset + 26) % 26;
        plainletter = char(plOffset + 65);
      }
      // cout << "E" << i << ": " << elOffset << " K" << i << ": " << klOffset << endl;
      //cout << elOffset - klOffset + 26 << endl;
      //increment count
      count++;
    }else{
      //special characters are unaffected by the cipher
      plainletter = encryptedLetter;
    }
    plaintext += plainletter;
  }
  SetMessage(plaintext);
}
string Vigenere::ToString(){
  return "(Vigenere)";
}
string Vigenere::FormatOutput(){
  string enc = (GetIsEncrypted() ? "1" : "0");
  stringstream ss;
  ss << "v|" << enc << "|" << GetMessage() << "|" << m_keyword;

  return ss.str();
}
