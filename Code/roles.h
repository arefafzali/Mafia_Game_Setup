#ifndef ROLES_H_
#define ROLES_H_

#include "headers.h"
class Roles{
public:
	string pass_name(){return personname;}
	virtual string pass_role_type()=0;
	virtual void set_role(string role)=0;
	void Set_Name(string name){personname=name;}
	void set_dead(){dead=true;check=true;}
	bool isdead(){return dead;}
	void get_silenced(){silenced=true;}
	void reset_silenced(){silenced=false;}
	bool is_silenced(){return silenced;}
	void get_rouintan(){rouintan=true;}
	void reset_rouintan(){rouintan=false;}
	bool is_rouintan(){return rouintan;}
	void get_voted(){vote=true;}
	void reset_voted(){vote=false;}
	bool voted(){return vote;}
	void get_healed(){healed=true;}
	void reset_healed(){healed=false;}
	bool is_healed(){return vote;}
	void raise_getvoted(){getvote++;}
	void reset_getvoted(){getvote=0;}
	int getvoted(){return getvote;}
	void check_the_roles(){check=true;}
	void reset_check_roles(){check=false;}
	bool is_role_checked(){return check;}
	virtual void set_suspect(string name){};
	virtual bool check_suspects(string name){};
	virtual void set_healed(string name){};
	virtual bool check_healeds(string name){};
	virtual void set_silenced(string name){};
	virtual bool check_silenceds(string name){};

private:
	// int vote=0;
	bool check=false;
	bool vote=false;
	int getvote=0;
	bool dead=false;
	bool silenced=false;
	bool healed=false;
	bool rouintan=false;
	string personname;
protected:
};


class Mafia:public Roles{
public:
	string pass_role_type();
	void set_role(string role);
	void set_silenced(string name){silenced_names.push_back(name);}
	bool check_silenceds(string name);
private:
	vector<string> silenced_names;
	bool godfather=false;
	bool silencer=false;
};

class Joker:public Roles{
public:
	string pass_role_type(){return "Joker";}
	void set_role(string role){joker=true;}
private:
	bool joker=false;
};

class Villager:public Roles{
public:
	string pass_role_type();
	void set_role(string role);
	void set_suspect(string name){suspect_names.push_back(name);}
	bool check_suspects(string name);
	void set_healed(string name){healed_names.push_back(name);}
	bool check_healeds(string name);
private:
	vector<string> suspect_names;
	vector<string> healed_names;
	bool detective=false;
	bool doctor=false;
	bool rouintan=false;
};

#endif