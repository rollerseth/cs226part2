/*
#Filename: huffmancode.cpp

#Author: Seth Roller

#Date: 5/2/19

#Program Name: huffmancode.cpp

#Assignment Number: 11

#Problem: Will be implementing a priority queue (heap) through
an array and then create huffman's binary tree

#Flow: The layout the main program will separate
use the function calls from PQHeap.cpp and huffman.cpp

#Sources:
No sources used for this file

I have thoroughly tested my code and it works properly 

 */



#include "huffman.h" 
using namespace std; 
int main() 
{ 
  string fn;
  string compress;
  string decompress;
  cout<<"enter the name of a file containing the characters:" << endl;
  cin >> fn;
  cout <<"file enetered " << fn << endl << endl;

  cout << "enter the name of a file for compression:" << endl;
  cin >> compress;
  cout << "file enetered " << compress << endl << endl;

  cout << "enter the name of a file for decompression:" << endl;
  cin >> decompress;
  cout << "file enetered " << decompress << endl << endl;
  
  huffman myhuffman(fn); 
  myhuffman.displayCode();
  myhuffman.compressdecompress(compress, decompress);
  
}//end main
