#ifndef _nmap_h
#define _nmap_h

#define NN 743
typedef long long int ll;
#include <iostream>
#include <typeinfo>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

template <typename K , typename V>
class Node1 {
		K num ;
		V blnc ;
		Node1<K,V>* next ;
	public:
		Node1();
		Node1(K k, V v);
	template <typename Kk , typename Vv> friend class Linkedlist1 ;
	
};

template <typename K , typename V>
class Linkedlist1 {
		Node1<K,V> *head ;
		int size;
	public:
		void insert(K n , V m);
		void remove(K);
		V check( K k);
		Linkedlist1();
		~Linkedlist1();
	template <typename Kk , typename Vv> friend class Number_Map ;
		
};

//NODE DEFAULT CONSTRUCTOR
template <typename K , typename V>
Node1<K,V>::Node1(){
	next = NULL ;
};

//NODE GENERIC CONSTRUCTOR
template <typename K , typename V>
Node1<K,V>::Node1(K k, V v){
	num = k;
	blnc = v;
	next = NULL ;
};

//LINKEDLIST CONSTRUCTOR
template <typename K , typename V>
Linkedlist1<K,V>::Linkedlist1(){
    head = NULL;
    size = 0;
}

//LINKEDLIST DESTRUCTOR
template <typename K , typename V>
Linkedlist1<K,V>::~Linkedlist1(){

	while(head!=NULL){
		Node1<K,V>*temp = head->next ;
		delete head ;
		head = temp ;
	}
	head==NULL;
}

//ADD FUNCTION FOR NODES
template <typename K , typename V>
void Linkedlist1<K,V>::insert(K n , V m){
	Node1<K,V>* newnode = new Node1<K,V>(n,m);
	Node1<K,V>* temp = head;
	if(temp==NULL){
		head = newnode ;
		size++;
		return ;
	}
	while( temp->next!=NULL){	
		if( temp->num == n){
			temp->blnc = m;
			return;
		}else temp = temp->next;
	}
	if( temp->num == n) {
		temp->blnc = m;
		return;
	}else{
		temp->next = newnode;
		newnode->next=NULL;
		size++;
	}
	return;
}

template <typename K , typename V>
V Linkedlist1<K,V>::check(K k){
	Node1<K,V>* temp = head;
	while(temp!=NULL){
		if( temp->num == k )return temp->blnc;
		else temp = temp->next;
	}
	return -1 ;
}

//REMOVES NODE FROM THE LINKED LIST
template <typename K , typename V>
void Linkedlist1<K,V>::remove( K k){
	
	Node1<K,V>*temp = head ;
	Node1<K,V>*temp_p = head ;
	if(temp==NULL){cout << "Error: Not found" << endl;return;}
	if(temp->next==NULL){
		if(temp->num == k){
			head = NULL;
			size--;
			delete(temp);
		}
		else cout << "Error: Not found" << endl;
		return;
	}
	if( temp->num == k){
		head = temp->next;
		size--;
		delete(temp);
		return;
	}
	while(temp!=NULL){
		if(temp->num == k){
			temp_p->next = temp->next;
			delete temp;
			size--;
			return;
		}else{
			temp_p = temp;
			temp = temp->next;
		}
	}
	cout << "Error: Not found" << endl;
}

template <typename K, typename V>
class Number_Map {	// map interface
	Linkedlist1<K,V> Map1[12][NN];
	int collisions[12];
	int noe;
	public:
		Number_Map();
		Number_Map(int capacity);	// constructor
		int size() const;				// number of entries in the map
		bool empty() const;				// is the map empty?
		V find( const K& k) ;	// find entry with key k
		void put( const K& k, const V& v);	// insert/replace pair (k,v)
		void erase( const K& k);		// remove entry with key k
		void hash_fun(int i , unsigned int sum , K k , V v);
		unsigned int int_cast( int x , int y );
		unsigned int comp_sum( int x , int y);
		unsigned int poly_sum( int x , int y );
		unsigned int cyc_sum( int x , int y );
		void printMap();
};

