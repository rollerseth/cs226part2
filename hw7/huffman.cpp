/*
#Filename: huffman.cpp

#Author: Seth Roller

#Date: 5/2/19

#Program Name: huffmancode.cpp

#Assignment Number: 11

#Problem: Will be implementing a priority queue (heap) through
an array and then create huffman's binary tree also a compression
/decompression algorithm

#Flow: The layout is all the functions filled in.
The functions will be utilized in the main program 

#Sources:
Dr.Bracken aided with the psuecode on how
to compress and decompress files



I have thoroughly tested my code and it works properly 

 */

#include "huffman.h"
#include <math.h>

//finished
huffman::huffman(string fn)
{
  inputFile = fn;
  char data;
  ifstream fin;
  numChars = 0;
  
  fin.open(fn.c_str());
  assert (fin.is_open());

  Heap theHeap;

  int count[26] = {0};

  for (int i = 0; i < 26; i++) 
    compressed[i] = NULL; 

  
  //reads in the characters and places them accordinly in
  //the array
  while (fin.get(data)) {
    count[data-65]++;
    numChars++;
  }

  //loop that inserts into the heap
  for (int i = 0; i < 26; i++) {
    cout << "Char = " << (char)('A'+(char)i) << " count = ";
    cout << count[i] << endl;
    if (count[i] != 0) {
	huffmannode *temp = new huffmannode;
	temp->symbol = (char)(i+65);
	temp->nodetype = leaf;
	temp->frequency = count[i];
	temp->left = NULL;
	temp->right = NULL;
	theHeap.heapInsert(*temp);
      }
  }

  theHeap.heapDisplay();
  //grab the current size of the heap
  int num = theHeap.heapSize();
  
  huffmannode *r;
  huffmannode *p;
  huffmannode *q;
  
  for (int j = 0; j < (num-1); j++) {
    //where dr.bracken told me to allocate memory
    p = new huffmannode;
    q = new huffmannode;
    r = new huffmannode;
    
    theHeap.heapDelete(*p);
    theHeap.heapDelete(*q);
    
    r->left = p;
    r->right = q;
    r->frequency = p->frequency + q->frequency;
    r->nodetype = nonleaf;
    r->symbol = '\0';
    
    theHeap.heapInsert(*r);
    
    cout << "for debug p->frequency = " << p->frequency;
    cout << " and q->frequency = " << q->frequency << endl;
    cout << "just inserted frequency = " << r->frequency << endl;

    //free up r
    delete r;
    r = NULL;

  }

  finalhuffmantree = new huffmannode;
  theHeap.heapDelete(*finalhuffmantree);
    
  cout << "the constructor has built the huffman tree\n\n";
  
}//end of function constructor

huffman::~huffman()
{
  
  //work in reverse to destroy
  //put everything back in the heap one level at a time and destroy
  //each internal node

  cout<<"Destructor executing"<<endl;

  Heap heapTwo;
  heapTwo.heapInsert(*finalhuffmantree);
  huffmannode * tempR;
  huffmannode * tempL;
  huffmannode * r;
  
  do {
    tempR = new huffmannode;
    tempL = new huffmannode;
    r = new huffmannode;
    heapTwo.heapDelete(*r);

    tempR = r->right;
    tempL = r->left;

    if (tempL != NULL)
      heapTwo.heapInsert(*tempL);

    if (tempR != NULL)
      heapTwo.heapInsert(*tempR);

    delete r;
    r = NULL;
    
  }while (heapTwo.heapSize() > 0);

  delete finalhuffmantree;
  finalhuffmantree = NULL;

  //deallocate mem for the compressed array
  for (int i = 0; i < 26; i++) {
    if (compressed[i] != NULL) {
      delete compressed[i];
      compressed[i] = NULL;
    }
  }
  
}


