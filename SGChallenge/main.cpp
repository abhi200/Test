#include <iostream>
#include "Statistics.h"
using namespace std;

void main()
{
	int year = 0;

	Statistics * statistic = new Statistics();

	//Run the Statistic Update
	year = statistic->run();

	//Check to see if we have valid data
	if (year > 0)
		cout << "The initial year with max population: " << year << endl;
	else
		cout << " Invalid Data" << endl;

	delete statistic;

	system("pause");
}