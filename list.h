#ifndef LIST_H
#define LIST_H

#include <string>
using namespace std;



template <class  T> class list;

//clase nodo de lista, con apuntador al siguiente y al anterior
template <class  T> class Node{
	friend class list<T>;
public:
	T data;
	Node *sig;
	Node *ante;

	Node(){ sig = ante = NULL; };
};


//clase lista con doble apuntador para poder insertar en O(1) en cualquier posicion
//y realizada con templates para su mejor uso
template <class  T> class list{
public:
	typedef Node<T> * Posicion;
	list();
	~list();
	Posicion  First();
	Posicion  Last();
	Posicion  End();
	Posicion  Next(Posicion pos);
	Posicion  Prev(Posicion pos);
	void Insert(T valor, Posicion pos);
	void Erase(Posicion pos);
	bool getValue(Posicion  pos, T **valor);
	int getSize();
	bool isEmpty();
	void Clear();

private:
	

	Posicion pri, ult;
	int tamano;



};


//constructor por defecto
template <class T> list<T>::list(){
	//inicializa variables de la lista
	tamano = 0;
	pri = ult = NULL;
}


// destructor por defecto
template <class T> list<T>::~list(){
	Posicion temp = pri;

	//borra todos los elementos de la lista
	while (temp != NULL){
		Posicion temp2 = temp;
		temp = temp->sig;
		delete temp2;
	}

	pri = ult = NULL;
}


//retorna la posicion del primer elemento de la lista
template <class  T>
typename list<T>::Posicion  list<T>::First(){
	return pri;
}


//retorna la posicion del ultimo elemento de la lista
template <class  T>
typename list<T>::Posicion   list<T>::Last(){
	return ult;
}


//retorna la posicion despues del ultimo elemento de la lista, es decir, null
template <class  T>
typename list<T>::Posicion   list<T>::End(){
	return NULL;
}


//Avanza la posicion a la siguiente posicion
//pos tiene que ser diferente de End
template <class  T>
typename list<T>::Posicion   list<T>::Next(Posicion pos){
	return pos->sig;
}

template <class  T>
typename list<T>::Posicion   list<T>::Prev(Posicion pos){
	return pos->ante;
}

/*
inserta un elemento en la lista en la posicion pos.
si pos es igual a End se inserta el elemento en la ultima posicion de la lista
*/
template <class  T>
void list<T>::Insert(T valor, Posicion pos){

	//creo el nuevo nodo con la informacion
	Posicion t = new Node<T>();
	t->data = valor;



	//si pri es nulo, la lista esta vacia e inserto el elemento de primero
	if (isEmpty())
	{
		pri = ult = t;
		t->sig = t->ante = NULL;
	}
	else if (First() == pos){ //si lo inserto de primero		
		//Se coloca antes de pos
		t->sig = pos;
		pos->ante = t;
		t->ante = NULL;
		pri = t;
	}
	else if (Last() == pos){
		//no pasa nada, el ultimo sigue siendo el ultimo
		//Se coloca antes de pos
		t->sig = pos;
		t->ante = pos->ante;
		t->ante->sig = t;
		pos->ante = t;
	}
	else if (pos == End()){
		ult->sig = t;
		t->ante = ult;
		t->sig = NULL;
		ult = t;
	}

	tamano++;
}

/*
borra el nodo de la lista encontrado en la posicion pos
el valor pos debe ser diferente de End
posicion queda con un valor invalido
*/
template <class  T>
void list<T>::Erase(Posicion pos){
	if (isEmpty()) return; //no hay valor que borrar
	if (pos == End()) return; //posicion no es valida


	//pongo al anterior, si existe, apuntado al nuevo siguiente 
	if (pos->ante != NULL){
		pos->ante->sig = pos->sig;
	}

	//pongo al siguiente, si existe, apuntado al anterior
	if (pos->sig != NULL){
		pos->sig->ante = pos->ante;
	}

	if (pos == Last()) ult = pos->ante; //muevo el ult de ser necesario
	if (pos == First()) pri = pos->sig; //muevo el primero de ser necesario

	delete pos; //libero la memoria
	tamano--;
}



/*
retorna el valor de una posicion de la lista
el valor pos debe ser diferente de End
*/
template <class  T>
bool list<T>::getValue(Posicion pos, T **valor){
	if (pos == End()) return false;

	*(valor) = &(pos->data);

	return true;
}


//retorna el tamano de la lista
template <class  T>
int list<T>::getSize(){
	return tamano;
}


//retorna si la lista esta vacia o no
template <class  T>
bool list<T>::isEmpty(){
	return First() == NULL;
}

//metodo para vaciar la lista
template <class  T>
void list<T>::Clear(){
	Posicion temp = pri;

	//borra todos los elementos de la lista
	while (temp != NULL){
		Posicion temp2 = temp;
		temp = temp->sig;
		delete temp2;
	}

	pri = ult = NULL;

	tamano = 0;
}

#endif