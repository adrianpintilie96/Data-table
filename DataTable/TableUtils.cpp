#include "stdafx.h"
#include "TableUtils.h"
#include <algorithm>
#include <iostream>

Table TableUtils::unionOperation(const Table & firstTable, const Table & secondTable)
{
	// call tablesGenericOperation with set_union
	return TableUtils::tablesGenericOperation(firstTable, secondTable,
		std::set_union<
			std::vector<Observation>::iterator, std::vector<Observation>::iterator, 
			std::back_insert_iterator<std::vector<Observation>>, ObservationComparator
		>);
}

Table TableUtils::intersectionOperation(const Table & firstTable, const Table & secondTable)
{
	// call tablesGenericOperation with set_intersection
	return TableUtils::tablesGenericOperation(firstTable, secondTable,
		std::set_intersection<
			std::vector<Observation>::iterator, std::vector<Observation>::iterator,
			std::back_insert_iterator<std::vector<Observation>>, ObservationComparator
		>);
}

Table TableUtils::differenceOperation(const Table & firstTable, const Table & secondTable)
{
	// call tablesGenericOperation with tablesGenericOperation
	return TableUtils::tablesGenericOperation(firstTable, secondTable,
		std::set_difference<
		std::vector<Observation>::iterator, std::vector<Observation>::iterator,
		std::back_insert_iterator<std::vector<Observation>>, ObservationComparator
		>);
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

	validatePrimaryKey(firstTable, secondTable);
}

void TableUtils::validatePrimaryKey(const Table & firstTable, const Table & secondTable)
{
	if (firstTable.m_primaryKeyIndex != secondTable.m_primaryKeyIndex)
	{
		throw std::invalid_argument("The primary keys of the tables \
				do not correspond.");
	}
}

/*      This solutions is limited to tables that have the same number of values, and the same values
   for the primary key field.
        To add support for tables that have a different number of values for the primary key field,
   the std::variant used in the Observation class should also support std::monostate, in order to
   simulate null values.
		The new version of the merge function will add new values to observations that have the 
	same value for the primary key field, and use null for all the other observations.
*/
Table TableUtils::merge(const Table& firstTable, const Table& secondTable)
{
	validatePrimaryKey(firstTable, secondTable);

	if (firstTable.getNumberOfObservations() != secondTable.getNumberOfObservations())
	{
		throw std::invalid_argument("The number of values of the tables does not \
				correspond.");
	}

	/* create a new table starting from the second table,
	where the missing attributes from the first table will be added */
	Table mergedTable(secondTable);

	std::vector<std::string> firstTableAttributes = firstTable.getAttributeNames();
	std::sort(firstTableAttributes.begin(), firstTableAttributes.end());

	std::vector<std::string> secondTableAttributes = secondTable.getAttributeNames();
	std::sort(secondTableAttributes.begin(), secondTableAttributes.end());

	std::vector<std::string> newAttributeNames;
	std::set_difference(
		firstTableAttributes.begin(), firstTableAttributes.end(),
		secondTableAttributes.begin(), secondTableAttributes.end(),
		std::back_inserter(newAttributeNames));

	// update the map containing the attribute names
	int numberOfAttributes = mergedTable.m_attributeNames.size();
	int newAttributeNameIndex = 0;
	for (int i = numberOfAttributes; i < numberOfAttributes+newAttributeNames.size() ; i++)
	{
		mergedTable.m_attributeNamesToIndex[newAttributeNames[newAttributeNameIndex]] = i;
		newAttributeNameIndex++;
	}

	// also update the attribute names
	mergedTable.m_attributeNames.insert(mergedTable.m_attributeNames.end(), 
		newAttributeNames.begin(), newAttributeNames.end());

	// convert names to indices
	std::vector<int> attributeIndeces(newAttributeNames.size());
	for (int i = 0; i < newAttributeNames.size(); i++)
	{
		attributeIndeces[i] = firstTable.m_attributeNamesToIndex.at(newAttributeNames[i]);
	}

	int primaryKeyIndex = secondTable.m_primaryKeyIndex;

	for (int i = 0; i < firstTable.m_observations.size(); i++)
	{
		auto firstTableObservation = firstTable.m_observations[i];
		auto secondTableObservation = secondTable.m_observations[i];

		// validate that the values of the primary keys are equal
		if (firstTableObservation.getValueByIndex(primaryKeyIndex) == secondTableObservation.getValueByIndex(primaryKeyIndex))
		{
			for (auto &attributeIndex : attributeIndeces)
			{
				mergedTable.m_observations[i].addValue(firstTableObservation.getValueByIndex(attributeIndex));
			}
		}
		else
		{
			throw std::invalid_argument("The tables do not have the same observations.");
		}
	}

	return mergedTable;
}





