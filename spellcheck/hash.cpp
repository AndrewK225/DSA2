/* 
    The hashtable class (implements functions defined in hash.h)
    Andrew Koe
*/

#include "hash.h"
#include <string>
#include <vector>
#include <algorithm>



//constructor
HashTable::HashTable(int size) {   
  data.resize(getPrime(size));  //resize because already declared in header
  filled = 0;
  capacity = data.size();
  collision_cnt = 0;
  
}

int HashTable::insert(const std::string &key, void *pv) {  
  std::string lc(key);
  std::transform(lc.begin(),lc.end(),lc.begin(),::tolower);  //convert to lowercase
  unsigned int pos = hash(lc);
  HashItem word;
  word.key = lc;
  word.isOccupied = true;
  
  //linear probing
  if(data[pos].isOccupied == false) {
    data[pos] = word;    
  }
  else {
    while(data[pos].isOccupied == true) {
      if(data[pos].key == lc) {
		return 1;
      }
      pos = (pos+1)%data.size();
    }
    data[pos] = word;
  }
  filled++;
  
  if(filled >= (data.size()>>1) ) {
    if(rehash()) {
      return 2;
    }
    else {
      return 0;
    }
  }
  
}

bool HashTable::contains(const std::string &key) {
  std::string lc(key);
  std::transform(lc.begin(),lc.end(),lc.begin(),::tolower);
  unsigned int pos = hash(lc);

  if(data[pos].isOccupied == false) //no word hashed there
    return false;
  else {
    if(data[pos].key == lc)
      return true;
    else {
      while(data[pos].isOccupied == true) {  //linear probing
	pos++;
	if(data[pos].key == lc) {
	  return true;
	} 
      }
      return false;
    }
  }
}

void* HashTable::getPointer(const std::string &key, bool *b) {
}

int HashTable::setPointer(const std::string &key, void *pv) {
}

bool HashTable::remove(const std::string &key) {
}

unsigned int HashTable::hash(const std::string &key) {
   std::string lc(key);
   std::transform(lc.begin(),lc.end(),lc.begin(),::tolower);  //convert to lowercase

  unsigned int hash_val = 0;
  int len = lc.length();
  for(int i = 0; i < len; i++) {
    hash_val = (hash_val << 6) + (hash_val<<16)+lc[i] - hash_val;
    hash_val += lc[i];
  }
  return (hash_val%data.size());
}


int HashTable::findPos(const std::string &key) {
}

bool HashTable::rehash() {
  unsigned int currsize = data.size();
  unsigned int nextsize = getPrime(data.size());  
  if(nextsize != 0) {
    //copy the current hashtable
    std::vector<HashItem> temp;
    temp.reserve(currsize);
    copy(data.begin(),data.end(),back_inserter(temp));
    
	
    data.resize(1);
    data[1].isOccupied = false;
	//resize the actual vector
    data.resize(nextsize);

    //re-insert all of the words?
    for(int i = 0; i < currsize; i++) {
      insert(temp[i].key);
    }
    
    return true;
  }
  else
    return false;
}


//takes in current size, returns next size
unsigned int HashTable::getPrime(int size) {
  unsigned int primes[8] = {100069, 201923, 405499, 811771, 1623857, 3247759, 6495527, 25265843};  //last one is more than double
  int i = 0;
  while(primes[i] < 2*size) {
    if(i < 7)  //hardcoding to avoid out of bounds
      i++;
    else {
      return 0;
    }
  }  
  return primes[i];  
}
