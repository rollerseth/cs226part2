/*
#Filename: PQHeap.cpp

#Author: Seth Roller

#Date: 5/2/19

#Program Name: huffmancode.cpp

#Assignment Number: 10

#Problem: Will be implementing a priority queue (heap) through
an array and then create huffman's binary tree

#Flow: The layout is all the functions filled in.
The functions will be utilized in the main program 

#Sources:
No sources were utilized

I have thoroughly tested my code and it works properly 

 */

#include "PQHeap.h"  // header file for class Heap

//finished
Heap::Heap() : size(0)
{
}  // end default constructor

//finished
bool Heap::heapIsEmpty() const
{
  if (size == 0)
    return true;
  else
    return false;
}  // end heapIsEmpty

//finished
void Heap::heapInsert(const huffmannode& newItem)
        
// Method: Inserts the new item after the last item in the
// heap and trickles it up to its proper position. The
// heap is full when it contains MAX_HEAP items.
{
  if (size >= MAX_HEAP) {
    cout << "Heap is full, cannot add anymore.\n";
  }

  else {

    //specific size test
    if (size == 0) {
      items[0] = newItem;
      size++;
    }

    //inserts into the heap if bigger than size 1
    else {
      items[size] = newItem;
      int i = size;
      size++;
      while (i > 0 && newItem.frequency < items[(i-1)/2].frequency) {
	huffmannode temp = items[i];
	items[i] = items[(i-1)/2];
	items[(i-1)/2] = temp;
	i = i/2;
      }

    }
      
      
  }//end of first else
   
}  // end heapInsert

//finished
void Heap::heapDelete(huffmannode& rootItem)
        
// Method: Swaps the last item in the heap with the root
// and trickles it down to its proper position.
{
  if (heapIsEmpty()) {
    cout << "Cannot remove from the heap because\n";
    cout << "it is empty" << endl;
  }
  
  //if heap is not empty
  else {

    //if size if 1 return first position
    if (size == 1) {
      rootItem = items[0];
      size = 0;
    }
    
    else {
      rootItem = items[0];
      items[0] = items[size-1];
      size--;
      heapRebuild(items[0].frequency);
    }
  } //end of first else 
    
}  // end heapDelete

// method returns the size of the heap
//finished
int Heap::heapSize()
{
  return size;
}//end of function

void Heap::heapRebuild(int root)
{
  
  int j = 0;
  //the bool is utilized so that no multiple if statements
  //do not get executed 
  bool finished = false;
  
  while (true) {

    //if j is at the end of the array of if there
    //is no left child for the current j
    if (j == (size-1) || (j*2+1 > size-1))
      break;

    //if the left child is less than the parent and the left child
    //is less than or equal to the right child execute
    else if (items[2*j+1].frequency < items[((2*j+1)-1)/2].frequency
	     && finished == false && (items[2*j+1].frequency
				      <= items[2*j+2].frequency)) {
      
      huffmannode temp = items[2*j+1];
      items[2*j+1] = items[((2*j+1)-1)/2];
      items[((2*j+1)-1)/2] = temp;
      j = 2*j+1;
      finished = true;
    }

    //if there is no right child for the current j
    else if (2*j+2 > size-1)
          break;

    //if the right child is less than the parent and the right child is
    //less than the left child 
    else if (items[2*j+2].frequency < items[((2*j+2)-1)/2].frequency
	     && finished == false) {
      huffmannode temp = items[2*j+2];
      items[2*j+2] = items[((2*j+2)-1)/2];
      items[((2*j+2)-1)/2] = temp;
      j = 2*j+2;
      finished = true;
    }

    //if none of these conditions execute just break
    else
      break;
    
    finished = false;

  }
  
}  // end heapRebuild
  
//finished
void Heap::heapDisplay()
{
  cout << "Heap Contents are as follows: " << endl;
  for (int i = 0; i < size; i++) {
    cout << "Symbol = " << items[i].symbol;
    cout << " frequency = " << items[i].frequency << endl;

  }
  cout << "end of heapDisplay\n\n";
  
}//end heapDisplay

// End of implementation file.
