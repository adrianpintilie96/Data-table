// DataTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TableUtils.h"
#include <iostream>

int main()
{
	Table moleculeTable("Molecules1", { "Name", "Solubility", "Weight" }, 0);

	//todo: utility to create observation? VERY IMPORTANT TO HOW YOU CREATE THE DATA
	Observation observation1(
		{
			{ "Paracetamol"}, {4.97}, {151}
		}
	);

	Observation observation2(
		{
			{ "Caffeine" }, { 5.05 }, { 194 }
		}
	);

	Observation observation3(
		{
			{ "Indomethacin" }, { 0.4 }, { 358 }
		}
	);

	moleculeTable.addObservation(observation1);
	moleculeTable.addObservation(observation2);
	moleculeTable.addObservation(observation3);
	moleculeTable.display();
	std::cout << std::endl;

	Table moleculeTable2("Molecules2", { "Name", "Solubility", "Weight" }, 0);

	Observation observation4(
		{
			{ "Methane" }, { 22.7 }, { 16 },
		}
	);

	Observation observation5(
		{
			{ "Sulfuric acid" }, { 5.05 }, { 98 },
		}
	);

	Observation observation6(
		{
			{ "Indomethacin" }, { 0.4 }, { 358 },
		}
	);

	if (observation3 == observation6)
	{
		std::cout << "Observation 3 and observation 6 are equal.\n\n";
	}

	if (observation4 == observation2)
	{
		std::cout << "Observation 4 and observation 2 are equal.\n\n";
	}

	moleculeTable2.addObservation(observation4);
	moleculeTable2.addObservation(observation5);
	moleculeTable2.addObservation(observation6);

	moleculeTable2.display();

	std::cout << std::endl << std::endl;
	auto table3 = TableUtils::intersectionOperation(moleculeTable, moleculeTable2);
	table3.display();

	std::cout << std::endl << std::endl;
	auto table4 = TableUtils::differenceOperation(moleculeTable, moleculeTable2);
	table4.display();

	std::cout << std::endl << std::endl;
	auto table5 = TableUtils::unionOperation(moleculeTable, moleculeTable2);
	table5.display();


	Observation observation7(
		{
			{ "Paracetamol" }, {"C8H9NO2"}, { 4.97 }, { 151 },
		}
	);

	Observation observation8(
		{
			{ "Caffeine" }, {"C8H10N4O2"}, { 5.05 }, { 194 }
		}
	);

	Observation observation9(
		{
			{ "Indomethacin" },{ "C19H16ClNO4" }, { 0.4 }, { 358 }
		}
	);

	Table moleculeTable6("Molecules3", { "Name", "Formula", "Solubility", "Weight" }, 0);
	moleculeTable6.addObservation(observation7);
	moleculeTable6.addObservation(observation8);
	moleculeTable6.addObservation(observation9);

	std::cout << std::endl << std::endl;
	moleculeTable6.display();

	TableUtils::merge(moleculeTable6, moleculeTable);

	return 0;
}

