// DataTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TableUtils.h"
#include <iostream>

int main()
{
	Table moleculeTable("Molecules", { "Name", "Solubility", "Weight"}, 0);

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
	

	Table moleculeTable2("Molecules", { "Name", "Solubility", "Weight" }, 0);

	//todo: update molecules
	Observation observation4(
		{
			{ "a" },{ 4.97 },{ 151 },
		}
	);

	Observation observation5(
		{
			{ "b" },{ 5.05 },{ 194 },
		}
	);

	Observation observation6(
		{
			{ "Indomethacin" },{ 0.4 },{ 358 },
		}
	);

	moleculeTable2.addObservation(observation4);
	moleculeTable2.addObservation(observation5);
	moleculeTable2.addObservation(observation6);

	std::cout << (observation3 == observation6) << std::endl;
	std::cout << (observation3 == observation5) << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	moleculeTable2.display();

	std::cout << std::endl;
	std::cout << std::endl;

	auto table3 = TableUtils::intersectionOperation(moleculeTable, moleculeTable2);

	table3.display();

    return 0;
}

