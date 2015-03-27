#include <iostream>
#include <fstream>
#include "Statistics.h"
#include "StringUtils.h"


//Initialize the default values
bool Statistics::init()
{
	if (!load_buffer())
		return false;

	return true;
}


//Core Logic method
int Statistics::run()
{
	//Exit cleanly if the buffer hasn't been filled
	if (!init())
		return -1;


	int population = 0; //yearly population counter
	int max_pop = 0;
	int max_year_index = 0;

	//More than one max year
	int multiple_max = 0;

	//Find the year with the max population
	for (int i = 0; i < MAX_CHANGES; i++){
		//Add the births and deaths to each year
		population += population_changes[i];

		if (population>max_pop){

			max_pop = population;
			max_year_index = i;
			//Reset multiple_max years counter to 0
			multiple_max = 0;
		}
		else if (population == max_pop){
			//Check to see if we have other years with max population then the one we are returning
			++multiple_max;
		}
	}


	if (multiple_max)
		std::cout << "There are " << multiple_max + 1 << " years with max population" << std::endl;

	return max_year_index + start_year;
}


//Parse file and load an array
bool Statistics::load_buffer()
{

	int birth_year, death_year;//Years
	std::ifstream inFile;//Input File

	char buf[100]; //file read buffer
	std::string line, key, value; //values being read


	//String Checks
	std::string errorMsg;
	bool valid = true;

	//Open the File
	inFile.open("Resources/stats.txt");

	//exit if the file is not open
	if (!inFile.is_open())
		return false;

	//Parse the contents and values
	while (!inFile.eof()){

		unsigned int delm = 0;
		int count = 0;

		//Read first line 
		inFile.getline(buf, sizeof(buf));
		line = buf;

		//Find the first delimiter
		delm = line.find_first_of(':');
		key = line.substr(0, delm); //Start Year of Decade		
		value = line.substr(delm + 1); //Count of People in the file

		//Convert the string to fill the start year and count
		if (!StringToInt(key, start_year) || !StringToInt(value, count)){

			errorMsg = " The file has invalid start year or count";
			valid = false;
			break;
		}


		//Go thru the list of people
		for (int i = 0; i < count; i++){
			//Read a line 
			inFile.getline(buf, sizeof(buf));
			line = buf;

			//Find the first delimiter
			delm = line.find_first_of(':');
			key = line.substr(0, delm); //Name of the person		
			value = line.substr(delm + 1); //Birth Year

			//Move to the next delimiter
			delm = value.find_first_of(',');
			key = value.substr(0, delm);		//Birth Year in key now
			value = value.substr(delm + 1);	 //Death Year

			if (!StringToInt(key, birth_year) || !StringToInt(value, death_year)){

				errorMsg = "File not formatted correctly or erroneous values";
				valid = false;
				break;
			}

			//Update the population count each year
			population_changes[birth_year - start_year]++;
			population_changes[death_year - start_year]--;

		}//People


		//Invalid Data
		if (!valid){

			std::cout << errorMsg.c_str() << std::endl;
			return false;
		}
		return true;

	}//EOF
}
