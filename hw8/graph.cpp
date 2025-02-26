/*
#Filename: graph.cpp

#Author: Seth Roller

#Date: 4/30/19

#Program Name: assign10.cpp

#Assignment Number: 10

#Problem: Will create a graph through an
allocated array of pointers

#Flow: The layout is all the functions filled in.
The functions will be utilized in the main program 

#Sources:
Dr.Bracken aided me in the DFS_visit function

I have thoroughly tested my code and it works properly 
Also BFS works 

 */

#include "queuei.h"
#include "graph.h"

struct graphNode
{  int name;
  graphPtr Next;
};

//finished
graph::graph() {

  headTopo = NULL;
  cycle = false;

  int n;
  string answer;
  int node1;
  int node2;
  
  //asking for the vertices 
  while (true) {
    cout << endl;
    cout << "Please enter the number of vertices: ";
    cin >> n;
    if (cin.good() && n > 0) {
      cout << endl;
      cout << "You entered " << n << endl;
      break;
    }
    cout << endl << endl;
    cout << "You entered " << n << endl;
    cout << "Invalid input, enter an integer";
    cout << endl << endl;
    cin.clear();
    cin.ignore(120, '\n');
  }

  //set everything in array to NULL
  //allocate the memory for the array
  vertices = n;
  for (int i = 0; i < n; i++) 
    theArray[i] = NULL;

  while (true) {
    cout << endl;
    cout << "Do you have a edge to enter(y or n)? ";
    cin >> answer;
    if (cin.good()) {
      cout << endl;
      if (answer == "y") {
	while (true) {
	  cout << "Enter the parent edge: ";
	  cin >> node1;
	  if (cin.good() && node1 < n) {
	    cout << "Entered " << node1 << endl;
	    break;
	  }
	  
	  else {
	    cout << endl << endl;
	    cout << "You entered " << node1 << endl;
	    cout << "Invalid input. Enter a number between 0 ";
	    cout << "and " << (n-1);
	    cout << endl << endl;
	    cin.clear();
	    cin.ignore(120, '\n');
	  }

	}
	
	while (true) {
	  cout << "Enter the child edge: ";
          cin >> node2;
          if (cin.good() && node2 < n) {
            cout << "Entered " << node2 << endl;
            graphNode *item = new graphNode;
	    item->name = node2;
	    if (theArray[node1] == NULL) {
	      item->Next = NULL;
	      theArray[node1] = item;

	    }

	    else {
	      item->Next = theArray[node1];
	      theArray[node1] = item;
	    }
	    
            break;
          }

          else {
            cout << endl << endl;
            cout << "You entered " << node2 << endl;
            cout << "Invalid input. Enter a number between 0 ";
            cout << "and " << (n-1);
            cout << endl << endl;
            cin.clear();
            cin.ignore(120, '\n');

	  }
	  
	}//end of while within if yes
	
      } //end of if yes
      
      else
	break;
	
    }//end of if

    else {
      cout << endl << endl;
      cout << "You entered " << answer << endl;
      cout << "Invalid input, y or n";
      cout << endl << endl;
      cin.clear();
      cin.ignore(120, '\n');
    }
    
  }//end of while

  for (int i = 0; i < n; i++) {
    cout << "Adjacency list of " << i << endl;
    graphPtr temp;
    temp = theArray[i];
    while (temp != NULL) {
      cout << "next node in is list = " << temp->name << endl;
      temp = temp->Next;
    }
  }
  
}

graph::graph(const graph& theGraph) {

  headTopo = NULL;
  cycle = false;


  graphPtr curr = theGraph.headTopo;
  vertices = theGraph.vertices;

  cout << "Copy Constructor, n = " << vertices << endl; 
  cout << "doing DFS with copy\n";
  
  if (curr != NULL)
    headTopo = curr;
  
  graphPtr temp = headTopo;
  curr = curr->Next;
  
  while (curr != NULL) {
    temp->Next = curr;
    curr = curr->Next;
    temp = temp->Next;
  }


  
  for (int i = 0; i < theGraph.vertices; i++) {
    theArray[i] = NULL;
    if (theGraph.theArray[i] != NULL) {
      theArray[i] = theGraph.theArray[i];
      graphPtr tempC = theArray[i]->Next;
      graphPtr tempD = theGraph.theArray[i]->Next;
      while (tempD != NULL) {
	graphNode *insert = new graphNode;
	insert = tempD;
	tempC = insert;
	tempD = tempD->Next;
	tempC = tempC->Next;
      }
      
    }

  }//end of for
  
}

