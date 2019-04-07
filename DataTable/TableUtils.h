#pragma once
#include "Table.h"

class TableUtils
{
public:
	TableUtils();
	~TableUtils();
	
	static Table unionOperation(const Table& firstTable, const Table& secondTable);
	static Table intersectionOperation(const Table& firstTable, const Table& secondTable);
	static Table differenceOperation(const Table& firstTable, const Table& secondTable);
	static Table merge(const Table& firstTable, const Table& secondTable);

	static Table sortByAttributeName(const Table& table, const std::string& attributeName);
	static Table sortByAttributeIndex(const Table& table, const int& attributeIndex);

private:
	static void validateTables(const Table& firstTable, const Table& secondTable);
	static void validatePrimaryKey(const Table& firstTable, const Table& secondTable);

};

