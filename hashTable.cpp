// Patrick Hourican
// pjh4as
// 10/14/20
// hashTable.cpp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "hashTable.h"

using namespace std;

HashTable::HashTable() {}

HashTable::HashTable(int size1) {
  hashTable = new vector<list<string>>;
  
  for (int i = 0; i < size1; i++) {
    list<string> temp;
    hashTable->push_back(temp);
  }
  size = size1;
}

HashTable::~HashTable() {
}

void HashTable::insert(string str) {
  int index = hash(str);
  
  hashTable->at(index).push_back(str);
}

int HashTable::hash(string str) {
  unsigned int hashIndex = 1;
  
  for(int j = 0; j<str.length();j++){
    hashIndex += (str[j]);
  }
  return hashIndex % size;
}

bool HashTable::contains(string str) {

  list<string> strAtHash = hashTable->at(hash(str));

  bool contains = (strAtHash.end() != find(strAtHash.begin(), strAtHash.end(), str));
  
  return contains;
}
