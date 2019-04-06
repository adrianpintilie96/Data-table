// DataTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Table.h"

int main()
{
	Table moleculeTable("Molecules", { "Name", "Solubility", "Weight"});

	//todo: utility to create observation?
	Observation observation1(
		{
			{ "Paracetamol"}, {4.97}, {151},
		}
	);

	Observation observation2(
		{
			{ "Caffeine" },{ 5.05 },{ 194 },
		}
	);

	Observation observation3(
		{
			{ "Indomethacin" },{ 0.4 },{ 358 },
		}
	);
	
	moleculeTable.addObservation(observation1);
	moleculeTable.addObservation(observation2);
	moleculeTable.addObservation(observation3);

	moleculeTable.display();
	
    return 0;
}

