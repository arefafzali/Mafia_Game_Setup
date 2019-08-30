#ifndef GOD_H_
#define GOD_H_
#include "room.h"

class God{
public:
	void create_room();
	void switch_room();
	void join();
	void vote();
	void end_vote();
	void mafia_vote();
	void detect();
	void heal();
	void silent();
	void room_state();
	void end_day();
	void end_of_room();
	Room room;
	void command_function(string command);
private:	
	vector<Room> rooms;
	vector<string> allnames;
	int maxvoted=0;
};

#endif