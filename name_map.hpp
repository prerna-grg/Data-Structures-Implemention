#ifndef _map_h
#define _map_h

#define N 2531
#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

template <typename K , typename V>
class Node {
		K name ;
		V mean ;
		Node<K,V>* next ;
	public:
		Node();
		Node(K k, V v);
	template <typename Kk , typename Vv> friend class Linkedlist ;
	
};

template <typename K , typename V>
class Linkedlist {
		Node<K,V> *head ;
		int size;
	public:
		void insert(K n , V m);
		void remove(K);
		void print();
		V check( K k);
		Linkedlist();
		~Linkedlist();
	template <typename Kk , typename Vv> friend class Name_Map ;
		
};

//NODE DEFAULT CONSTRUCTOR
template <typename K , typename V>
Node<K,V>::Node(){
	next = NULL ;
};

//NODE GENERIC CONSTRUCTOR
template <typename K , typename V>
Node<K,V>::Node(K k, V v){
	name = k;
	mean = v;
	next = NULL ;
};

//LINKEDLIST CONSTRUCTOR
template <typename K , typename V>
Linkedlist<K,V>::Linkedlist(){
    head = NULL;
    size = 0;
}

//LINKEDLIST DESTRUCTOR
template <typename K , typename V>
Linkedlist<K,V>::~Linkedlist(){

	while(head!=NULL){
		Node<K,V>*temp = head->next ;
		delete head ;
		head = temp ;
	}
	head==NULL;
}

//ADD FUNCTION FOR NODES
template <typename K , typename V>
void Linkedlist<K,V>::insert(K n , V m){
	Node<K,V>* newnode = new Node<K,V>(n,m);
	Node<K,V>* temp = head;
	if(temp==NULL){
		head = newnode ;
		size++;
		return ;
	}
	while( temp->next!=NULL){	
		if( temp->name == n){
			temp->mean = m;
			return;
		}else temp = temp->next;
	}
	if( temp->name == n) {
		temp->mean = m;
		return;
	}else{
		temp->next = newnode;
		newnode->next=NULL;
		size++;
	}
	return;
}

template <typename K , typename V>
V Linkedlist<K,V>::check(K k){
	Node<K,V>* temp = head;
	while(temp!=NULL){
		if(temp->name == k )return temp->mean;
		else temp = temp->next;
	}
	return " Not found" ;
}