void huffman::inOrder(string s, huffmannode *t)
{
  
  if (t == NULL) 
    return;

  //if the left is not null add 0
  if (t->left != NULL)
    s += '0';
  inOrder(s, t->left);
  
  if (t->nodetype == leaf) {
    cout << "Frequency = " << t->frequency << " the letter " << t->symbol;
    cout << " the binary string is " << s << endl;

    //insert into the compressed array
    item *newOne = new item;
    newOne->compress = s;
    newOne->length = s.size();
    compressed[(int)(t->symbol-(char)65)] = newOne;

    }


  
  else
    cout << "Frequency = " << t->frequency << endl;
     
  s.erase(s.size()-1);
    
  //if the right is not null add 1
  if (t->right != NULL)
    s += '1';
  inOrder(s, t->right);

 
}

//list operations
void huffman::displayCode() 
{
  string s;
 
  inOrder(s, finalhuffmantree);
}

void huffman::compressdecompress(string compress, string decompress)
{

  
  char data;
  char data1;
  ifstream fin;
  ifstream later;

  fin.open(inputFile.c_str());
  assert (fin.is_open());

  ofstream fon;

  fon.open(compress);
  //opened files and initiated all vars
  //necessary to compress the file
  
  int i = 0;//what number char we are at
  int index = 0;//what bit position at
  unsigned char compressedChar = 0;
  int pickupk = 0;
  int pickupj = compressed[i]->length;
  bool loop = true;
  
  int kBook = 0;
  
  while (loop) {

    //if starting from 0 grab
    //another char
    if (pickupk == 0) {
      fin.get(data);
      i++;
    }

    pickupj = compressed[(int)(data-(char)65)]->length;

    for (int k = pickupk, j = pickupj-1; k < pickupj; k++, j--) {
      kBook = k;//this is for book keeping
      index++;
      
      if (compressed[(int)(data-(char)65)]->compress.at(k) == '1') 
	compressedChar += pow(2, 8-index);

      if (index == 8) {
	
	if (k != pickupj-1) {
	  ++k;
	  pickupk = k;
	  kBook = k;
	}	
	break;
      }
      
    }//end of for

    if (i >= (numChars-1) || index == 8) {
      //when to write to the file and reset index
      fon << compressedChar;      
      index = 0;

      compressedChar = 0;
      
      //this exits the loop when EOF
      if ((fin.peek() < (char)65) && kBook == (pickupj-1)) 
	loop = false;
    }
    
    //reset k
    else if (index != 8) 
      pickupk = 0;

  }

  //close compression and input files
  fin.close();
  fon.close();

  //open the compressed and decompressed files
  fin.open(compress.c_str());
  assert (fin.is_open());
  
  fon.open(decompress);

  fin.get(data);
  int position = 0;
  huffmannode *temp = finalhuffmantree;
  int writing = 0;
  loop = true;
  
  while (loop) {

    //resets the temp variable
    if (temp->nodetype == leaf)
      temp = finalhuffmantree;

    //position gets to 8 means
    //another char gets grabbed
    if (position > 7) {
      fin.get(data);
      position = 0;
    }

    //goes through the huffmantree and exits
    //once a leaf encounted or position reaches
    //the max 8 bits per char
    while (temp->nodetype != leaf && position != 8) {

      if ((((data & ((char)0x80 >> position)) >> (8-position-1))
	  & (0x01)) == (char)0)
	temp = temp->left;
      
      else
	temp = temp->right;
      
      position++;
	  
    }
    
    if (temp->nodetype == leaf && writing < (numChars-1)) {
      fon << temp->symbol;
      writing++;
    }
    
    
    else if (writing >= (numChars-1))
      loop = false;
    
  }//end of reading compressed

  fin.close();
  fon.close();

  
  later.open(decompress.c_str());
  fin.open(inputFile.c_str());
  int alt = 0;
  cout << "INPUT FILE:\tDECOMPRESSED FILE:\n";
  while (alt < (numChars-1)) {
    fin.get(data);
    later.get(data1);
    cout << "   " << data << "\t\t   " << data1;
    cout << endl;
    alt++;
  }
  

}
