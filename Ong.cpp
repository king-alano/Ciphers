/*
0;136;0c  file: Ong.cpp
  auth: AJ Boyd, aboyd3@umbc.edu, Section 11
  date: 4/9/22
  desc: implimentation for the Ong class which is a child of the Cipher class
*/

#include "Ong.h"
#include <istream>
#include <string>
#include <vector>
using namespace std;

//defualt constructor
Ong::Ong(){
  //honestly no clue what goes in here...
}
//overloaded constructor
Ong::Ong(string message, bool encrypted){
  SetMessage(message);

  //if the parent cipher does not equal the passed boolean, toggle the cipher
  if(GetIsEncrypted() != encrypted){
    ToggleEncrypted();
  }
}
//destructor
Ong::~Ong(){
  //cout << "ong destructor called." << endl;
}

//public functions that are virutal in parent class
void Ong::Encrypt(){
  //code to encrtypt Ong Cipher
  int LEN = GetMessage().length();
  char letter, nextChar;
  string code;
  
  for(int i = 0; i < LEN; i++){ //for loop iterates through the entire message char by char
    letter = GetMessage()[i];
    nextChar = GetMessage()[i + 1];
    
    if((int(letter) >= 'A' && int(letter) <= 'Z') || (int(letter) >= 'a' && letter <= 'z')){
      //if the character is a letter
      if(IsVowel(letter)){
	//if vowel
	if(int(nextChar) == 32){
	  //if the next character is a space, only add the vowel
	  code += letter;
	}else{
	  //else add the vowel and a dash
	  code += letter;
	  code += "-";
	}
      }else{
	//if a consinent add ong's and such
	if(int(nextChar) == 32 || int(nextChar) == 0){ //same if-else for the vowels
          code += letter;
	  code += "ong";
        }else{
          code += letter;
	  code += "ong-";
	}
      }
    }else{
      //if special character, print as is
      code += letter;
    }
  }

  SetMessage(code);
}
void Ong::Decrypt(){
  //code to decrypt Ong cipher
  int LEN = GetMessage().length();
  char letter, nextChar;
  string code;

  for(int i = 0; i < LEN; i++){
    letter = GetMessage()[i];
    nextChar = GetMessage()[i + 1];
   
    code += GetMessage()[i]; //adds the letter at the current i index to code
    
    if((int(letter) >= 'A' && int(letter) <= 'Z') || (int(letter) >= 'a' && letter <= 'z')){
      if(IsVowel(letter)){
	//if vowel
	i++; //increment i by one to skip '-'

	if(int(nextChar) == 32){
	  //if the next character is a space, add a space
	  code += " ";
	}
      }else{
	//if not vowel
	i += 4; //increment i by four to skip '-ong'
	
	if(int(GetMessage()[i]) == 32){
	  //if the next character is a space, add a space
          code += " ";
        }
      }
    }
  }
  
  SetMessage(code);
}
string Ong::ToString(){
  return "(Ong)";
}
string Ong::FormatOutput(){
  string type = "o";
  string enc = (GetIsEncrypted() ? "1" : "0");
  stringstream ss;

  ss << type << "|" << enc << "|" << GetMessage() <<  "|";
  return ss.str();
}

//helper function
bool Ong:: IsVowel(char letter){
  return (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U');
}
