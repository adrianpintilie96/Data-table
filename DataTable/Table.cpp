#include "stdafx.h"
#include "Table.h"
#include <iostream>
#include <string>


Table::Table(std::string name, std::vector<std::string> attributesNames, int pkIndex)
	:m_name(name),
	m_primaryKeyIndex(pkIndex),
	m_attributeNames(attributesNames)
{
	for (size_t index = 0; index < attributesNames.size(); index++)
	{
		m_attributeNamesToIndex[attributesNames[index]] = index;
	}
}

Table::~Table()
{
}

int Table::getNumberOfAttributes() const
{
	return m_attributeNames.size();
}

int Table::getNumberOfObservations() const
{
	return m_observations.size();
}

int Table::getPrimaryKeyIndex() const
{
	return m_primaryKeyIndex;
}

std::vector<std::string> Table::getAttributeNames() const
{
	return m_attributeNames;
}

void Table::display() const
{
	// display the names of the attributes
	auto attributeNames = this->getAttributeNames();

	for (auto &attributeName : attributeNames)
	{
		std::cout << attributeName + " | ";
	}

	std::cout << "\n----------------------------\n";

	// display the values of each observation
	for (auto &observation : m_observations)
	{
		observation.display();
	}

}

void Table::addObservation(const Observation& observation)
{
	// validate the value of the primary key
	auto primaryKeyValue = observation.getValueByIndex(m_primaryKeyIndex);
	if (m_primaryKeyValues.find(primaryKeyValue) != m_primaryKeyValues.end())
	{
		throw std::invalid_argument("The value of the Primary Key is not unique.");
	}

	// validate the attributes
	if (observation.getNumberOfValues() != this->getNumberOfAttributes())
	{
		throw std::invalid_argument("The number of value of the observation does not \
				correspond with the number of attributes of the table.");
	}

	// store the new values
	m_observations.push_back(observation);
	m_primaryKeyValues.insert(primaryKeyValue);
}

void Table::addObservations(const std::vector<Observation>& observations)
{
	for (auto &observation : observations)
	{
		this->addObservation(observation);
	}
}
