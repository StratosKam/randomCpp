#ifndef LL
#define LL
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class LinkedList{
	struct Node{
		int id;
		Node* next;
	};
private:
	Node* head;
	int size;
public:
	LinkedList(){
		head=NULL;
		size=0;
	}
	~LinkedList(){
		Node* node=head;
		while(node!=NULL){
			head=head->next;
			delete node;
			node=head;
		}
	}

	void add(int id){
		Node* node=new Node();
		node->id=id;
		node->next=head;
		head=node;
		++size;
	}
	void addAll(LinkedList linkedList){
		for(int i=0;i<linkedList.getSize();i++){
			add(linkedList.get(i));
		}
	}

	void addAll(LinkedList *linkedList){
		for(int i=0;i<linkedList->getSize();i++){
			add(linkedList->get(i));
		}
	}

	void removeAll(int id){
		if(size==0){
			return;
		}
		Node *node=head,*previous;
		while(node->id== id){
			head=head->next;
			delete node;
			node=head;
			--size;
			if(node==NULL){
				return;
			}
		}
		previous=head;
		node=head->next;
		while(node!=NULL){
			if(node->id==id){
				previous->next=node->next;
				--size;
				delete node;
				node=previous->next;
			}else{
				previous=node;
				node=node->next;
			}

		}
		
	}

	void change(int from,int to){
		if(size==0){
			return;
		}
		Node* node=head;
		while(node != NULL){
			if(node->id==from){
				node->id=to;
			}
			node=node->next;
		}
		
	}
	bool contains(int id){
		if(size==0){
			return false;
		}
		Node* node=head;
		while(node->id != id){
			if(node->next==NULL){
				return false;
			}
			node=node->next;
		}
		return true;
	}

	void print(){
		Node* node=head;
		while(node!=NULL){
			cout<<node->id<<" ";
			node=node->next;
		}
		cout<<endl;
	}

	int getSize(){
		return size;
	}

	int get(int index){
		if(index>=size){
			return -1;
		}
		Node* node=head;
		for(int i=0;i<index;i++){
			node=node->next;
		}
		return node->id;
	}

	int removeRandom(){
		if(size==0){
			return -1;
		}
		int id;
		if(size==1){
			id=head->id;
			delete head;
			head=NULL;
			size=0;
		}else{
			int random=rand()%size;
			id=get(random);
			removeAll(id);
		}
		
		return id;
	}
};

#endif