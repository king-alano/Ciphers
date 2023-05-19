/*
  file: RailFence.cpp
  auth: AJ Boyd, aboyd3@umbc.edu, Section 11
  date: 4/8/22
  desc: implimentation for the RailFence class which is a child of the Cipher class
*/

#include <iostream>
#include <string>
#include "RailFence.h"
using namespace std;

//defualt constructor
RailFence::RailFence(){
  m_rails = 3;
}
//overloaded constructor
RailFence::RailFence(string message, bool encrypted, int rails){
  SetMessage(message);

  //if the parent cipher does not equal the passed boolean, toggle the cipher
  if(GetIsEncrypted() != encrypted){
    ToggleEncrypted();
  }
  m_rails = rails;
}
//destructor
RailFence::~RailFence(){
  //cout << "rail fence destructor called." << endl;
}

//public functions that are virutal in parent class
void RailFence::Encrypt(){
  //code to encrtypt Rail Fence Cipher
  int LEN = GetMessage().length();
  int period = 2 * (m_rails - 1); //period formula from the provided wiki page
  string code;
  
  /* cout << "string len: " << LEN << endl;
  cout << "period: " << period << endl;  
  cout << "is this gonna be easy?: " << (LEN % period == 0) << endl;
  */

  /*so rail fence is kinda hard but after researching on wikipedia, the cipher can be used by
    placing the plaintext in a rectangle and having each letter placed diagonally inside the rectangle
    
    ex.
    W...R...A..
    .E.A.E.S.F.
    .._..._...E
    which encodes to be: WRAEAESF__E
    
    using this logic, if the cipher can be represented in a rectangle with a height = m_rails
    and width = LEN
   */
  for(int i = 0; i < m_rails; i++){
    for(int j = 0; j < LEN; j++){
      int column = j;
      
      column = column % period; //gets remainder from the period equation
      //this will make the column position variable somewhere between 0-period(exclusive)

      //when the remainder is greater than or equal to m_rails, update column
      if(column >= m_rails){
	column = period - column;
      }

      //if the position column mathches the row, add it to the code
      if(column == i){
	code += GetMessage()[j];
      }
    }
  }
  SetMessage(code);
}
void RailFence::Decrypt(){
  //code to decrypt Rail Fence cipher
  int LEN = GetMessage().length();
  int period = 2 * (m_rails - 1); 
  int count = 0;//counter variable to put the encrypted text back into the correct position
  char temp[LEN];//the line of plaintext is temporarily held in an array of chars 
  string plaintext;

  //does encryption in reverse; as in goes from the "rectangle" to the staight line of plaintext 
  for(int i = 0; i < m_rails; i++){
    for(int j = 0; j < LEN; j++){
      int index = j; //calculates the position to place the character (in plaintext array)

      index = index % period;
      //when the remainder is greater than or equal to m_rails, update index
      //this 
      if(index >= m_rails){
        index = period - index;
      }
      //if the position index mathches the row index, add it to the temp array then incriment couont
      if(index == i){
        temp[j] = GetMessage()[count];
	count++;
      }
    }
  }
  //converts the char array into a normal string
  for(int i = 0; i < LEN; i++)
    plaintext += temp[i];
  SetMessage(plaintext);
}
string RailFence::ToString(){
  return "(Rail Fence)";
}
string RailFence::FormatOutput(){
  string type = "r";
  string enc = (GetIsEncrypted() ? "1" : "0");
  stringstream ss;

  ss << type << "|" << enc << "|" << GetMessage() <<  "|" << to_string(m_rails);
  return ss.str();
}
