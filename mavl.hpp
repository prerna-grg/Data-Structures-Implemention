#ifndef _MAVL_H
#define _MAVL_H
#include <iostream>
using namespace std;

class node{
	int roll_no;
	string name;
	node* left;
	node* right;
	node* parent;
	node* self;
	int height;
	int place;
	public:
	node();
	node(int h , string k);
	bool isLeft();
	friend class MAVLTree;
};

class MAVLTree{
	node* root;
	node* root_t2;
	int treesize;
	public:
    MAVLTree();  //Initialize the ADT	
    int size() const;	// number of elements
    bool isEmpty() const;	// is the tree empty?
	node* insert_t2( const int k, string s);
	void insert(const int k , string s);//insert key k,s into the tree
  	void remove(const int k);//remove k from the tree, if exists
   	string search(const int k);//search for key k in the tree
   	node* leftRotate(node*);
   	node* rightRotate(node*);
   	void balance(node*);
   	void remove_t2(node*);
	void delete_by_place(int i); //Delete from the entry at the  ith place (as determined by the order of insertion)
    int get_place(int k);//Return the place (which is determined by the order of insertion), if x does not exist, return -1 
    void print(node*);
    int check_case(node*,node*);
};

node::node(){
	roll_no = 0;
	name = "";
	left=NULL;
	right = NULL;
	parent = NULL;
	self = NULL;
	height = 0;
	place = 0;
}

node::node(int n , string k){
	roll_no = n;
	name = k;
	left=NULL;
	right = NULL;
	parent = NULL;
	self = NULL;
	height = 0;
	place = 0;
}

bool node::isLeft(){
	if( parent==NULL)return false;
	if( parent->left == this) return true;
	return false;
}

MAVLTree::MAVLTree(){
	root=NULL;
	treesize=0;
	root_t2=NULL;
}

int MAVLTree::size() const{return treesize;}

bool MAVLTree::isEmpty() const{return treesize==0;}

node* MAVLTree::insert_t2(const int k , string s){
	node* newnode = new node;
	newnode->roll_no = k;
	newnode->name = s;
	newnode->height = 0;
	newnode->place = 1;
	if(root_t2==NULL){ root_t2=newnode;return newnode;}
	node* temp= root_t2;
	node* temp_p = root_t2;
	int lr=0;
	while(temp->right!=NULL){
		temp->place++;
		temp = temp->right;
	}
	temp->place++;
	temp->right = newnode;
	newnode->parent = temp;
	node* temp2 = newnode;
	int h=1;
	while(temp2->parent!=NULL){
		if(temp2->parent->height >= h) break;
		else {
			temp2->parent->height = h;
			temp2 = temp2->parent;
			h++;
		}
	}
	node* x = newnode;
	node* y = x->parent;
	if(y==NULL){return newnode;}
	node* z = y->parent;
	if(z==NULL)return newnode;
	while(z!=NULL){
		if(z->left==NULL && z->right==NULL)return newnode;
		else if(z->left!=NULL && z->right==NULL){
			if( z->left->height <= 0 ) {
				z = z->parent;
				y = y->parent;
				x = x->parent;
				continue;
			}else break;
		}
		else if(z->left==NULL && z->right!=NULL){
			if( z->right->height <= 0 ) {
				z = z->parent;
				y = y->parent;
				x = x->parent;
				continue;
			}else break;
		}
		else{
			if( (z->left->height - z->right->height) <=1 && (z->left->height - z->right->height) >=-1  ){
				z = z->parent;
				y = y->parent;
				x = x->parent;
				continue;
			}else break;
		}
	}
	if(z==NULL) return newnode;
	//z->height = z->height -2 ;
	if( z->left!=NULL && y->left!=NULL) z->place = z->left->place + y->left->place+1;
	else if( z->left!=NULL && y->left==NULL) z->place = z->left->place + 1;
	else if( z->left==NULL && y->left !=NULL) z->place = y->left->place+1;
	else z->place = 1;
	y->place = z->place + x->place+1;
	if( z->parent == NULL){
		root_t2 = leftRotate(z);
		balance(z);
		return newnode;
	}else{
		node* t = z->parent;
		if(z->isLeft()){
			t->left = leftRotate(z);
			t->left->parent = t;
			balance(z);
		}else{
			t->right = leftRotate(z);
			t->right->parent = t;
			balance(z);
		}
		return newnode;
	}
	return newnode;
}

