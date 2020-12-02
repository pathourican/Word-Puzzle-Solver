// Patrick Hourican
// pjh4as
// 10/14/2020
// wordPuzzle.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

#include "timer.h"
#include "hashTable.h"

#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];

using namespace std;

bool readInGrid(string filename, int& rows, int& cols);
string getWordInGrid(int startRow, int startCol, int dir, int len, int numRows, int numCols);
bool checkprime(unsigned int p);
int getNextPrime(unsigned int n);

int main(int argc, char* argv[]) {

  string dir[8] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
  
  int count = 0;
string output = "";
timer t;
  int rows, cols;
  
  ifstream file(argv[1]);
  
  string line;

  int sizeCounter = 0;
  while(getline(file, line))
    sizeCounter++;
  sizeCounter = sizeCounter*2;
  if (!checkprime(sizeCounter)) {
    sizeCounter = getNextPrime(sizeCounter);
  }
  
  file.close();
  
  HashTable dict(sizeCounter);

  file.open(argv[1]);
  
  while(getline(file, line)) {
      dict.insert(line);
  }

  bool result = readInGrid(argv[2], rows, cols);
  t.start();
  for(int i = 0; i<rows; i++) {
    for(int j = 0; j<cols; j++) {
      for(int k = 0; k <=7;k++) {
	for(int l = 3; l<=22;l++) {
	  string line = getWordInGrid(i, j, k, l, rows, cols);
	  if(l > line.length()) {
	    break;
	  }
	  else if(dict.contains(line)) {
	    count++;
	    output += dir[k] + " (" + to_string(i) + ", " + to_string(j) + "): " + line + "\n";
	   
	  }
	}
      }
    }
  }
  t.stop();
  
  cout << output;
  cout << count << " words found" << endl;
  //float time = static_cast<int>(t.getTime()*1000);
  //cout << "Found all words in " << time/1000  << " seconds"<<endl;
  return 0;
}

bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);
    // upon an error, return false
    if (!file.is_open()) {
        return false;
    }

    // first comes the number of rows
    file >> rows;
    //cout << "There are " << rows << " rows." << endl;

    // then the columns
    file >> cols;
    //cout << "There are " << cols << " cols." << endl;

    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
	    // cout << grid[r][c];
        }
        //cout << endl;
    }
    return true;
}

string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }

    return output;
}

bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}
