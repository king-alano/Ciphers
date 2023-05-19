/*
  file: CipherTool.cpp
  auth: AJ Boyd, aboyd3@gmail.com, section 11
  date: 4/9/22
  desc: implimentation of the CipherTool class
*/

#include "CipherTool.h"
#include "Cipher.h"
#include "Caesar.h"
#include "RailFence.h"
#include "Ong.h"
#include "Vigenere.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// constuctor
CipherTool::CipherTool(string file){
  m_filename = file;
}
//destructor
CipherTool::~CipherTool(){
  for(unsigned int i = 0; i < m_ciphers.size(); i++){
    delete m_ciphers.at(i);
  }
  cout << "Ciphers deleted." << endl;
}
//other public functions
void CipherTool::LoadFile(){
  //opens file and reads in each cipher. each cipher should be dynamically allocated and put into m_ciphers vector
  string type, encrypted, message, other;
  ifstream file;
  file.open(m_filename);

  if(file.is_open()){
    while(getline(file, type, DELIMITER) &&
	  getline(file, encrypted, DELIMITER) &&
	  getline(file, message, DELIMITER) &&
	  getline(file, other, '\n')){

      if(type == "c"){
	Caesar *c = new Caesar(message, StringToBoolean(encrypted), stoi(other));
	m_ciphers.push_back(c);
      }else if(type == "r"){
	RailFence *r = new RailFence(message, StringToBoolean(encrypted), stoi(other));
	m_ciphers.push_back(r);
      }else if(type == "o"){
        Ong *o = new Ong(message, StringToBoolean(encrypted));
	m_ciphers.push_back(o);
      }else{
	//extra credit cipher if you see this in the base submission, my fault
	Vigenere *v = new Vigenere(message, StringToBoolean(encrypted), other);
	m_ciphers.push_back(v);
      }
    }
    file.close();
    cout << "Ciphers imported." << endl;
  }else{
    cout << "File could not be openned." << endl;
  }
}
bool CipherTool::StringToBoolean(string input){
  //given a string (either 0 or 1), returns either true or false
  return stoi(input);
}
void CipherTool::EncryptDecrypt(bool encode){
  //encrypts or decrypts each of the ciphers in m_ciphers
  int count = 0;

  for(unsigned int i = 0; i < m_ciphers.size(); i++){
    Cipher *c = m_ciphers.at(i);
    // cout << "want us to encrypt?: " << encode << " is it encrypted?: " << c->GetIsEncrypted() << endl;
    //cout << (encode == c->GetIsEncrypted()) << endl;

    if(encode != c->GetIsEncrypted()){
      //since you cannot decrypt a message that's already decrypted, only do changes is encode and GetIsEncrypted do not equal each other
      count++;
      encode ? c->Encrypt() : c->Decrypt();//whenever i use the ternary operator i feel like i have an IQ of 200+
      c->ToggleEncrypted();
    }
  }
  if(encode){
    cout << count << " Cipher(s) encrypted." << endl;
  }else{
    cout << count << " Cipher(s) decrypted." << endl;
  }
}
void CipherTool::Export(){
  //exports the cipheres in m_ciphers
  ofstream newFile;
  string fileName;
    
  cout << "What do you want to call the export file?" << endl;
  cin >> fileName;
  
  newFile.open(fileName);
  for(unsigned int i = 0; i < m_ciphers.size(); i++){
    newFile << m_ciphers.at(i)->FormatOutput() << endl;
  }
  newFile.close();
  cout << m_ciphers.size() << " Ciphers exported." << endl;
}
int CipherTool::Menu(){
  //displays the menu; returns choice
  int choice = 0;
  cout << "What would you like to do?" << endl;
  cout << " 1. Display all Ciphers." << endl;
  cout << " 2. Encrypt all Ciphers." << endl;
  cout << " 3. Decrypt all Ciphers." << endl;
  cout << " 4. Export  all Ciphers." << endl;
  cout << " 5. Quit." << endl;
  cin >> choice;
  cout << endl;
  
  return choice;
}
void CipherTool::Start(){
  //loads imput file and manages program
  LoadFile();
  bool flag = true; //flag
  while(flag){
    switch(Menu()){ //switch statement based on Menu's output
    case 1:
      cout << "Ciphers:" << endl;
      for(unsigned int i = 0; i < m_ciphers.size(); i++){
	cout << " " << (i+1) << ". " << *m_ciphers.at(i) << endl;
      }
      cout << endl;
      break;
    case 2:
      cout << "Encrypting Ciphers..." << endl;
      EncryptDecrypt(true);
      cout << endl;
      break;
    case 3:
      cout << "Decrypting Ciphers..." << endl;
      EncryptDecrypt(false);
      cout << endl;
      break;
    case 4:
      Export();
      cout << "Ciphers exported into file." << endl;
      cout << endl;
      break;
    case 5:
      cout << "Thanks for playing!" << endl;
      cout << endl;
      flag =  false;
      break;
    default:
      cout << "Invalid input." << endl;
      cout << endl;
      break;
    }
  }
}
