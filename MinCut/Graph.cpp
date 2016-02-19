#include <iostream>
#include <fstream>
#include <math.h>
#include "LinkedList.cpp"
#include <stdlib.h>
#include <time.h>

using namespace std;
class Graph{
	struct Vertex{
		int id;
		LinkedList* neighbors;
		Vertex* next;
	};
private:
	Vertex* head;
	int size;

	int karger(){
		while(size>2){
			contraction();
		}
		return(head->neighbors->getSize());
	}

	int kargerStein(int threshold){
		while(size>threshold){
			contraction();
		}
		int first=getCopy().karger();
		int second=getCopy().karger();
		if(first<second){
			return first;
		}else{
			return second;
		}
	}

	void contraction(){
		if(size<=2){
			return;
		}
		int pos1=rand()%size;
		
		Vertex *vertex1;
		if(pos1==0){
			vertex1=head;
		}else{
			vertex1=head;
			for(int i=0;i<pos1;i++){
				vertex1=vertex1->next;
			}
		}
		int id2=vertex1->neighbors->removeRandom();

		Vertex* vertex2;
		if(head->id==id2){
			vertex2=head;
			head=head->next;
		}else{
			Vertex *previous=head;
			vertex2=head->next;
			while(vertex2->id!=id2){
				previous=vertex2;
				vertex2=vertex2->next;
			}
			previous->next=vertex2->next;
		}	
		vertex2->neighbors->removeAll(vertex1->id);
		vertex1->neighbors->addAll(vertex2->neighbors);
		for(int i=0;i<vertex2->neighbors->getSize();i++){
			changeEdge(vertex2->neighbors->get(i),vertex2->id,vertex1->id);
		}
		--size;
		delete vertex2->neighbors;
		delete vertex2;
	}

	void changeEdge(int at,int from,int to){
		Vertex* vertex=head;
		while(vertex->id != at){
			if(vertex==NULL){
				return;
			}
			vertex=vertex->next;
		}
		if(at==from || at==to){
			vertex->neighbors->removeAll(from);
			vertex->neighbors->removeAll(to);
		}else{
			vertex->neighbors->change(from,to);	
		}
	}
public:
	Graph(){
		head=NULL;
		size=0;
	}

	~Graph(){
		Vertex* vertex=head;
		while(vertex!=NULL){
			head=head->next;
			delete vertex->neighbors;
			delete vertex;
			vertex=head;
		}
	}
	
	Graph getCopy(){
		Graph copy;
		Vertex* vertex=head;
		while(vertex!=NULL){
			copy.addDeep(vertex->id,vertex->neighbors);
			vertex=vertex->next;
		}
		return copy;

	}

	void add(int id,LinkedList *neighbors){
		Vertex* vertex=new Vertex();
		vertex->id=id;
		vertex->neighbors=neighbors;
		vertex->next=head;
		++size;
		head=vertex;
	}

	void addDeep(int id,LinkedList *neighbors){
		Vertex* vertex=new Vertex();
		vertex->id=id;
		vertex->neighbors=new LinkedList;
		vertex->neighbors->addAll(neighbors);
		vertex->next=head;
		++size;
		head=vertex;
	}

	int getMinCut(bool stein){
		// srand(time(NULL));	
		if(stein){
			return getCopy().kargerStein(size/sqrt(2));
		}else{
			return getCopy().karger();
		}
		
	}
	
	void print(){
		Vertex* vertex=head;
		while(vertex!=NULL){
			cout<<vertex->id<<" - ";
			vertex->neighbors->print();
			cout<<endl;
			vertex=vertex->next;
		}
	}


};