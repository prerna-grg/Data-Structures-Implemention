#include <iostream>
#include "mavl.hpp"
#include <fstream>
using namespace std;
int main(){
	
	MAVLTree m;
	ifstream file;
	file.open("entries.txt");
	if( !file){
		cout << "Error opening file" << endl;
		return -1;
	}
	int roll_no;
	string name;
	while(file >> roll_no >> name){
		m.insert(roll_no,name);
	}
	file.close();

	char y = 'y';
	while( y=='y' || y=='Y'){
		int h;
		cout << "Please enter 1 to insert" << endl;
		cout << "Please enter 2 to delete by key" << endl;
		cout << "Please enter 3 to get place of a key" << endl;
		cout << "Please enter 4 to delete by place of a key" << endl;
		cout << "Please enter 5 to search for a key" << endl;
		cout << "Please enter 6 to find size of tree" << endl;
		cout << "Please enter 7 to check if tree is empty" << endl;
		cin >> h;
		if( h==1){
			cout << "Please enter the roll number and name of your entry" << endl;
			cout << "Roll No : " ;
			cin >> roll_no ;
			while(cin.fail()){
				cout << "PLease enter integer input" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> roll_no ;
			}
			cout << "Name : " ;
			cin >> name;
			m.insert(roll_no , name);
		}
		else if(h==2){
			int key;
			cout << "Please enter the key you want to delete : " ;
			cin >> key;
			while(cin.fail()){
				cout << "PLease enter integer input" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> key ;
			}
			m.remove(key);
			
		}
		else if(h==3){
			int k;
			cout << "Please note that places begin from 1" << endl;
			cout << "Please enter the key : " ;
			cin >> k;
			while(cin.fail()){
				cout << "PLease enter integer input" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> k ;
			}
			cout << m.get_place(k) << endl;
		}
		else if(h==4){
			int place;
			cout << "Please note that places begin from 1" << endl;
			cout << "Please enter the place : " ;
			cin >> place;
			while(cin.fail()){
				cout << "PLease enter integer input" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> place ;
			}
			m.delete_by_place(place);
		}
		else if(h==5){
			int se;
			cout << "Please enter the  key : " ;
			cin >> se;
			while(cin.fail()){
				cout << "PLease enter integer input" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> se ;
			}
			cout << m.search(se) << endl;
		}
		else if(h==6){
			cout << "Tree size= " << m.size() << endl;
		}
		else if(h==7){
			if(m.isEmpty()) cout << "The tree is empty." << endl;
			else cout << "The tree is not empty , it has " << m.size() << " nodes." << endl;
		}
		else{
			cout << "Please enter correct input !!" << endl;
		}
		cout << "Would you like to continue? y/n " ;
		cin >> y;
		cout << endl;
	}
}