//REMOVES NODE FROM THE LINKED LIST
template <typename K , typename V>
void Linkedlist<K,V>::remove( K k){
	
	Node<K,V>*temp = head ;
	Node<K,V>*temp_p = head ;
	if(temp==NULL)return;
	if(temp->next==NULL){
		if(temp->name == k){
			head = NULL;
			size--;
			delete(temp);
		}
		else cout << "Error: Not found" << endl;
		return;
	}
	if( temp->name == k){
		head = temp->next;
		size--;
		delete(temp);
		return;
	}
	while(temp!=NULL){
		if(temp->name == k){
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
class Name_Map {	// map interface
	Linkedlist<K,V> Map[12][N];
	int collisions[12];
	int noe;
	public:
		Name_Map();
		Name_Map(int capacity);	// constructor
		int size() const;				// number of entries in the map
		bool empty() const;				// is the map empty?
		V find( const K& k) ;	// find entry with key k
		void put( const K& k, const V& v);	// insert/replace pair (k,v)
		void erase( const K& k);		// remove entry with key k
		void printMap();
		void hash_fun(int i , unsigned int sum , K k , V v);
		unsigned int int_cast(const char* , int);
		unsigned int comp_sum(const char* , int);
		unsigned int poly_sum(const char* , int);
		unsigned int cyc_sum(const char* , int);
};

template <typename K, typename V>
Name_Map<K,V>::Name_Map(){noe=0;for(int i=0 ; i<12 ; i++)collisions[i]=0;}

template <typename K, typename V>
Name_Map<K,V>::Name_Map(int capacity){noe=0;for(int i=0 ; i<12 ; i++)collisions[i]=0;}

template <typename K, typename V>
int Name_Map<K,V>::size() const{return noe;}

template <typename K, typename V>
bool Name_Map<K,V>::empty() const{return noe==0;}

template <typename K, typename V>
void Name_Map<K,V>::put( const K& k , const V& v){
	noe++;
	if (typeid(K)==typeid(string)){
		const char* temps = k.c_str();
		int length = k.length();
		unsigned int sum=0;
		/************************************COMPONENT SUM*****************************************/
		sum = comp_sum(temps,length);
		hash_fun(0,sum,k,v);
		/***********************************POLYNOMIAL SUM********************************************/
		sum = poly_sum(temps,length);
		hash_fun(1,sum,k,v);
		/***************************************CYCLIC SUM***********************************************/
		sum = cyc_sum(temps,length);
		hash_fun(2,sum,k,v);
		/****************************************INTEGER CASTING******************************************/
		sum = int_cast(temps,length);
		hash_fun(3,sum,k,v);
	}
}

template <typename K, typename V>
unsigned int Name_Map<K,V>::int_cast(const char* temps , int l){
	unsigned int sum=0;
	int i=0;
	while( i+3<l ){
		int temp = 0;
		int p1 = temps[i];
		i++;
		int p2 = temps[i];
		i++;
		int p3 = temps[i];
		i++;
		int p4 = temps[i++];
		i++;
		temp = ( p1 | p2<<8 | p3 <<16 | p4<<24 )& 0x7FFFFFFF ;
		sum = sum + temp ;
	}
	int k = l-i;
	int p;
	for( int j = 0 ; j<k ; j++){
		int p1 = temps[j+k];
		int shift = 8*j;
		p1 = p1<<shift ;
		p = p | p1;
	}
	sum = sum + p;
	return (unsigned)sum;
}

template <typename K, typename V>
unsigned int Name_Map<K,V>::comp_sum(const char* temps , int l){
	unsigned int sum=0;
	for(int i=0 ; i<l ; i++){
		int p = temps[i];
		sum = sum +p ;
	}
	return (unsigned)sum;
}

template <typename K, typename V>
unsigned int Name_Map<K,V>::poly_sum(const char* temps , int l){
	int a=33;
	unsigned int sum = 0;
	for( int i=0 ; i<l ; i++){
		int p = temps[i];
		sum = sum*a + p ;
	}
	return (unsigned)sum;
}

template <typename K, typename V>
unsigned int Name_Map<K,V>::cyc_sum(const char* temps, int l){
	unsigned int sum = 0;
	for (int i = 0; i < l ; i++) {
		sum = (sum << 5) | (sum >> 27);
		sum = sum + ((unsigned int) temps[i]);
	}
	return (unsigned)sum;
}



template <typename K, typename V>
void Name_Map<K,V>::hash_fun(int i , unsigned int sum , K k , V v){




		if( (int)sum<0 ) sum = unsigned((int)sum*-1) ;
		int index = 0;
		index = sum%N;
		
		if( i==0 ) {
			if( Map[0][index].head!=NULL)collisions[0]++;
			Map[0][index].insert(k,v); // COMPONENET SUM AND DIVISION
		}
		if( i==1 ) {
			if( Map[3][index].head!=NULL)collisions[3]++;
			Map[3][index].insert(k,v); // POLUNOMIAL SUM AND DIVISION
		}
		if( i==2 ) {
			if( Map[6][index].head!=NULL)collisions[6]++;
			Map[6][index].insert(k,v); // CYCLIC SUM AND DIVISION
		}
		if( i==3 ) {
			if( Map[9][index].head!=NULL)collisions[9]++;
			Map[9][index].insert(k,v);  // INTEGER CASTING AND MAD
		}

		int a = 2539 , b = 2521;
		index = (( (a*sum)%N + b%N)%N)%N;
		if( i==0 ) {
			if( Map[1][index].head!=NULL)collisions[1]++;
			Map[1][index].insert(k,v); // COMPONENET SUM AND DIVISION
		}
		if( i==1 ) {
			if( Map[4][index].head!=NULL)collisions[4]++;
			Map[4][index].insert(k,v); // POLUNOMIAL SUM AND DIVISION
		}
		if( i==2 ) {
			if( Map[7][index].head!=NULL)collisions[7]++;
			Map[7][index].insert(k,v); // CYCLIC SUM AND DIVISION
		}
		if( i==3 ) {
			if( Map[10][index].head!=NULL)collisions[10]++;
			Map[10][index].insert(k,v);  // INTEGER CASTING AND MAD
		}
		
		index = ((int)(4096*((sum*0.6180339887 - (int)(sum*0.6180339887)))))%N ;
		if( i==0 ) {
			if( Map[2][index].head!=NULL)collisions[2]++;
			Map[2][index].insert(k,v); // COMPONENET SUM AND DIVISION
		}
		if( i==1 ) {
			if( Map[5][index].head!=NULL)collisions[5]++;
			Map[5][index].insert(k,v); // POLUNOMIAL SUM AND DIVISION
		}
		if( i==2 ) {
			if( Map[8][index].head!=NULL)collisions[8]++;
			Map[8][index].insert(k,v); // CYCLIC SUM AND DIVISION
		}
		if( i==3 ) {
			if( Map[11][index].head!=NULL)collisions[11]++;
			Map[11][index].insert(k,v);  // INTEGER CASTING AND MAD
		}
}

template <typename K, typename V>
V Name_Map<K,V>::find(const K& k) {

	int m = N;
	int a=2539 , b=2521;
	const char* temps = k.c_str();
	unsigned int sum = poly_sum(temps,k.length());
	if( (int)sum<0 ) sum = (int)sum*-1 ;
	int index =  (( (a*sum)%N + b%N)%N)%N;
	V s = Map[4][index].check(k);
	return s;
}

template <typename K, typename V>
void Name_Map<K,V>::erase(const K& k){
	const char* temps = k.c_str();
	int index = 0;
	unsigned int sum[4];
	int a = 2539;
	int b = 2521;
	sum[0] = comp_sum(temps,k.length());
	sum[1] = poly_sum(temps,k.length());
	sum[2] = cyc_sum(temps,k.length());
	sum[3] = int_cast(temps,k.length());
	for(int i=0 ; i<4 ; i++){
		if( (int)sum[i]<0 ) sum[i] = (int)sum[i]*-1 ;
		index = sum[i]%N;
		cout << i*3 << endl;
		Map[i*3][index].remove(k);
		index = (( (a*sum[i])%N + b%N)%N)%N;
		cout << i*3+1 << endl;
		Map[i*3+1][index].remove(k);
		int index = ((int)(4096*((sum[i]*0.6180339887 - (int)(sum[i]*0.6180339887)))))%N;
		cout << i*3+2 << endl;
		Map[i*3+2][index].remove(k);
	}
	return;
}

template <typename K, typename V>
void Name_Map<K,V>::printMap(){
	cout << "NAME MAP" << endl;
	cout << "\t\t\t" << "Division\t" << "MAD\t\t" << "Multiplication\t" << endl; 
	for( int i=0 ; i<4 ; i++){
		if(i==0)cout << "Component Sum \t\t";
		if(i==1)cout << "Polynomial Sum\t\t" ;
		if(i==2)cout << "Cyclic Sum\t\t" ;
		if(i==3)cout << "Integer casting\t\t" ;
		cout << 100.0*collisions[i*3]/noe << "%\t" << 100.0*collisions[i*3+1]/noe << "%\t" << 100.0*collisions[i*3+2]/noe << "%" << endl;
	}
	cout << endl;
	
	ofstream myfile;
  	myfile.open ("2016csb1050_output.txt" , fstream::in | fstream::out | fstream::app);
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
