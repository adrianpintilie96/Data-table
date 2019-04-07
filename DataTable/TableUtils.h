#pragma once
#include "Table.h"

class TableUtils
{
public:
	TableUtils();
	~TableUtils();
	
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

};

