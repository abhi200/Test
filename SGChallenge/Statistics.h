#ifndef _STATISTICS_H
#define _STATISTICS_H

#define MAX_CHANGES 100
class Statistics
{
public:
	//Default CTOR and DTOR
	Statistics(){}
	~Statistics(){}

	bool init();
	int run();
	bool load_buffer();
private:
	int population_changes[MAX_CHANGES] = {}; // Population Changes
	int start_year;

};


#endif