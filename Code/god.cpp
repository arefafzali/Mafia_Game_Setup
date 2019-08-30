

#include "god.h"

void God::create_room(){
	string roomname;
	cin>>roomname;
	Room thisroom;
	thisroom.check_name(rooms,roomname);
	thisroom.get_room_name(roomname);
	string line;
	vector<instanceOfRoles> roles;
	getline(cin,line);
	line.erase(line.begin());
	string roletype;
	for(int i=0;i<line.size()+1;i++){
		if(line[i]!=' '&& i!=line.size()){
			roletype.push_back(line[i]);
		}
		else{
			instanceOfRoles instance;
			instance.name=roletype;
			string num;
			for(i++;line[i]!=' ' && i<line.size();i++){
				num.push_back(line[i]);
			}
			instance.count= sToi(num);
			roles.push_back(instance);
			thisroom.add_charater_num(instance.count);
			roletype.erase(roletype.begin(),roletype.end());
		}
	}
	for(int i=0;i<roles.size();i++){
		roles[i].name.erase(roles[i].name.begin());
		if(check_strings(roles[i].name,"Mafia")){
			Mafia mafia;
			thisroom.check_roles<Mafia>(mafia,roles[i].count);
		}
		else if(check_strings(roles[i].name,"Villager")){
			Villager villager;
			thisroom.check_roles(villager,roles[i].count);
		}
		else if(check_strings(roles[i].name,"Joker")){
			Joker joker;
			thisroom.check_roles(joker,roles[i].count);
			thisroom.set_roles("Joker",roles[i].count);
		}
		else if(check_strings(roles[i].name,"Detective")){
			Villager detective;
			thisroom.check_roles(detective,roles[i].count);
			thisroom.set_roles("Detective",roles[i].count);
		}
		else if(check_strings(roles[i].name,"Doctor")){
			Villager doctor;
			thisroom.check_roles(doctor,roles[i].count);
			thisroom.set_roles("Doctor",roles[i].count);
		}
		else if(check_strings(roles[i].name,"RouinTan")){
			Villager rouintan;
			thisroom.check_roles(rouintan,roles[i].count);
			thisroom.set_roles("RouinTan",roles[i].count);
		}
		else if(check_strings(roles[i].name,"Silencer")){
			Mafia silencer;
			thisroom.check_roles(silencer,roles[i].count);
			thisroom.set_roles("Silencer",roles[i].count);
		}
		else if(check_strings(roles[i].name,"GodFather")){
			Mafia godFather;
			thisroom.check_roles(godFather,roles[i].count);
			thisroom.set_roles("GodFather",roles[i].count);
		}
		else{
			throw "Invalid Role!";
		}
	}
	rooms.push_back(thisroom);
	room=rooms[rooms.size()-1];
}
void God::switch_room(){
	string line,roomname;
	bool hasname=false,hasroom=false;
	getline(cin,line);
	for(int i=0;i<line.size();i++){
		if(line[i]!=' '){
			hasname=true;
			roomname.push_back(line[i]);
		}
	}
	if(!hasname){
		throw "Invalid room name";
	}
	for(int i=0; i<rooms.size();i++){
		if(check_strings(roomname,rooms[i].pass_room_name())){
			room=rooms[i];
			hasroom=true;
		}
	}
	if(!hasroom){
		throw "Invalid room name";
	}
}
void God::join(){
	string line;
	getline(cin,line);
	string name;
	line.erase(line.begin());
	for(int i=0;i<line.size()+1;i++){
		if(line[i]!=' ' && i!=line.size()){
			name.push_back(line[i]);
		}
		else{
			allnames.push_back(name);
			name.erase(name.begin(),name.end());
			room.add_people_num(1);
		}
	}
	room.print_roles(allnames);
}
void God::vote(){
	
	string voter,votee;
	bool voter_repeated=false,votee_repeated=false,voted=true;
	cin>>voter>>votee;
	for(int i=0;i<room.roles.size();i++){
		if(check_strings(room.roles[i]->pass_name(),voter)){
			if(room.roles[i]->is_silenced()){
				room.roles[i]->reset_silenced();
				throw "This user has been silenced before";
			}
			voter_repeated=true;
		}

		if(check_strings(room.roles[i]->pass_name(),votee)){
			votee_repeated=true;
		}
	}
	if(!voter_repeated || !votee_repeated)
		throw "User not joined";

	for(int i=0;i<room.roles.size();i++){
		if(check_strings(room.roles[i]->pass_name(),voter) && !room.roles[i]->voted()){
			if(!room.roles[i]->isdead()){
				room.roles[i]->get_voted();
				voted=false;
			}
			else
				throw "User already dead";
		}
		if(check_strings(room.roles[i]->pass_name(),votee)){
			if(!room.roles[i]->isdead())
				room.roles[i]->raise_getvoted();
			else
				throw "User already dead";
		}
	}
	if(voted)
		throw "User already voted";
}
void God::end_vote(){
	maxvoted=0;
	int max=0;
	for(int i=0;i<room.roles.size();i++){
		if(room.roles[max]->getvoted()<room.roles[i]->getvoted())
			max=i;
	}
	for(int i=0;i<room.roles.size();i++){
		room.roles[i]->reset_getvoted();
		room.roles[i]->reset_voted();
	}
	if(check_strings(room.roles[max]->pass_role_type(),"Joker")){
		for(int i=0;i<room.roles.size();i++){
			delete room.roles[i];
		}
		throw "Do I look like a guy with a plan?";
	}
	else{
		room.roles[max]->set_dead();
		room.decrease_roles_num(room.roles[max]);
		cout<<"Died "<<room.roles[max]->pass_name()<<endl;
		room.day=false;
		room.night=true;
		room.numday++;
		cout<<"Night "<<room.numnight<<endl;
	}
}
void God::mafia_vote(){
	string voter,votee;
	cin>>voter>>votee;
	room.check_existance(voter,votee);
	room.mafia_vote(votee,voter,maxvoted);
	if(maxvoted==room.pass_mafia_number()){
		maxvoted=0;
		int max=0;
		for(int i=0;i<room.roles.size();i++){
			if(room.roles[max]->getvoted()<room.roles[i]->getvoted())
				max=i;
		}
		for(int i=0;i<room.roles.size();i++){
			room.roles[i]->reset_getvoted();
			room.roles[i]->reset_voted();
		}
		cout<<"Mafia try to kill "<<room.roles[max]->pass_name()<<endl;
		room.dead_by_mafia=max;
	}
}
void God::detect(){
	string detective_name,suspect_name;
	bool ok=false;
	cin>>detective_name>>suspect_name;
	room.check_existance(detective_name,suspect_name);
	for(int i=0;i<room.roles.size();i++){
		if(check_strings(room.roles[i]->pass_name(),detective_name) && !ok){
			if(!room.roles[i]->isdead() && check_strings(room.roles[i]->pass_role_type(),"Detective")){
				if(!room.roles[i]->check_suspects(suspect_name)){
					room.roles[i]->set_suspect(suspect_name);
					room.roles[i]->check_the_roles();
					ok=true;
					break;
				}
				else
					throw "Detective has already asked";
			}
			else
				throw "User can not ask";
		}
	}
	if(!ok)
		throw "User can not ask";
	
	else if(ok){
		for(int i=0;i<room.roles.size();i++){
			if(check_strings(room.roles[i]->pass_name(),suspect_name)){
				if(!room.roles[i]->isdead()){
					if(check_strings(room.roles[i]->pass_role_type(),"Mafia")||
						check_strings(room.roles[i]->pass_role_type(),"Silencer"))
						cout<<"Yes"<<endl;
					else
						cout<<"No"<<endl;
					break;
				}
				else
					throw "Person is dead";
			}
		}
	}
}
void God::heal(){
	string doctor_name,healed_name;
	bool ok=false;
	cin>>doctor_name>>healed_name;
	room.check_existance(doctor_name,healed_name);
	for(int i=0;i<room.roles.size();i++){
		if(check_strings(room.roles[i]->pass_name(),doctor_name) && !ok){
			if(!room.roles[i]->isdead() && check_strings(room.roles[i]->pass_role_type(),"Doctor")){
				if(!room.roles[i]->check_healeds(healed_name)){
					room.roles[i]->check_the_roles();
					room.roles[i]->set_healed(healed_name);
					ok=true;
					break;
				}
				else
					throw "Doctor has already healed";
			}
			else
				throw "User can not heal";
		}
	}
	if(!ok)
		throw "User can not ask";
	
	else if(ok){
		for(int i=0;i<room.roles.size();i++){
			if(check_strings(room.roles[i]->pass_name(),healed_name)){
				if(!room.roles[i]->isdead()){
					room.roles[i]->get_healed();
					room.healed_by_doctor.push_back(i);
					break;
				}
				else
					throw "Person is dead";
			}
		}
	}
}
void God::silent(){
	string silencer,silenced_name;
	bool ok=false;
	cin>>silencer>>silenced_name;
	room.check_existance(silencer,silenced_name);
	for(int i=0;i<room.roles.size();i++){
		if(check_strings(room.roles[i]->pass_name(),silencer) && !ok){
			if(!room.roles[i]->isdead() && check_strings(room.roles[i]->pass_role_type(),"Silencer")){
				if(!room.roles[i]->check_silenceds(silenced_name)){
					room.roles[i]->set_silenced(silenced_name);
					room.roles[i]->check_the_roles();
					ok=true;
					break;
				}
				else
					throw "Silencer has already silenced";
			}
			else
				throw "User can not ask";
		}
	}
	if(!ok)
		throw "User can not silence";
	
	else if(ok){
		for(int i=0;i<room.roles.size();i++){
			if(check_strings(room.roles[i]->pass_name(),silenced_name)){
				if(!room.roles[i]->isdead()){
					room.roles[i]->get_silenced();
					break;
				}
				else
					throw "Person is dead";
			}
		}
	}
}
void God::room_state(){
	cout<<"Mafia = "<<room.pass_mafia_number()<<endl;
	cout<<"Villager = "<<room.pass_villager_number()<<endl;
}
void God::end_day(){
	room.end_of_day();
}
void God::end_of_room(){
	room.end_of_game();
}
void God::command_function(string command){
	while(cin>>command){
		try{
			if(command=="Create_room"){
				create_room();
			}
			else if(command=="Switch_room"){
				switch_room();
			}
			else if(command=="Join"){
				join();
			}
			else if(command=="Vote" && room.day){
				vote();
			}
			else if(command=="End_vote" && room.day){
				end_vote();
			}
			else if(command=="Vote" && room.night){
				mafia_vote();
				end_day();
			}
			else if(command=="Detect" && room.night){
				detect();
				end_day();
			}
			else if(command=="Heal" && room.night){
				heal();
				end_day();
			}
			else if(command=="Silent" && room.night){
				silent();
				end_day();
			}

			else if(command=="Get_room_state"){
				room_state();
			}

			else{
				throw "Command Not Found!";
			}

			end_of_room();

		}catch(const char* except){
			cerr<<except<<endl;
		}
	}
}



// #endif