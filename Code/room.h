#ifndef ROOM_H_
#define ROOM_H_

#include "roles.h"

class Room{
public:
	~Room(){}
	string pass_name(){return roomname;}
	template <class T>
	void check_roles(T roletype,int count);
	void get_room_name(string name){roomname=name;}
	void check_name(vector<Room> rooms,string roomname);
	string pass_room_name(){return roomname;}
	void add_people_num(int n){allpeople+=n;}
	void add_charater_num(int n){allcharacter+=n;}
	void print_roles(vector<string>& allnames);
	void set_roles(string role,int c);
	int pass_mafia_number(){return mafianum;}
	int pass_villager_number(){return villagernum;}
	void decrease_roles_num(Roles* role);
	void check_existance(string detective_name,string suspect_name);
	void mafia_vote(string votee,string voter,int& maxvoted);
	void end_of_day();
	void end_of_game();

	vector<Roles*> roles;
	bool night=false;
	bool day=false;
	int numday=1;
	int numnight=1;
	int dead_by_mafia=0;
	vector<int> healed_by_doctor;
private:
	int allpeople=0;
	int allcharacter=0;
	string roomname;
	int mafianum=0;
	int villagernum=0;
};
template <class T>
void Room::check_roles(T roletype,int count){
	bool repeated=false;
	int c=0;
	if(count<0){
		throw "Invalid Role Number!";
	}

	for(int i=0;i<roles.size();i++){
		if(roles[i]->pass_role_type()==roletype.pass_role_type()){
			// roles.erase(roles.begin()+i-1);
			// i--;
			repeated=true;
			c++;
		}
	}
	if(!repeated){
		for(int i=0;i<count;i++)
			roles.push_back(new T());
	}
	else if(repeated){
		if(count<c){
			// int x=0;
			// for(int i=roles.size();i>-1;i--){
			// 	if(check_strings(roles[i]->pass_role_type(),roletype.pass_role_type()) && c!=x){
			// 		roles.erase(roles.begin()+i);
			// 		x++;
			// 	}

			// }
		}
		if(count>c){
			for(int j=0;j<count-c;j++){
				roles.push_back(new T());
			}
		}
	}

	if(check_strings(roletype.pass_role_type(),"Mafia")||check_strings(roletype.pass_role_type(),"Silencer")||
		check_strings(roletype.pass_role_type(),"GodFather"))
		mafianum+=count-c;
	else
		villagernum+=count-c;
	// cout<<mafianum<<endl<<villagernum<<endl<<endl;
}


#endif