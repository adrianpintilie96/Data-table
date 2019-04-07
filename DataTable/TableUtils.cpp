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

	//sort the tables by the primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	Table unionTable(firstTable.m_name, firstTable.m_attributeNames, firstTable.m_primaryKeyIndex);
	std::vector<Observation> unionObservations;

	std::set_union(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(unionTable.m_observations),
		ObservationComparator(firstTable.m_primaryKeyIndex)
	);

	// use addObservations to make sure we validate the input and update the keys 
	unionTable.addObservations(unionObservations);

	return unionTable;
}

Table TableUtils::intersectionOperation(const Table & firstTable, const Table & secondTable)
{
	TableUtils::validateTables(firstTable, secondTable);

	//sort the tables by the primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	Table intersectionTable(firstTable.m_name, firstTable.m_attributeNames, firstTable.m_primaryKeyIndex);
	std::vector<Observation> intersectionObservations;
	std::set_intersection(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(intersectionObservations),
		ObservationComparator(firstTable.m_primaryKeyIndex)
	);

	// use addObservations to make sure we validate the input and update the keys 
	intersectionTable.addObservations(intersectionObservations);
	return intersectionTable;
}

/* todo: as the only difference between the operations defined so far is the called function,
	a more generic function should be defined. This function has as input also a pointer to the function to be called */
Table TableUtils::differenceOperation(const Table & firstTable, const Table & secondTable)
{
	TableUtils::validateTables(firstTable, secondTable);

	// sort the tables by the primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	Table differenceTable(firstTable.m_name, firstTable.m_attributeNames, firstTable.m_primaryKeyIndex);
	std::vector<Observation> differentObservations;
	std::set_difference(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(differentObservations),
		ObservationComparator(firstTable.m_primaryKeyIndex)
	);

	// use addObservations to make sure we validate the input and update the keys 
	differenceTable.addObservations(differentObservations);
	return differenceTable;
}

Table TableUtils::sortByAttributeName(const Table & table, const std::string& attributeName)
{
	return TableUtils::sortByAttributeIndex(table, table.m_attributeNamesToIndex.at(attributeName));
}

Table TableUtils::sortByAttributeIndex(const Table & table, const int & attributeIndex)
{
	if (attributeIndex > table.m_observations.size() - 1)
	{
		throw std::invalid_argument("The specified attribute does not exist in the table.");
	}

	Table sortTable(table);
	std::sort(sortTable.m_observations.begin(), sortTable.m_observations.end(), ObservationComparator(attributeIndex));
	return sortTable;
}

void TableUtils::validateTables(const Table & firstTable, const Table & secondTable)
{
	if (firstTable.m_attributeNames != secondTable.m_attributeNames)
	{
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




