#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap {
 public:
  heap(int capacity);
  
  //insert a node with string id
  // 0 on success, 1 if already filled, 2 if a node with id already exists
  int insert(const std::string &id, int key, void *pv = NULL);
  
  //increaseKey and decreaseKey 
  //0 on success, 1 if id does not exist
  int setKey(const std::string &id, int key);
  
  
  int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);
  
  //delete the node with specified id from the heap
  int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

 private:
  class node{
  public:
    std::string id;
    int key;
    void *pData;
  };
  int capacity;
  int filled;
  HashTable *map;
  std::vector<node> tree;
  
  void percUp(int cur_pos);
  void percDown(int cur_pos);
  int getPos(node *pn);
  bool heap_ord_check(int pos);

};


#endif
