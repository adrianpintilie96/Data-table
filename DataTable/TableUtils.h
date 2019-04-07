#pragma once
#include "Table.h"

class TableUtils
{
public:
	//todo: change name of table to reflect it is static and remove the constructor?
	TableUtils();
	~TableUtils();
	
	//todo: return by reference?
	static Table unionOperation(const Table& firstTable, const Table& secondTable);
	static Table intersectionOperation(const Table& firstTable, const Table& secondTable);
	static Table differenceOperation(const Table& firstTable, const Table& secondTable);
	static Table merge(const Table& firstTable, const Table& secondTable);


	//careful at this copies
	static Table sortByAttributeName(const Table& table, const std::string& attributeName);
	static Table sortByAttributeIndex(const Table& table, const int& attributeIndex);


private:
	static void validateTables(const Table& firstTable, const Table& secondTable);
	static void validatePrimaryKey(const Table& firstTable, const Table& secondTable);

};

