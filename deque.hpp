#ifndef _DEQUE_H
#define _DEQUE_H

#include <iostream>
#include "cStack.hpp"

using namespace std;

template <typename E>
class Deque {	

	private:
		cStack<E> dequee ;
	public:
		Deque();	// constructor
		int size() const;	// number of items in the deque
		bool empty() const;		// is the deque empty?
		const E& front() const; // the first element
		const E& back() const;	// the last element
		void insertFront(const E& e);	// insert new first element
		void insertBack(const E& e);	// insert new last element
		void removeFront();	// remove first element
		void removeBack();	// remove last element
};

template <typename E>
Deque<E>::Deque(){
	
}
template <typename E>
int Deque<E>::size() const{
	int i = dequee.redsize() + dequee.bluesize();
	return i;
}

template <typename E>
bool Deque<E>::empty() const{
	if( dequee.redempty() && dequee.blueempty() ) return true;
	return false ;
}

template <typename E>
const E& Deque<E>::front() const{
	if( !dequee.redempty() ) return dequee.redtop();
	else if( dequee.redempty() && !dequee.blueempty()) return dequee.bluetop();
	else { cout << "ERROR: Deque empty" ;}
}

template <typename E>
const E& Deque<E>::back()const{
	if( !dequee.blueempty() ) return dequee.bluetop();
	else if( dequee.blueempty() && !dequee.redempty()) return dequee.redtop();
	else { cout << "ERROR: Deque empty" ;}
}

template <typename E>
void Deque<E>::insertFront(const E& e){
	if(dequee.blueempty() && !dequee.redempty()){
		E h = dequee.redtop();
		dequee.redpop();
		dequee.bluepush(h);
	}
	dequee.redpush(e);
}

template <typename E>
void Deque<E>::insertBack(const E& e){
	if( !dequee.blueempty() && dequee.redempty()){
		E h = dequee.bluetop();
		dequee.bluepop();
		dequee.redpush(h);
	}
	dequee.bluepush(e);
}

template <typename E>
void Deque<E>::removeFront(){
	if( dequee.redempty() && dequee.blueempty()) {
		cout << "ERROR : Deque empty!" << endl;
		return;
	}
	else if( dequee.redempty() && !dequee.blueempty()) dequee.bluepop();
	else {
		dequee.redpop();
		if( dequee.redempty()){
			cStack <E> temp;
			int h = dequee.bluesize();
			int mov = h/2;
			for(int j=0 ; j<mov ; j++){
				E g = dequee.bluetop();
				dequee.bluepop();
				temp.bluepush(g);
			}
			for(int j=0 ; j<h-mov ; j++){
				E g = dequee.bluetop();
				dequee.bluepop();
				dequee.redpush(g);
			}
			for(int j=0 ; j<mov ; j++){
				E g = temp.bluetop();
				temp.bluepop();
				dequee.bluepush(g);
			}
		}
	}
}

template <typename E>
void Deque<E>::removeBack(){
	if( dequee.redempty() && dequee.blueempty()) {
		cout << "ERROR : Deque empty!" << endl;
		return;
	}
	else if( !dequee.redempty() && dequee.blueempty()) dequee.redpop();
	else {
		dequee.bluepop();
		if( dequee.blueempty()){
			cStack <E> temp;
			int h = dequee.redsize();
			int mov = h/2;
			for(int j=0 ; j<mov ; j++){
				E g = dequee.redtop();
				dequee.redpop();
				temp.redpush(g);
			}
			for(int j=0 ; j<h-mov ; j++){
				E g = dequee.redtop();
				dequee.redpop();
				dequee.bluepush(g);
			}
			for(int j=0 ; j<mov ; j++){
				E g = temp.redtop();
				temp.redpop();
				dequee.redpush(g);
			}
		}
	}
}

#endif
