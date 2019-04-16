#pragma once
#include "Table.h"

class TableUtils
{
public:
	
	/* Returns a new table as a result of the union operation between the input tables */
	static Table unionOperation(const Table& firstTable, const Table& secondTable);
	/* Returns a new table as a result of the intersection operation between the input tables */
	static Table intersectionOperation(const Table& firstTable, const Table& secondTable);
	/* Returns a new table as a result of the difference operation between the input tables */
	static Table differenceOperation(const Table& firstTable, const Table& secondTable);
	/* Returns a new table as a result of the merge operation between tables that have
		the same field as primary key */
	static Table merge(const Table& firstTable, const Table& secondTable);

	/* Returns a copy of the input table, sorted using the attribute name */
	static Table sortByAttributeName(const Table& table, const std::string& attributeName);
	/* Returns a copy of the input table, sorted using the attribute index */
	static Table sortByAttributeIndex(const Table& table, const int& attributeIndex);

private:
	/* Validates the tables for common scenarios */
	static void validateTables(const Table& firstTable, const Table& secondTable);
	/* Validates that the primary key attribute of the first table is identical with 
	the primary key attribute of the second table*/
	static void validatePrimaryKey(const Table& firstTable, const Table& secondTable);

	template<class T>
	static Table tablesGenericOperation(const Table& firstTable, const Table& secondTable, T operation);
};

template<class T>
 Table TableUtils::tablesGenericOperation(const Table& firstTable, const Table& secondTable, T operation)
{
	// validate the tables
	TableUtils::validateTables(firstTable, secondTable);

	// sort the tables by the primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	// construct the new table
	Table resultTable(firstTable.m_name, firstTable.m_attributeNames, firstTable.m_primaryKeyIndex);
	std::vector<Observation> resultedObservations;

	// perform the operation
	operation(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(resultedObservations),
		ObservationComparator(firstTable.m_primaryKeyIndex)
	);

	// use addObservations to make sure we validate the input and update the keys 
	resultTable.addObservations(resultedObservations);

	return resultTable;

}
