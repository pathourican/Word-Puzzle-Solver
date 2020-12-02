// Patrick Hourican
// pjh4as

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class HashTable {

 public:
  HashTable();

  HashTable(int size1);
  ~HashTable();

  bool contains(string str);
  void insert(string str);
  int hash(string str);

 private:
  int size;
  
  vector<list<string>>* hashTable;

  //friend class wordPuzzle;
};
#endif
