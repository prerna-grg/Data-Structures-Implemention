#include <iostream>
#include <string>
#include "number_map.hpp"
#include "name_map.hpp"
#include <cmath>
#include <fstream>

typedef long long int ll;
using namespace std;
int main(){
	
	Number_Map <ll,int> NU(743);
	ifstream inp;
	inp.open("numbers.txt");
	ll phone;
	int blnc;
	while(inp>>phone>>blnc){
		NU.put(phone,blnc);
	}
	inp.close();

	NU.printMap();
	cout << endl;
	
	Name_Map <string,string> NA(2531);
	ifstream inp1;
	inp1.open("names.txt");
	string token,meaning;
	while(inp1>>token){
		getline(inp1,meaning);
		NA.put(token,meaning);
	}
	inp1.close();

	NA.printMap();
	cout << endl;
	
	char c = 'y';
	while( c=='y' || c=='Y'){
		int h;
		cout << "Please​ ​ enter​ ​ 1 ​ ​ to​ ​ know​ ​ balance​ ​ of​ ​ a ​ ​ phone​ ​ number​ ​ and​ ​ 2 ​ ​ to​ ​ know​ ​ meaning​ ​ of​ ​ a ​ ​ name " ;
		cin >> h ;
		if( h==1){
			ll number ;
			cout << "Please​ ​ enter​ ​ number " ;
			cin >> number;
			while(cin.fail()){
				cout << "PLease enter integer input" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> number ;
			}
			int k = NU.find(number);
			cout << "Number= " << number << "," << " Balance= " << k << endl;
		}
		else if( h==2){
			string word ;
			cout << "Please​ ​ enter​ ​ name " ;
			cin >> word;
			string s = NA.find(word);
			cout << "Name= " << word << "," << " Meaning= " << s << endl;
		}
		else{
			cout << "Please enter a valid number!!" << endl;
		}
		
		cout << "Do u want to continue ?y/n " ;
		cin >> c;
	}
}
