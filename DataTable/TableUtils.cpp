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

Table TableUtils::intersectionOperation(const Table & firstTable, const Table & secondTable)
{
	//utility in table to validate they are the same

	//sort by primary key
	auto sortedTable1 = TableUtils::sortByAttributeIndex(firstTable, firstTable.m_primaryKeyIndex);
	auto sortedTable2 = TableUtils::sortByAttributeIndex(secondTable, firstTable.m_primaryKeyIndex);

	//todo: initialize different? maybe problems that not all the parameters are initialized the right way + copies
	Table intersectionTable(firstTable);

	//todo: problems here because is set. also, how to check always the primary key is unique 

	std::vector<Observation> intersectionObservations;

	std::set_intersection(
		sortedTable1.m_observations.begin(), sortedTable1.m_observations.end(),
		sortedTable2.m_observations.begin(), sortedTable2.m_observations.end(),
		std::back_inserter(intersectionObservations), 
		[&firstTable](const Observation& firstObservation, const Observation& secondObservation)
			{
				return  firstObservation.getValueByIndex(firstTable.m_primaryKeyIndex) <
					secondObservation.getValueByIndex(firstTable.m_primaryKeyIndex);
			}
	);

	//todo: copy here or?
	intersectionTable.m_observations = intersectionObservations;

	//todo: this can be by reference or not?
	return intersectionTable;
}

Table TableUtils::sortByAttributeName(const Table & table, const std::string& attributeName)
{
	//todo: check this is another copy here?
	try
	{
		return TableUtils::sortByAttributeIndex(table, table.m_attributeToIndex.at(attributeName));
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
	std::sort(sortTable.m_observations.begin(), sortTable.m_observations.end(),
		[&attributeIndex](const Observation& firstObservation, const Observation& secondObservation)
	{
		return  firstObservation.getValueByIndex(attributeIndex) <
			secondObservation.getValueByIndex(attributeIndex);
	}
	);
	
	//todo: sort ascending or descending
	return sortTable;
}




