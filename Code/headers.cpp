
#include "headers.h"

int cToi(char n){
	int x;
	switch(n){
		case '0':
			x=0;
			break;
		case '1':
			x=1;
			break;
		case '2':
			x=2;
			break;
		case '3':
			x=3;
			break;
		case '4':
			x=4;
			break;
		case '5':
			x=5;
			break;
		case '6':
			x=6;
			break;
		case '7':
			x=7;
			break;
		case '8':
			x=8;
			break;
		case '9':
			x=9;
			break;
	}
	return x;
}

int sToi(string name){
	int n=0;
	for(int i=0;i<name.size();i++){
		n+=cToi(name[i]);
		n*=10;
	}
	n=n/10;
	return n;
}

bool check_strings(string fname,string sname){
	if(fname.size()==sname.size()){
		for(int i=0;i<fname.size();i++){
			if(fname[i]!=sname[i])
				return false;
		}
		return true;
	}
	else
		return false;
}

