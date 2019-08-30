

#include "room.h"



void Room::check_name(vector<Room> rooms,string roomname){
	for(int i=0;i<rooms.size();i++){
		if(check_strings(roomname,rooms[i].pass_name())){
			throw "Room Name Has Been Used Before!";
		}
	}
}

void Room::print_roles(vector<string>& allnames){
	if(allpeople>allcharacter){
		throw "many users";
	}
	else if(allpeople==allcharacter){
		int n=0;
		n=rand() % allnames.size();
		for(int i=0;i<allpeople;i++){
			roles[i]->Set_Name(allnames[n]);
			cout<<allnames[n]<<" is "<<roles[i]->pass_role_type()<<endl;
			n++;
			if(n==allnames.size())
				n=0;
		}
		night=false;
		day=true;
		cout<<"Day "<<numday<<endl;
	}
}

void Room::set_roles(string role,int c){
	for(int i=roles.size()-c;i<roles.size();i++){
		if(check_strings(role,"Detective"))
			roles[i]->set_role("Detective");
		else if(check_strings(role,"Doctor"))
			roles[i]->set_role("Doctor");
		else if(check_strings(role,"RouinTan")){
			roles[i]->set_role("Rouintan");
			roles[i]->get_rouintan();
		}
		else if(check_strings(role,"Silencer"))
			roles[i]->set_role("Silencer");
		else if(check_strings(role,"GodFather"))
			roles[i]->set_role("GodFather");
	}
}

void Room::decrease_roles_num(Roles* role){
	if(check_strings(role->pass_role_type(),"Mafia")||check_strings(role->pass_role_type(),"Silencer")||
		check_strings(role->pass_role_type(),"GodFather"))
		mafianum--;
	else
		villagernum--;	
}

void Room::check_existance(string name1,string name2){
	bool name1_repeated=false,name2_repeated=false;
	for(int i=0;i<roles.size();i++){
		if(check_strings(roles[i]->pass_name(),name1)){
			name1_repeated=true;
		}

		if(check_strings(roles[i]->pass_name(),name2)){
			name2_repeated=true;
		}
	}
	if(!name1_repeated || !name2_repeated)
		throw "User not joined";
}

void Room::mafia_vote(string votee,string voter,int& maxvoted){
	bool voted=true;
	for(int i=0;i<roles.size();i++){
		if(check_strings(roles[i]->pass_name(),voter) && !roles[i]->voted()){
			if(!roles[i]->isdead()){
				if(check_strings(roles[i]->pass_role_type(),"Mafia")||check_strings(roles[i]->pass_role_type(),"Silencer")||
					check_strings(roles[i]->pass_role_type(),"GodFather")){
					roles[i]->get_voted();
					maxvoted++;
					voted=false;
					if(check_strings(roles[i]->pass_role_type(),"Mafia"))
						roles[i]->check_the_roles();
				}
				else
					throw "This user can not vote";
			}
			else{
				throw "User already dead";
			}
		}
		if(check_strings(roles[i]->pass_name(),votee)){
			if(!roles[i]->isdead()){
				roles[i]->raise_getvoted();
			}
			else{
				throw "User already dead";
			}
		}
	}
	if(voted)
		throw "User already voted";
}

void Room::end_of_day(){
	bool end=true;
	for(int i=0;i<roles.size();i++){
		if(!check_strings(roles[i]->pass_role_type(),"Villager")&&!check_strings(roles[i]->pass_role_type(),"GodFather")&&
			!check_strings(roles[i]->pass_role_type(),"RouinTan")&&!check_strings(roles[i]->pass_role_type(),"Joker")){
			if(!roles[i]->is_role_checked())
				end=false;
		}
	}
	if(end){
		cout<<"Day "<<numday<<endl;
		numnight++;
		day=true;
		night=false;
		bool heal=false;
		for(int i=0;i<healed_by_doctor.size();i++){
			if(dead_by_mafia==healed_by_doctor[i]){
				roles[dead_by_mafia]->reset_healed();
				heal=true;
				break;
			}
		}
		if(!heal){
			if(!check_strings(roles[dead_by_mafia]->pass_role_type(),"RouinTan")&&!roles[dead_by_mafia]->is_rouintan()){
				roles[dead_by_mafia]->set_dead();
				decrease_roles_num(roles[dead_by_mafia]);
				cout<<"Killed "<<roles[dead_by_mafia]->pass_name()<<endl;
			}
			else{
				roles[dead_by_mafia]->reset_rouintan();
			}
		}
		for(int i=0;i<roles.size();i++){
			if(roles[i]->is_silenced())
				cout<<"Silenced "<<roles[i]->pass_name()<<endl;
		}

	}
}

void Room::end_of_game(){
	if(mafianum>=villagernum){
		cout<<"Loose!"<<endl;
		for(int i=0;i<roles.size();i++){
			delete roles[i];
		}
		cout<<"In room "<<roomname<<" ";
		throw "game over!";
	}
	else if(mafianum==0){
		cout<<"Victory!"<<endl;
		for(int i=0;i<roles.size();i++){
			delete roles[i];
		}
		cout<<"In room "<<roomname<<" ";
		throw "game over!";
	}
}

