/* 
   Andrew Koe EE'16 
   Spell check
   
*/

#include <iostream>
#include "hash.h"
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib> //for exit()

using namespace std;

int main() {
  string dict_name, txt_name, out_name, line, word, wrd2chk;
  ifstream dict_file, txt_file;
  ofstream out_file;
  HashTable table;
  int line_cnt = 0;
  int i, len, line_len;
  bool nochk_flag = false;
  bool mentioned = false;


  //read in the dictionary
  cout << "Enter name of dictionary: ";
  cin >> dict_name;
  dict_file.open(dict_name.c_str(),ios::in);
  if(!(dict_file.is_open())) {
    cerr << "Error opening dictionary file\n" << endl;
    exit(1);
  }


clock_t startTime = clock();
  while(getline(dict_file,word)) {
    table.insert(word);
  }
  cout <<"Total time (in seconds) to load dictionary: " << double(clock()-startTime)/(double)CLOCKS_PER_SEC<< endl;
  
  //open the input file
  cout << "Enter name of input file: ";
  cin >> txt_name;
  txt_file.open(txt_name.c_str(),ios::in);
  if(!(txt_file.is_open())) {
    cerr << "Error opening input file\n" << endl;
    exit(1);
  }


  //open or create the outfile
  cout << "Enter name of output file: ";
  cin >> out_name;
  out_file.open(out_name.c_str(),ios::out);
  if(!(out_file.is_open())) {
    cerr << "Error opening/creating output file\n" << endl;
    exit(1);
  }


  startTime = clock();
  //start moving through the file
  while(getline(txt_file,line)) {
    line_cnt++;
    i = 0;  //reset to first character of each line;
    wrd2chk.clear();
    len = 0;
    line_len = line.length();
    if(line_len == 0) {
      continue;
    }
    //while not at the end of the line, keep taking words
    while(i <= line_len) {
      if(line[i] >= '0' && line[i] <= '9' || line[i] >= 'A' && line[i] <= 'Z' || line[i] >= 'a' && line[i] <= 'z' || line[i] == '-' || line[i] == 39) {
	if(line[i] >= '0' && line[i] <= '9') {
	  nochk_flag = true;
	}
	len++;
 	if(len <= 20) {
	  wrd2chk += line[i];
	}
	
	else {
	  if(mentioned == false) {
	    transform(wrd2chk.begin(),wrd2chk.end(),wrd2chk.begin(),::tolower);
	    out_file << "Long word at line " << line_cnt << ", starts: " << wrd2chk << endl;
	    mentioned = true;
	  }
	  nochk_flag = true;
	}
	i++;
      } 
      else { //invalid character found
	if(nochk_flag) {
	  wrd2chk.clear();
	  len = 0;
	  nochk_flag = false;
	  mentioned = false;
	  i++;
	}
	
	else {
	  if(table.contains(wrd2chk)) {
	    wrd2chk.clear();
	    len = 0;
	    i++;
	  }
	  else if(wrd2chk.length()) {
	    transform(wrd2chk.begin(),wrd2chk.end(),wrd2chk.begin(),::tolower);
	    out_file << "Unknown word at line " << line_cnt << ": " << wrd2chk << endl;
	    wrd2chk.clear();
	    len = 0;
	    i++;
	  }
	  else {
	    wrd2chk.clear();
	    len = 0;
	    i++;
	  }
	}
     
      }
      continue; 
    
    
    }

  }
   cout <<"Total time (in seconds) to check document: " <<double(clock()-startTime)/(double)CLOCKS_PER_SEC<< endl;


}
