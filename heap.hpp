#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
using namespace std;

template <typename E>
class node{
	private:
		E elem;
		node<E>* parent;
		node<E>* left;
		node<E>* right;
	public:
		node();
		node(E e);
	template <typename T , typename C> friend class Heap;
};

template <typename E, typename C>	// element and comparator
class Heap{
	private:
		int heapsize;
		E* Arr;
		node<E>* root;
		node<E>* last;
	public:
		Heap(); //Constructor
		int size() const;	// number of elements
		bool isEmpty() const;	// is the queue empty?
		void insert(const E& e);	// insert element
		const E& min() const;	// minimum element
		void removeMin();	// remove minimum
		void mergeHeaps(Heap H);	//MODIFIED 
		void buildHeap(E A[], int size);
		void UpHeapify(node<E>*);
		void DownHeapify(node<E>*);
		bool getSmall(const E& e1, const E& e2,  C& isLess);
		void preorder(E* A , node<E>* , int ,int);
		//One function to do the traversal 
		void heapDelete(node<E>* );
};

//default constructor for node
template <typename E>
node<E>::node(){
	parent = NULL;
	left = NULL;
	right = NULL;
};

//copy constructor
template <typename E>
node<E>::node(const E a){
	elem = a;
	parent = NULL;
	left = NULL;
	right = NULL;
};

//default constructor for heap
template <typename E, typename C>
Heap<E,C>::Heap(){
	heapsize=0;
	root = NULL;
	last = NULL;
}

//return size of the heap
template <typename E, typename C>
int Heap<E,C>::size() const{
	return heapsize;
}

template <typename E, typename C>
bool Heap<E,C>::isEmpty() const {
	return heapsize==0;
}

template <typename E, typename C>
void Heap<E,C>::insert(const E& e){

	node<E>* newnode = new node<E>(e);
	if(heapsize==0){
		root = last = newnode;
		heapsize++;
		return;
	}
	else if(heapsize==1){
		root->left = newnode;
		root->left->parent = root;
		last = root->left;
		heapsize++;
		UpHeapify(last);
		return;
	}
	else{
		heapsize++;
		if( last == last->parent->left ){
			last->parent->right = newnode;
			last->parent->right->parent = last->parent;
			last = last->parent->right;
			UpHeapify(last);
			return;
		}
		else{
			node<E>* temp = last;
			while(temp!=root){
				if(temp==temp->parent->left) break;
				temp = temp->parent;
			}
			if(temp!=root) temp = temp->parent->right ;
			while(temp->left != NULL) temp = temp->left;
			temp->left = newnode;
			newnode->parent = temp;
			last = newnode;
			UpHeapify(newnode);
			return;
		}
	}	
}

template <typename E, typename C>
bool Heap<E,C>::getSmall(const E& e1, const E& e2,  C& isless) {
	return (isless(e1, e2) ? true : false) ;
}

template <typename E, typename C>
void Heap<E,C>::UpHeapify(node<E>* n){
	
	C isless;
	while( n->parent!= NULL ){
		if( getSmall(n->elem,n->parent->elem , isless)){
			E temp = n->parent->elem;
			n->parent->elem = n->elem;
			n->elem = temp;
			n = n->parent;
		}
		else break;
	}
}

template <typename E, typename C>
void Heap<E,C>::DownHeapify(node<E>* n){

	C isless;
	while( n->left!=NULL || n->right!=NULL ){
		if( n->right==NULL){
			if( getSmall(n->left->elem , n->elem , isless)){
				E temp = n->elem;
				n->elem = n->left->elem;
				n->left->elem = temp;
			}
			return;
		}
		if( !getSmall(n->elem,n->left->elem,isless) || !getSmall(n->elem,n->right->elem,isless)  ){
			if( getSmall(n->left->elem , n->right->elem , isless)){
				E temp = n->elem;
				n->elem = n->left->elem;
				n->left->elem = temp;
				n = n->left;
			}else{
				E temp = n->elem;
				n->elem = n->right->elem;
				n->right->elem = temp;
				n = n->right;
			}
		}
		else return;
	
	}
}

template <typename E, typename C>
const E& Heap<E,C>::min() const{
	if(heapsize==0)cout << "ERROR: Heap empty ... Cannot return min" << endl;
	else return root->elem;
}

template <typename E, typename C>
void Heap<E,C>::removeMin(){
	if(heapsize==0){ cout << "ERROR: heap empty" << endl; return; }
	else if(heapsize==1){
		node<E>* temp1 = root;
		root = last = NULL;
		delete(temp1);
		heapsize = 0;
		return;
	}else{
		heapsize--;
		E temp1 = last->elem;
		last->elem = root->elem;
		root->elem = temp1;
		node<E>* temp = last;
		if(last == last->parent->right){
			node<E>* temp1 = last;
			last = last->parent->left;
			last->parent->right = NULL; 
			delete(temp1);
		}else{
			while( temp!=root ){
				if(temp == temp->parent->right) break;
				temp=temp->parent;
			}
			if(temp!=root) temp=temp->parent->left;
			while(temp->right !=NULL) temp = temp->right;
			node<E>* temp1 = last;
			last->parent->left = NULL;
			last = temp;
			delete(temp1);
		}
		DownHeapify(root);
	}
}

template <typename E, typename C>
void Heap<E,C>::mergeHeaps(Heap H){
	int size = heapsize+H.size() ;
	E A[size];
	Arr = new E[heapsize];
	H.Arr = new E[H.size()];
	preorder( Arr , root , 0 , heapsize);
	preorder( H.Arr , H.root , 0 , H.size());
	for( int i=0 ; i<heapsize ; i++) A[i] = Arr[i];
	for( int i=0 ; i<H.size() ; i++) A[i+heapsize] = H.Arr[i];
	heapsize=0;
	buildHeap(A,size);
}

template <typename E, typename C>
void Heap<E,C>::preorder( E* A , node<E>* head , int i , int size){
	if(i>=size)return;
	A[i] = head->elem;
	preorder(A , head->left , 2*i+1 , size);
	preorder(A , head->right , 2*i+2 , size);
}

template <typename E, typename C>
void Heap<E,C>::buildHeap( E A[] , int size){
	if(size==0)return;
	heapDelete(root);
	node<E>* arr[size];
	for(int h=0 ; h<size ; h++)arr[h] = new node<E>(A[h]);
	heapsize = size;
	for(int i=size/2-1 ; i>=0 ; i--){
		int c1 = 2*i+1;
		int c2 = 2*i+2;
		if(c1<size){
			arr[i]->left = arr[c1];
			arr[c1]->parent = arr[i];
		}
		if(c2<size){
			arr[i]->right = arr[c2];
			arr[c2]->parent = arr[i];
		}
		DownHeapify(arr[i]);
	}
	root = arr[0];
	last = arr[size-1];
	heapsize = size;
}

template <typename E, typename C>
void Heap<E,C>::heapDelete(node<E>* head){
	if( head==NULL) return;
	heapDelete(head->left);
	heapDelete(head->right);
	delete(head);
}

#endif