template <typename K, typename V>
Number_Map<K,V>::Number_Map(){noe=0; for(int i=0 ; i<12 ; i++)collisions[i]=0;}

template <typename K, typename V>
Number_Map<K,V>::Number_Map(int capacity){noe=0; for(int i=0 ; i<12 ; i++)collisions[i]=0;}

template <typename K, typename V>
int Number_Map<K,V>::size() const{return noe;}

template <typename K, typename V>
bool Number_Map<K,V>::empty() const{return noe==0;}

template <typename K, typename V>
void Number_Map<K,V>::put( const K& k , const V& v){
	noe++;
	int sum=0;
	int x = (int)(k>>32);
	int y = (int)k;
	/************************************COMPONENT SUM*****************************************/
	sum = comp_sum(x,y);
	hash_fun(0,sum,k,v);
	/***********************************POLYNOMIAL SUM********************************************/
	sum = poly_sum(x,y);
	hash_fun(1,sum,k,v);
	/***************************************CYCLIC SUM***********************************************/
	sum = cyc_sum(x,y);
	hash_fun(2,sum,k,v);
	/****************************************INTEGER CASTING************************************/
	sum = int_cast(x,y);
	hash_fun(3,sum,k,v);
}

template <typename K, typename V>
unsigned int Number_Map<K,V>::int_cast( int x , int y ){
	x = x&0x7fffffff ;
	y = y&0x7fffffff ;
	return (unsigned)x+y;
}

template <typename K, typename V>
unsigned int Number_Map<K,V>::comp_sum( int x , int y){
	return (unsigned)x+y;
}

template <typename K, typename V>
unsigned int Number_Map<K,V>::poly_sum( int x , int y){
	return (unsigned)33*x + y;
}

template <typename K, typename V>
unsigned int Number_Map<K,V>::cyc_sum( int x , int y){
	x = (x << 5) | (x >> 27);
	return (unsigned)x+y;
}

template <typename K, typename V>
void Number_Map<K,V>::hash_fun(int i , unsigned int sum , K k , V v){

		if( (int)sum<0 ) sum = -1*sum ;
		int index = 0;
		index = sum%NN;
		if( i==0 ) {
			if( Map1[0][index].head!=NULL)collisions[0]++;
			Map1[0][index].insert(k,v); // COMPONENET SUM AND DIVISION
		}
		if( i==1 ) {
			if( Map1[3][index].head!=NULL)collisions[3]++;
			Map1[3][index].insert(k,v); // POLUNOMIAL SUM AND DIVISION
		}
		if( i==2 ) {
			if( Map1[6][index].head!=NULL)collisions[6]++;
			Map1[6][index].insert(k,v); // CYCLIC SUM AND DIVISION
		}
		if( i==3 ) {
			if( Map1[9][index].head!=NULL)collisions[9]++;
			Map1[9][index].insert(k,v);  // INTEGER CASTING AND MAD
		}
	
		int a = 2539 , b = 2521;
		index = (a*sum + b)%NN;
		if( i==0 ) {
			if( Map1[1][index].head!=NULL)collisions[1]++;
			Map1[1][index].insert(k,v); // COMPONENET SUM AND DIVISION
		}
		if( i==1 ) {
			if( Map1[4][index].head!=NULL)collisions[4]++;
			Map1[4][index].insert(k,v); // POLUNOMIAL SUM AND DIVISION
		}
		if( i==2 ) {
			if( Map1[7][index].head!=NULL)collisions[7]++;
			Map1[7][index].insert(k,v); // CYCLIC SUM AND DIVISION
		}
		if( i==3 ) {
			if( Map1[10][index].head!=NULL)collisions[10]++;
			Map1[10][index].insert(k,v);  // INTEGER CASTING AND MAD
		}
		
		index = ((int)(4096*((sum*0.6180339887 - (int)(sum*0.6180339887)))))%743;
		if( i==0 ) {
			if( Map1[2][index].head!=NULL)collisions[2]++;
			Map1[2][index].insert(k,v); // COMPONENET SUM AND DIVISION
		}
		if( i==1 ) {
			if( Map1[5][index].head!=NULL)collisions[5]++;
			Map1[5][index].insert(k,v); // POLUNOMIAL SUM AND DIVISION
		}
		if( i==2 ) {
			if( Map1[8][index].head!=NULL)collisions[8]++;
			Map1[8][index].insert(k,v); // CYCLIC SUM AND DIVISION
		}
		if( i==3 ) {
			if( Map1[11][index].head!=NULL)collisions[11]++;
			Map1[11][index].insert(k,v);  // INTEGER CASTING AND MAD
		}
}

