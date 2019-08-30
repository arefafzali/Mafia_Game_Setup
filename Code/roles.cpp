
#include "roles.h"
string Mafia::pass_role_type(){
	if(godfather)
		return "GodFather";
	else if(silencer)
		return "Silencer";
	else
		return "Mafia";
}
void Mafia::set_role(string role){
	if(check_strings(role,"GodFather"))
		godfather=true;
	else if(check_strings(role,"Silencer"))
		silencer=true;
}
bool Mafia::check_silenceds(string name){
	for(int i=0;i<silenced_names.size();i++){
		if(check_strings(name,silenced_names[i])){
			return true;
		}
	}
	return false;
}

string Villager::pass_role_type(){
	if(detective)
		return "Detective";
	else if(doctor)
		return "Doctor";
	else if(rouintan)
		return "RouinTan";
	else
		return "Villager";
}
void Villager::set_role(string role){
	if(check_strings(role,"Detective"))
		detective=true;
	else if(check_strings(role,"Doctor"))
		doctor=true;
	else if(check_strings(role,"Rouintan"))
		rouintan=true;
}
bool Villager::check_suspects(string name){
	for(int i=0;i<suspect_names.size();i++){
		if(check_strings(name,suspect_names[i])){
			return true;
		}
	}
	return false;
}
bool Villager::check_healeds(string name){
	for(int i=0;i<healed_names.size();i++){
		if(check_strings(name,healed_names[i])){
			return true;
		}
	}
	return false;
}