void MAVLTree::insert(const int k, string s){

	node* sibling = insert_t2(k,s);
	node* newnode = new node;
	newnode->roll_no = k;
	newnode->name = s;
	newnode->height = 0;
	newnode->self = sibling;
	sibling->self = newnode;
	newnode->place = -1;
	if(root==NULL){ root=newnode;treesize++;return;}
	node* temp=root;
	node* temp_p = root;
	int lr=0;
	while(temp!=NULL){
		temp_p = temp;
		if( k < temp->roll_no){
			temp = temp->left;
			lr=0;
		}
		else{
			temp = temp->right;
			lr=1;
		}
	}
	temp = newnode;
	temp->parent = temp_p;
	if(lr==0)temp_p->left = temp;
	else temp_p->right = temp;
	node* temp2 = newnode;
	balance(temp2);
	treesize++;
	node* x = newnode;
	node* y = newnode->parent;
	if(y==NULL)return;
	node* z = y->parent;
	if(z==NULL)return;
	while(z!=NULL){
		if(z->left==NULL && z->right==NULL)return;
		else if(z->left!=NULL && z->right==NULL){
			if( z->left->height <= 0 ) {
				z = z->parent;
				y = y->parent;
				x = x->parent;
				continue;
			}else break;
		}
		else if(z->left==NULL && z->right!=NULL){
			if( z->right->height <= 0 ) {
				z = z->parent;
				y = y->parent;
				x = x->parent;
				continue;
			}else break;
		}
		else{
			if( (z->left->height - z->right->height) <=1 && (z->left->height - z->right->height) >=-1  ){
				z = z->parent;
				y = y->parent;
				x = x->parent;
				continue;
			}else break;
		}
	}
	if(z==NULL)return;
	int o=check_case(y,x);
	if(o==2) {
		z->left = leftRotate(y);
		z->left->parent = z;
		balance(z->left->left);
	}
	else if(o==4) {
		z->right = rightRotate(y);
		z->right->parent = z;
		balance(z->right->right);
	}
	if(o==1 || o==2){
		if( z->parent==NULL){
			root = rightRotate(z);
			balance(z);
			return;
		}else{
			node* t = z->parent;
			if(z->isLeft()){
				t->left = rightRotate(z);
				t->left->parent = t;
				balance(z);
			}else{
				node* t = z->parent;
				t->right = rightRotate(z);
				t->right->parent = t;
				balance(z);
			}
			return;
		}
	}
	else if(o==3 || o==4){
		if( z->parent == NULL){
			root = leftRotate(z);
			balance(z);
			return;
		}else{
			node* t = z->parent;
			if(z->isLeft()){
				t->left = leftRotate(z);
				t->left->parent = t;
				balance(z);
			}else{
				t->right = leftRotate(z);
				t->right->parent = t;
				balance(z);
			}
			return;
		}
	}
	return;
}

