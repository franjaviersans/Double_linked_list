#ifndef LIST_H
#define LIST_H

#include <string>
using namespace std;



template <class  T> class list;

//list class node, with pointer to the next and prev node
template <class  T> class Node{
	friend class list<T>;
public:
	T data;
	Node *next;
	Node *prev;

	Node(){ next = prev = NULL; };
};


//double linked list class that allows insertions in O(1) at every position
//and done with templates for a more flexible use
template <class  T> class list{
public:
	typedef Node<T> * Position;
	list();
	~list();
	Position  first();
	Position  last();
	Position  end();
	Position  next(Position pos);
	Position  prev(Position pos);
	void insert(T value, Position pos);
	void erase(Position pos);
	bool getValue(Position  pos, T **value);
	int getSize();
	bool isEmpty();
	void clear();

private:


	Position fir, las;
	int size;



};


//default constructor
template <class T>
list<T>::list(){
	//initialize all variables
	size = 0;
	fir = las = NULL;
}


//default destructure
template <class T>
list<T>::~list(){
	clear();
}


//return the position of the first element on the list
template <class  T>
typename list<T>::Position  list<T>::first(){
	return fir;
}


//return the position of the las element of the list
template <class  T>
typename list<T>::Position   list<T>::last(){
	return las;
}


//return the position after the las element of the list, which is null
template <class  T>
typename list<T>::Position   list<T>::end(){
	return NULL;
}


//advance the position to the next position
//pos must be different to end
template <class  T>
typename list<T>::Position   list<T>::next(Position pos){
	return pos->next;
}

//advance the position to the previous position
//pos must be different to end
template <class  T>
typename list<T>::Position   list<T>::prev(Position pos){
	return pos->prev;
}

//inset an element on the list at the position pos
//if pos is equal to end, insert the element in the las position of the list
template <class  T>
void list<T>::insert(T value, Position pos){

	//create a node with information
	Position t = new Node<T>();
	t->data = value;

	//if fir is null, the list is empty, and the element is inserted in the first position
	if (isEmpty())
	{
		fir = las = t;
		t->next = t->prev = NULL;
	}
	else if (first() == pos){ //if the insertion is in the first position
		//the new element goes before pos
		t->next = pos;
		pos->prev = t;
		t->prev = NULL;
		fir = t;
	}
	else if (last() == pos){
		//nothing happends, the last element remains the las element
		//the new element goes before pos
		t->next = pos;
		t->prev = pos->prev;
		t->prev->next = t;
		pos->prev = t;
	}
	else if (pos == end()){
		las->next = t;
		t->prev = las;
		t->next = NULL;
		las = t;
	}

	size++;
}


//erase the node of the list at the position pos
//the value pos must be different to end
//the actual position is updated to an invalid value
template <class  T>
void list<T>::erase(Position pos){
	if (isEmpty()) return; //there is nothing to erase
	if (pos == end()) return; //pos is an invalid position

	if (pos->prev != NULL){
		pos->prev->next = pos->next;
	}

	if (pos->next != NULL){
		pos->next->prev = pos->prev;
	}

	if (pos == last()) las = pos->prev;
	if (pos == first()) fir = pos->next;

	delete pos; //erase memory
	size--;
}



//returns the value at the position pos
//the value pos must be different to end
template <class  T>
bool list<T>::getValue(Position pos, T **value){
	if (pos == end()) return false;

	*(value) = &(pos->data);

	return true;
}

//return the size of the list
template <class  T>
int list<T>::getSize(){
	return size;
}

//return true if the list is empty
template <class  T>
bool list<T>::isEmpty(){
	return first() == NULL;
}

//method to clear the list
template <class  T>
void list<T>::clear(){
	Position temp = fir;

	//erase all the elements in the list
	while (temp != NULL){
		Position temp2 = temp;
		temp = temp->next;
		delete temp2;
	}

	fir = las = NULL;

	size = 0;
}

#endif