graph::~graph() {
  
  cout << "Deconstructor Executing\n";
  
  //delete the linked list
  if (headTopo != NULL) {
    graphPtr tempD = headTopo->Next;
    delete headTopo;
    headTopo = NULL;
    while (tempD != NULL) {
      graphPtr tempC = tempD->Next;
      delete tempD;
      tempD = NULL;
      tempD = tempC;
    }
    
  }

  
  //delete contents in theArray
  for (int i = 0; i < vertices; i++) {

    if (theArray[i] != NULL) {

      graphPtr tempD = theArray[i];
      
      while (tempD != NULL) {
	graphPtr tempC = tempD->Next;
	delete tempD;
	tempD = NULL;
	tempD = tempC;
		
      } //end of while
      
    }//end of if
    
  }//end of for
  
  
}


bool graph::DFS(int v) {

  if (v > vertices || v < 0) {
    cout << "You entered " << v << endl;
    cout << "Enter an integer between 0 and " << vertices-1<< endl;
    return false;
  }

  //delete the linked list if not NULL
  if (headTopo != NULL) {
    graphPtr tempD = headTopo->Next;
    delete headTopo;
    headTopo = NULL;
    while (tempD != NULL) {
      graphPtr tempC = tempD->Next;
      delete tempD;
      tempD = NULL;
      tempD = tempC;
    }
    
  }
  
  int visit[vertices] = {0};

  for (int i = v; i < vertices; i++) {
    if (visit[i] == 0) 
      DFS_visit(i, visit);
  }

  for (int i = 0; i < v; i++) {
    if (visit[i] == 0)
      DFS_visit(i , visit);
  }

  cout << v << " began DFS and was successful\n";
  return true;
  
}


bool graph::BFS(int v) {
  
  if (v > vertices || v < 0) {
    cout << "You entered " << v << endl;
    cout << "Enter an integer between 0 and " << vertices-1<< endl;
    return false;
  }

  bool success = true;
  queueClass Q;
  int visit[vertices] = {0};
  Q.QueueInsert(v, success);

  visit[v] = 1;
  cout << "BFS visited: " << v << endl;
  
  while (!Q.QueueIsEmpty()) {
    
    Q.QueueDelete(v, success);

    graphPtr temp = theArray[v];
    while (temp != NULL) {
      
      if (visit[temp->name] != 1) {
	Q.QueueInsert(temp->name, success);
	visit[temp->name] = 1;
	cout << "BFS visited: " << temp->name << endl;
      }

      temp = temp->Next;
      
    }//end of while
    
  }//end of if queues is empty while

  cout << v << " began BFS and was successful\n";
  return true;
  
}


void graph::topo() {
  DFS(0);

  cout << "The topological sort results:\n";

  if (cycle != true) {
    graphPtr temp = headTopo;
    
    while (temp != NULL) {
      cout << "next node in topological sort = " << temp->name << endl;
      temp = temp->Next;
    }
    cout << "Topological Sort Complete\n";
  }

  //if the graph contains a cycle
  else {
    cout << "**graph contains a cycle, top sort undefined**\n";
    cout << "Topological Sort Complete\n";
  }

}

void graph::DFS_visit(int v, int visiting[]) {

  cout << "DFS_V visiting: " << v << endl;

  visiting[v] = 1;

  graphPtr temp = theArray[v];
 
  while (temp != NULL) {
    
    if (visiting[temp->name] == 0) 
      DFS_visit(temp->name, visiting);

    else if (visiting[temp->name] == 1)
      cycle = true;
    temp = temp->Next;

  }


  visiting[v] = 2;

  graphPtr headTemp = new graphNode;

  headTemp->name = v;
  headTemp->Next = headTopo;
  headTopo = headTemp;
  
}