void MAVLTree::remove(const int k){
	node* temp = root;
	while(temp!=NULL){
		if ( k==temp->roll_no) break;
		else if ( k<temp->roll_no) temp=temp->left;
		else temp=temp->right;
	}
	if( temp==NULL ){
		cout << "NOT FOUND" << endl;
		return ;
	}
	if(temp==root && treesize==1){
		root = NULL;
		node* temp2 = root_t2;
		root_t2=NULL;
		delete(temp);
		delete(temp2);
		treesize = 0;
		return;
	}
	remove_t2(temp->self);
	node* z = temp->parent;
	if( temp->left==NULL && temp->right==NULL) { 
		if(temp->parent !=NULL ){
			if(temp->isLeft()) temp->parent->left  = NULL;
			else temp->parent->right = NULL;
		}
		delete temp;	
	}
	else if( temp->left==NULL && temp->right!=NULL) {
		if(temp->isLeft()){
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
		}else{
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
		}
		delete temp;
	}
	else if( temp->left!=NULL && temp->right==NULL ){
		if( temp->isLeft() ){
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
		}else{
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		}
		delete temp;
	}else{
		node* temp1 = temp->right;
		while(temp1->left !=NULL)temp1 = temp1->left;
		temp->roll_no = temp1->roll_no;
		temp->name = temp1->name;
		temp1->self->self = temp;
		temp->self = temp1->self;
		z = temp1->parent;
		if( temp1->left == NULL && temp1->right == NULL){
			if( temp1->isLeft()) temp1->parent->left = NULL;
			else temp1->parent->right = NULL;
		}
		else{
			if( temp1->isLeft()){
				
				temp1->parent->left = temp1->right;
				temp1->right->parent = temp1->parent;
			}else{
				z->right = temp1->right;
				z->right->parent = z;
			}
		}
		delete temp1 ;
	}
	treesize--;
	balance(z);
	while( z!=NULL){
		node* r = z->parent;
		while( z!=NULL ){
			if( z->left==NULL && z->right ==NULL ){
				z = z->parent;
			}
			else if( z->left!=NULL && z->right == NULL){
				if(z->left->height ==0 ) z = z->parent;
				else break;
			}
			else if( z->left==NULL && z->right != NULL){
				if(z->right->height ==0 ) z = z->parent;
				else break;
			}
			else{
				if( (z->left->height - z->right->height) <=1 && (z->left->height - z->right->height) >=-1 )z = z->parent;
				else break;
			}
		}
		if( z==NULL)return;
		node* y;
		node* x;
		
		if( z->left==NULL && z->right==NULL)return;
		else if( z->left==NULL && z->right!=NULL) y = z->right;
		else if( z->left!=NULL && z->right==NULL) y = z->left;
		else{
			int h1 = z->left->height;
			int h2 = z->right->height;
			if( h1>h2) y=z->left;
			else y=z->right;
		}
		if( y->left==NULL && y->right==NULL)return;
		else if( y->left==NULL && y->right!=NULL) x = y->right;
		else if( y->left!=NULL && y->right==NULL) x = y->left;
		else{
			int h1 = y->left->height;
			int h2 = y->right->height;
			if( h1>h2) x=y->left;
			else if( h1==h2){
				if( y->isLeft())x = y->left;
				else x = y->right;
			}
			else x=y->right;
		}
		int o=check_case(y,x);
		if(o==2) {
			z->left = leftRotate(y);
			z->left->parent = z;
			balance(z->left->left);
		}
		else if(o==4) {
			z->right = rightRotate(y);
			z->right->parent = z;
			balance(z->right->right);
		}
		if(o==1 || o==2){
			if( z->parent==NULL){
				root = rightRotate(z);
				balance(root);
				z = r;
				continue;
			}else{
				node* t = z->parent;
				if(z->isLeft()){
					t->left = rightRotate(z);
					t->left->parent = t;
					balance(z);
				}else{
					t->right = rightRotate(z);
					t->right->parent = t;
					balance(z);
				}
				z = r;
				continue;
			}
		}
		else if(o==3 || o==4){
			if( z->parent == NULL){
				root = leftRotate(z);
				balance(root);
				z = r;
				continue;
			}
			else{
				node* t = z->parent;
				if(z->isLeft()){
					t->left = leftRotate(z);
					t->left->parent = t;
					balance(z);
				}else{
					t->right = leftRotate(z);
					t->right->parent = t;
					balance(z);
				}
				z = r;
				continue;
			}
		}
	}
	return;
}

