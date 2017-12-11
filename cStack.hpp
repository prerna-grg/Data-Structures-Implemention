#ifndef _CSTACK_H
#define _CSTACK_H

#include <iostream>
using namespace std;
template <typename E>
class cStack {

	private: 
		int cap;
		E* ar;
	 	int top_r;
	 	int top_b;
	 	
	public:

		cStack(int cap = 100); // constructor from capacity
		cStack(const cStack<E> &S); //copy constructor
		int redsize() const;		// number of items in stack
		bool redempty() const;		// is the stack empty?
		const E& redtop() const;	      		// the top element
		void redpush(const E& e); 		// push x onto the stack
		void redpop();		      	// remove the top element
		int bluesize() const;               // number of items in stack
		bool blueempty() const;             // is the stack empty?
		const E& bluetop() const;           // the top element
		void bluepush(const E& e);          // push x onto the stack
		void bluepop();                     // remove the top element 		
};

template <typename E>
cStack<E>::cStack(int n){
	this->cap = n;
	ar = new E[cap];
	top_r = -1;
	top_b = n;
}

template <typename E>
cStack<E>::cStack(const cStack<E> &S){
	cap = S.cap;
	ar = new E[cap];
	for(int i=0;i<cap;i++){
		ar[i]=S.ar[i];
	}
	top_r = S.top_r;
	top_b = S.top_b;
}

template <typename E>
int cStack<E>::redsize() const{
	return top_r+1 ;
}

template <typename E>
int cStack<E>::bluesize() const{
	return cap-top_b;
}

template <typename E>
bool cStack<E>::redempty() const{
	if(top_r==-1)return true;
	return false;
}

template <typename E>
bool cStack<E>::blueempty() const{
	if(top_b==cap)return true;
	return false;
}

template <typename E>
void cStack<E>::redpush(const E& e){
	if(top_b-top_r > 1){
		top_r++;
		ar[top_r] = e;
	}
	else{
		cout << "ERROR: Full" << endl;
		return;
	}
}

template <typename E>
void cStack<E>::bluepush(const E& e){
	if(top_b-top_r > 1){
		top_b--;
		ar[top_b] = e;
	}
	else{
		cout << "ERROR: Full" << endl;
		return;
	}
}

template <typename E>
const E& cStack<E>::redtop() const{
	if(!redempty())return ar[top_r];
	else cout << "ERROR: Empty" << endl;
}

template <typename E>
const E& cStack<E>::bluetop() const{
	
	if(!blueempty())return ar[top_b];
	else cout << "ERROR: Empty" << endl;
}

template <typename E>
void cStack<E>::redpop(){
	if(!redempty())top_r--;
	else{
		cout << "ERROR: Red Empty" << endl;
		return;
	}
}

template <typename E>
void cStack<E>::bluepop(){
	if(!blueempty())top_b++;
	else{
		cout << "ERROR: Blue Empty" << endl;
		return;
	}
}

#endif