template <typename K, typename V>
V Number_Map<K,V>::find(const K& k) {
	
	unsigned int x = (int)(k>>32);
	unsigned int y = (int)k;
	unsigned int sum= poly_sum(x,y);
	if( (int)sum<0 ) sum = -1*sum ;
	int a=2539 , b=2521;
	int index = (a*sum + b)%NN;
	V s = Map1[4][index].check(k);
	return s;
}

template <typename K, typename V>
void Number_Map<K,V>::erase(const K& k){
	
	int index = 0;
	unsigned int sum[3];
	int a = 2539;
	int b = 2521;
	unsigned int x = (int)(k>>32);
	unsigned int y = (int)k;
	sum[0] = comp_sum(x,y);
	sum[1] = poly_sum(x,y);
	sum[2] = cyc_sum(x,y);
	sum[3] = int_cast(x,y);

	for(int i=0 ; i<4 ; i++){
		if( (int)sum[i]<0 ) sum[i] = (int)sum[i]*-1 ;
		index = sum[i]%NN;
		Map1[i*3][index].remove(k);
		index =(a*sum[i] + b)%NN;
		Map1[i*3+1][index].remove(k);
		int index = ((int)(4096*((sum[i]*0.6180339887 - (int)(sum[i]*0.6180339887)))))%NN;
		Map1[i*3+2][index].remove(k);
	}
	return;
}

template <typename K, typename V>
void Number_Map<K,V>::printMap(){
	cout << "NUMBER MAP" << endl;
	cout << "\t\t\t" << "Division\t" << "MAD\t\t" << "Multiplication\t" << endl; 
	for( int i=0 ; i<4 ; i++){
		if(i==0)cout << "Component Sum \t\t";
		if(i==1)cout << "Polynomial Sum\t\t" ;
		if(i==2)cout << "Cyclic Sum\t\t" ;
		if(i==3)cout << "Integer casting\t\t" ;
		cout << 100.0*collisions[i*3]/noe << "%\t" << 100.0*collisions[i*3+1]/noe << "%\t" << 100.0*collisions[i*3+2]/noe << "%" <<endl;
	}
	cout << endl;
	
	ofstream myfile;
  	myfile.open ("2016csb1050_output.txt");
  	myfile << "NUMBER MAP" << endl;
	myfile << setw(28) << "Division" << setw(12) << "MAD" << "\t\t";
	myfile << setw(8) << "Multiplication" << endl; 
	for( int i=0 ; i<4 ; i++){
		if(i==0)myfile << "Component Sum \t\t";
		if(i==1)myfile << "Polynomial Sum\t\t" ;
		if(i==2)myfile << "Cyclic Sum\t\t\t" ;
		if(i==3)myfile << "Integer casting\t\t" ;
		myfile << 100.0*collisions[i*3]/noe << "%" << setw(15) << 100.0*collisions[i*3+1]/noe << "%" << setw(15) << 100.0*collisions[i*3+2]/noe << "%" <<endl;
	}
	myfile << endl;
}

#endif
