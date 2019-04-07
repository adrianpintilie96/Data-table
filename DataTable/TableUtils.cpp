#include "stdafx.h"
#include "TableUtils.h"
#include <algorithm>
#include <iostream>

TableUtils::TableUtils()
{
}


TableUtils::~TableUtils()
{
}

Table TableUtils::unionOperation(const Table & firstTable, const Table & secondTable)
{
	TableUtils::validateTables(firstTable, secondTable);
	//todo: to catch here the error? think not

	//sort the tables by the primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	//todo: initialize different? maybe problems that not all the parameters are initialized the right way + copies
	Table intersectionTable(firstTable);
	//todo: problems here because is set. also, how to check always the primary key is unique 

	std::vector<Observation> intersectionObservations;
	std::set_union(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(intersectionObservations),
		ObservationComparator(firstTable.m_primaryKeyIndex)
	);
	//todo: copy here or?
	intersectionTable.m_observations = intersectionObservations;

	//todo: this can be by reference or not?
	return intersectionTable;
}

Table TableUtils::intersectionOperation(const Table & firstTable, const Table & secondTable)
{
	TableUtils::validateTables(firstTable, secondTable);

	//sort the tables by the primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	Table intersectionTable(firstTable);
	std::vector<Observation> intersectionObservations;

	std::set_intersection(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(intersectionObservations),
		ObservationComparator(firstTable.m_primaryKeyIndex)
	);

	intersectionTable.m_observations = intersectionObservations;
	return intersectionTable;
}

Table TableUtils::differenceOperation(const Table & firstTable, const Table & secondTable)
{
	TableUtils::validateTables(firstTable, secondTable);

	// sort the tables by the primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	// create the new table as a copy of the first table
	Table intersectionTable(firstTable);
	std::vector<Observation> intersectionObservations;
	
	// perform the difference between the observations of the two tables;
	std::set_difference(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(intersectionObservations),
		ObservationComparator(firstTable.m_primaryKeyIndex)
	);

	// assign the resulted values to the new table
	intersectionTable.m_observations = intersectionObservations;
	return intersectionTable;
}



Table TableUtils::sortByAttributeName(const Table & table, const std::string& attributeName)
{
	//todo: check this is another copy here?
	try
	{
		return TableUtils::sortByAttributeIndex(table, table.m_attributeNamesToIndex.at(attributeName));
	}
	catch (const std::out_of_range&)
	{
		std::cerr << "The specified attribute does not exist in the table.\n";
		return table;
	}
}

Table TableUtils::sortByAttributeIndex(const Table & table, const int & attributeIndex)
{
	Table sortTable = table;
	//todo: take care on what other parameters are set when copy here

	//todo: validate the index here to be less + should catch all the throws?
	std::sort(sortTable.m_observations.begin(), sortTable.m_observations.end(), ObservationComparator(attributeIndex));

	//todo: sort ascending or descending can be solved easily with default parameter
	return sortTable;
}

void TableUtils::validateTables(const Table & firstTable, const Table & secondTable)
{
	//todo: catch only invalid argument exception
	if (firstTable.m_attributeNames != secondTable.m_attributeNames)
	{
		//todo: is this message correct?
		//this comparison works for vectors?
		throw std::invalid_argument("The attributes of the tables \
				do not correspond.");
	}

	if (firstTable.m_primaryKeyIndex != secondTable.m_primaryKeyIndex)
	{
		throw std::invalid_argument("The primary keys of the tables \
				do not correspond.");
	}
}

Table TableUtils::merge(const Table& firstTable, const Table& secondTable)
{
	//todo: validate

	//important use primary key

	//todo: copies x2;
	std::vector<std::string> firstTableAttributes = firstTable.getAttributeNames();
	std::sort(firstTableAttributes.begin(), firstTableAttributes.end());

	std::vector<std::string> secondTableAttributes = secondTable.getAttributeNames();
	std::sort(secondTableAttributes.begin(), secondTableAttributes.end());

	std::vector<std::string> newAttributeNames;

	std::set_difference(
		firstTableAttributes.begin(), firstTableAttributes.end(),
		secondTableAttributes.begin(), secondTableAttributes.end(),
		std::back_inserter(newAttributeNames));

	Table mergedTable(firstTable);

	for (auto &attributeName : newAttributeNames)
	{
		auto values = firstTable.getValuesByAttributeName(attributeName);
	}

	

	return Table("", { "","" }, 0);
	
}




