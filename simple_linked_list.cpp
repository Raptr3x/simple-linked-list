/* 
add(); ------------------ DONE
count(); ---------------- DONE
count_from(); ----------- DONE
remove(); --------------- DONE
remove_all(); ----------- DONE
insert_after(); --------- DONE
insert_before(); -------- DONE

find_node_by_data(); ---- DONE
list_empty(); ----------- DONE
*/

#include <iostream>
#include <vector>
#include "spdlog/spdlog.h"

using namespace std;
using namespace spdlog;

struct node{
	int data;
	node *next;	
};
node *head = NULL;

bool list_empty(){
	/*
	returns true if list is empty
	*/
	if(head==NULL){
		debug("List is empty");
		return true;
	}
	debug("List not empty");
	return false;
}

vector<node*> find_node_by_data(int value, node *ptr){
	/*
	Returns an vector where first item is adress of targeted node
	and second item is a node that was before targeted node

	second element is NULL if no previous nodes
	*/
	debug("Finding node");
	node * old_ptr = NULL;
	while(ptr->data!=value){
		old_ptr=ptr;
		ptr=ptr->next;
		if(ptr==NULL){
			info("No such item after given node pointer");
			break;
		}
	}
	if(ptr->data==value){
		debug("Node found");
		vector<node*> nodes = {ptr, old_ptr};
		return nodes;
	}
}

void add(int value){
	/*
	Adds value to the list
	*/
	node *temp = new node;
	temp->data = value;
	temp->next = head;
	head=temp;
	debug("Added value {}", value);
}

int count(){
	/*
	Counts how many elements is there in the list
	*/
	node *ptr = head;
	if (list_empty())
		return 0;
	unsigned int n=0; //start of counting
	while(ptr!=NULL){
		n++;
		ptr = ptr->next;
	}
	info("List consists of {} elements", n);
}

int count_from(int data){
	/*
	Counts how many elements is there from given element to first one
	*/
	node *ptr = head;
	if(list_empty()){
		return 0;
	}
	ptr = find_node_by_data(data, ptr)[0];
	if(ptr->data==data){
		unsigned int n=0; //start of counting
		while(ptr!=NULL){
			n++;
			ptr = ptr->next;
		}
		if(ptr==NULL){
			info("value {} is {} elements from beginning", data, n);
		}
		return 0;
	}
}

int display(){
	/*
	Displays the list
	*/
	node *ptr = head;
	if(list_empty()){
		return 0;	
	}
	cout<<"list:";
	while(ptr!=NULL){
		cout<<"  "<<ptr->data;
		ptr = ptr->next;
	}
	cout<<endl;
}

void insert_after(int insert_value, int targeted_value){
	/*
	Inserts element after given value

	First arg is value to be inserted
	Second arg is value that should be after
	*/
	node* ptr = head;
	vector<node*> v;
    v = find_node_by_data(targeted_value, ptr); //takes nodes before=>[1] and target=>[0];
    if(v[1]==0){
    	//found node was first, no node before
    	add(insert_value);
    }
    else{
    	node* tmp = new node;
    	tmp->data = insert_value;
    	v[1]->next = tmp;
    	tmp->next = v[0];
    	debug("Added value {}", insert_value);
    }
}

void insert_before(int insert_value, int targeted_value){
	/*
	Inserts element before given value

	First arg is value to be inserted
	Second arg is value that should be before
	*/
	node* ptr = head;
	vector<node*> v;
	v = find_node_by_data(targeted_value, ptr);
	node* tmp = new node;
	tmp->data = insert_value;
	tmp->next = v[0]->next;
	v[0]->next = tmp;
}

void remove(int value){
	/*
	Removes an element
	*/
	node* ptr = head;
	vector<node*> v = find_node_by_data(value, ptr);
	if(v[1]!=0){
		v[1]->next = v[0]->next;
	}
	else{
		head = v[0]->next;
	}
	delete v[0];
	debug("Removed value {}", value);
}

void remove_all(){
	/*
	Removes all elements from the list

	head becomes NULL
	*/
	node* ptr = head;
	node* nextNode;
	while(ptr!=NULL){
		nextNode=ptr->next;
		delete ptr;
		ptr=nextNode;
	}
	head=NULL;
	info("Whole list is cleared!");
}

int main(){
	set_level(level::debug);
	add(1);
	add(3);
	add(2);
	add(5);
	add(7);
	display();
	insert_before(4, 1);
	insert_after(12, 1);
	remove(4);
	display();
	count_from(1);
	count();
	remove_all();
	display();
	return 0;
}