void MAVLTree::remove_t2(node* temp){
	node* z = temp->parent;
	node* update;
	if( temp->left==NULL && temp->right==NULL) { 
		if(temp->parent !=NULL ){
			if(temp->isLeft()) temp->parent->left  = NULL;
			else temp->parent->right = NULL;
		}
		update = temp->parent;
		while( update!=NULL){
			update->place--;
			update = update->parent;
		}
		delete temp;
	}
	else if( temp->left==NULL && temp->right!=NULL) {
		
		if(temp->isLeft()){
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
		}else{
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
		}
		update = temp->parent;
		while( update!=NULL){
			update->place--;
			update = update->parent;
		}
		delete temp;
	}
	else if( temp->left!=NULL && temp->right==NULL ){
		
		if( temp->isLeft() ){
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
		}else{
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		}
		update = temp->parent;
		while( update!=NULL){
			update->place--;
			update = update->parent;
		}
		delete temp;
	}else{
		node* temp1 = temp->right;
		while(temp1->left !=NULL)temp1 = temp1->left;
		temp->roll_no = temp1->roll_no;
		temp->name = temp1->name;
		temp1->self->self = temp;
		temp->self = temp1->self;
		z = temp1->parent;
		if( temp1->left == NULL && temp1->right == NULL){
			if(temp1->isLeft())temp1->parent->left = NULL;
			else temp1->parent->right=NULL;
		}
		else{
			if( temp1->isLeft()){
				temp1->parent->left = temp1->right;
				temp1->right->parent = temp1->parent;
			}else{
				temp1->parent->right = temp1->right;
				temp1->right->parent = temp1->parent;
			}
		}
		update = temp1->parent;
		while( update!=NULL){
			update->place--;
			update = update->parent;
		}
		delete temp1 ;
	}
	balance(z);
	while( z!=NULL){
		node* r = z->parent;
		while( z!=NULL ){
			if( z->left==NULL && z->right ==NULL ){
				z = z->parent;
			}
			else if( z->left!=NULL && z->right == NULL){
				if(z->left->height ==0 ) z = z->parent;
				else break;
			}
			else if( z->left==NULL && z->right != NULL){
				if(z->right->height ==0 ) z = z->parent;
				else break;
			}
			else{
				if( (z->left->height - z->right->height) <=1 && (z->left->height - z->right->height) >=-1 )z = z->parent;
				else break;
			}
		}
		if( z==NULL)return;
		node* y;
		node* x;
		
		if( z->left==NULL && z->right==NULL)return;
		else if( z->left==NULL && z->right!=NULL) y = z->right;
		else if( z->left!=NULL && z->right==NULL) y = z->left;
		else{
			int h1 = z->left->height;
			int h2 = z->right->height;
			if( h1>h2) y=z->left;
			else y=z->right;
		}
		if( y->left==NULL && y->right==NULL)return;
		else if( y->left==NULL && y->right!=NULL) x = y->right;
		else if( y->left!=NULL && y->right==NULL) x = y->left;
		else{
			int h1 = y->left->height;
			int h2 = y->right->height;
			if( h1>h2) x=y->left;
			else if( h1==h2){
				if( y->isLeft())x = y->left;
				else x = y->right;
			}
			else x=y->right;
		}
		int o= check_case(y,x);
		if(o==2) {
		
			if( y->left!=NULL && x->left!=NULL) y->place = y->left->place + x->left->place+1;
			else if( y->left!=NULL && x->left==NULL) y->place = y->left->place + 1;
			else if(y->left==NULL && x->left!=NULL) y->place = x->left->place + 1;
			else y->place = 1;
			if( x->right !=NULL) x->place = y->place + x->right->place + 1;
			else x->place = y->place + 1;
			z->left = leftRotate(y);
			z->left->parent = z;
			balance(z->left->left);
		}
		else if(o==4) {
			if( y->right!=NULL && x->right!=NULL) y->place = y->right->place + x->right->place+1;
			else if( y->right!=NULL && x->right==NULL) y->place = y->right->place + 1;
			else if(y->right==NULL && x->right!=NULL) y->place = x->right->place + 1;
			else y->place = 1;
			if( x->left !=NULL) x->place = y->place + x->left->place + 1;
			else x->place = y->place+1;
			z->right = rightRotate(y);
			z->right->parent = z;
			balance(z->right->right);
		}
		if(o==1 || o==2){
			if( z->right!=NULL && y->right!=NULL) z->place = z->right->place + y->right->place+1;
			else if( z->right!=NULL && y->right==NULL) z->place = z->right->place + 1;
			else if( z->right==NULL && y->right !=NULL) z->place = y->right->place+1;
			else z->place = 1;
			y->place = z->place + x->place+1;
			if( z->parent==NULL){
				root_t2 = rightRotate(z);
				balance(root_t2);
				return;
			}else{
				node* t = z->parent;
				if(z->isLeft()){
					t->left = rightRotate(z);
					t->left->parent = t;
					balance(z);
				}else{
					t->right = rightRotate(z);
					t->right->parent = t;
					balance(z);
				}
				z = r;
				continue;
			}
		}
		else if(o==3 || o==4){
		
			if( z->left!=NULL && y->left!=NULL) z->place = z->left->place + y->left->place+1;
			else if( z->left!=NULL && y->left==NULL) z->place = z->left->place + 1;
			else if( z->left==NULL && y->left !=NULL) z->place = y->left->place+1;
			else z->place = 1;
			y->place = z->place + x->place+1;
			if( z->parent == NULL){
				root_t2 = leftRotate(z);
				balance(root_t2);
				return;
			}
			else{
				node* t = z->parent;
				if(z->isLeft()){
					t->left = leftRotate(z);
					t->left->parent = t;
					balance(z);
				}else{
					t->right = leftRotate(z);
					t->right->parent = t;
					balance(z);
				}
				z = r;
				continue;
			}
		}
	}
	return;
}

