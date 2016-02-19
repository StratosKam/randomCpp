#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "LinkedList.cpp"
#include "Graph.cpp"

using namespace std;

/**
*
* 1 argument: path to graph file
*
**/
int main(int argc, char* argv[]){

	ifstream file(argv[1]);
	string linebuffer;
	Graph graph;
	LinkedList *neighbors;
	while (file && getline(file, linebuffer)){
		if (linebuffer.length() != 0){
			char *characters = const_cast<char*>(linebuffer.c_str());
			char* tokens=strtok(characters,"\t");
			int vertexId=atoi(tokens);
			tokens = strtok (NULL, "\t");
			neighbors=new LinkedList;
			int number;
			while (tokens != NULL){
				number=atoi(tokens);
				tokens = strtok (NULL, "\t");
				if(tokens!=NULL){
					neighbors->add(number);
				}
			}

			graph.add(vertexId,neighbors);
		}
	}

	srand(time(NULL));	
	cout<<"Karger: "<<graph.getMinCut(false)<<endl;
	cout<<"Karger-Stein: "<<graph.getMinCut(true)<<endl;

	return 0;
}