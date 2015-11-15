/* Andrew Koe
   Heap 10/13/14 
*/

//#include <iostream>
#include "heap.h"
#include "hash.h"

using namespace std;

heap::heap(int capacity) {
  this -> capacity = capacity;
  this -> filled = 0;
  tree.resize(capacity+1);
  map = new HashTable(capacity*2);
}

int heap::insert(const string &id, int key, void *pv) {
  if (filled == capacity) {
    return 1;
  }
  
  else if(filled < capacity && map->contains(id)) {
    return 2;
  }
  
  else {
    filled++;
    tree[filled].id = id;
    tree[filled].key = key;
    tree[filled].pData = pv;

    map -> insert(id, &tree[filled]);
    percUp(filled);
    return 0;
  }

}

int heap::setKey(const string &id, int key) {
  //  cout << "setKey called\n";
  bool exists = false;
  node *node_ptr = static_cast<node *>(map -> getPointer(id, &exists));
 
  if(exists == false) {
    return 1;
  }

  int pos = getPos(node_ptr);
  // cout << pos << "\n";
  tree[pos].key = key;
  //fix heap order 
  if(heap_ord_check(pos)) {
    percDown(pos);
  }
  else if(tree[pos].key< tree[pos/2].key) {
    percUp(pos);
  }
  return 0;
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {
  if(filled == 0) {
    return 1;
  }

  if(pId) {
    *pId = tree[1].id;
  }
  if(pKey) {
    *pKey = tree[1].key;
  }
  if(ppData) {
    *(static_cast<void**>(ppData)) = tree[1].pData;
  }
  
  map -> remove(tree[1].id);  //remove root

  tree[1] = tree[filled];
  filled--;
  percDown(1);  //fix order
  return 0;
}

int heap::remove(const string &id, int *pKey, void *ppData) {
  bool exists = false;
  node *node_ptr = static_cast<node *>(map->getPointer(id,&exists));
 
  if(exists == false)
    return 1;
  
  int pos = getPos(node_ptr);
  
  if(pKey) {
    *pKey = tree[pos].key;
  }
  if(ppData) {
    *(static_cast<void **>(ppData)) = tree[pos].pData;
  }

  map -> remove(id);
  
  tree[pos] = tree[filled];
  map -> setPointer(tree[pos].id, &tree[pos]);
  filled--;

  if(heap_ord_check(pos)) {
    percDown(pos);
  }
  else if(tree[pos].key < tree[pos/2].key) {
    percUp(pos);
  }
  return 0;
}

void heap::percUp (int cur_pos) {
  int hole = cur_pos;
  node tmp = tree[cur_pos];

  for ( ; hole > 1 && tmp.key < tree[hole/2].key; hole = hole/2) {
    tree[hole] = tree[hole/2];
    map->setPointer(tree[hole].id, &tree[hole]);
  }

  tree[hole] = tmp;
  map->setPointer(tree[hole].id, &tree[hole]);
}

void heap::percDown(int cur_pos) {
  int hole = cur_pos;
  int child = 0;
  node tmp = tree[cur_pos];

  for ( ; hole * 2 <= filled; hole = child) {
    child = hole * 2;
    if (child != filled && tree[child+1].key < tree[child].key) {  //children are 2n and 2n+1
      child++;
    }
    if (tree[child].key < tmp.key) {
      tree[hole] = tree[child];
      map->setPointer(tree[hole].id, &tree[hole]);
    }
    else
      break;
  }
  tree[hole] = tmp;
  map->setPointer(tree[hole].id, &tree[hole]);

}

int heap::getPos(node *pn) {
  // cout << "in getPos\n";
  int pos = pn - &tree[0];
  // cout<< "leaving getPos\n";
  return pos;
}

bool heap::heap_ord_check(int pos) {
  if (((pos*2 <= filled ) && (tree[pos].key > tree[pos*2].key)) ||((pos*2+1 <= filled) && (tree[pos].key > tree[pos*2+1].key)) || ((pos == 1))) {
    return true;
  }
  else {
    return false;
  }
}