string MAVLTree::search(const int k){
	node* temp = root;
	while(temp!=NULL){
		if ( k==temp->roll_no) return temp->name;
		else if ( k<temp->roll_no) temp=temp->left;
		else temp=temp->right;
	}
	if( temp==NULL ){
		cout << "NOT FOUND" << endl;
		return "" ;
	}
}

void MAVLTree::delete_by_place(int i){
	int z=0;
	node* temp = root_t2;
	if( temp->place < i) return;
	while( temp!=NULL){
		if( temp->left==NULL) z=0;
		else z = temp->left->place;
		if( i<=z)temp=temp->left;
		else if( i==z+1){
			remove(temp->roll_no);
			break;
		}
		else{
			i = i-z-1;
			temp = temp->right;
		}
	
	}	
}

int MAVLTree::get_place(int k){
	node* temp2 = root;
	while(temp2!=NULL){
		if ( k==temp2->roll_no) break ;
		else if ( k<temp2->roll_no) temp2=temp2->left;
		else temp2=temp2->right;
	}
	if( temp2==NULL )return -1;
	node* temp = temp2->self;
	int plac=1;
	if( temp->left !=NULL) plac = plac + temp->left->place;
	while( temp->parent !=NULL){
		if( !temp->isLeft()){
			if( temp->parent->left !=NULL)plac = plac + 1 + temp->parent->left->place;
			else plac = plac +1;
		}
		temp = temp->parent;
	}
	return plac;
}

node* MAVLTree::rightRotate(node* e){
	node* temp = e->left;
	e->left = e->left->right;
	if(e->left!=NULL)e->left->parent=e;
	temp->right = e;
	e->parent= temp;
	temp->parent = NULL;
	return temp;
}

node* MAVLTree::leftRotate(node* e){
	node* temp = e->right;
	e->right = e->right->left;
	if(e->right!=NULL)e->right->parent = e;
	temp->left = e;
	e->parent= temp;
	temp->parent = NULL;
	return temp;
}

void MAVLTree::balance(node* e){
	while( e!=NULL){
		if( e->left == NULL && e->right==NULL) e->height=0;
		else if( e->left != NULL && e->right==NULL) e->height= e->left->height + 1;
		else if( e->left == NULL && e->right!=NULL) e->height= e->right->height + 1;
		else{
			int h1= e->left->height;
			int h2= e->right->height;
			e->height = max(h1,h2) +1;
		}
		e = e->parent;
	}
}

int MAVLTree::check_case(node* y , node* x){
	int o=0;
	if( y->isLeft() && x->isLeft() ) o=1; //Left Left
	else if( y->isLeft() && !x->isLeft() ) o=2; // Left Right
	else if( !y->isLeft() && !x->isLeft() ) o=3; // Right Right
	else if( !y->isLeft() && x->isLeft() ) o=4; //Right Left
	return o;
}
void MAVLTree::print(node* e){
	if(e==NULL)return;
	print(e->left);
	print(e->right);
}
#endif
