#include "stdafx.h"
#include "Table.h"
#include <iostream>
#include <string>

//todo: pairs can be used to validate the input of the values added later correpond with data from the constructor
Table::Table(std::string name, std::vector<std::string> attributesNames, int pkIndex)
	:m_name(name),
	m_primaryKeyIndex(pkIndex),
	m_attributeNames(attributesNames)
{
	//todo: make sure you use the map the right way here because we iterate a map
	//todo: what is size t
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

//todo: make sure you modify both map and vector to not have problems
std::vector<std::string> Table::getAttributeNames() const
{
		return m_attributeNames;
}

//todo: be consistent with using functions of members
void Table::display() const
{

	//todo: display the attribute?
	//todo: difference between map and unordered map

	auto attributeNames = this->getAttributeNames();

	for (auto &attributeName : attributeNames)
	{
		std::cout << attributeName + " | ";
	}

	std::cout << "\n----------------------------\n";

	for (auto &observation : m_observations)
	{
		observation.display();
	}

}

bool Table::operator==(const Table & other) const
{

	//todo: problem here because can have same elements but in different order
	if (this->m_observations.size() != other.getNumberOfObservations())
	{
		return false;
	}

	//for (size_t i = 0; i < length; i++)
	//{

	//}

	return true;
}

//todo: const ref
//todo: very important: change the infrastrcuture to work with values instead of observations?
void Table::addObservation(Observation observation)
{
	if (observation.getNumberOfValues() != this->getNumberOfAttributes())
	{
		throw std::invalid_argument("The number of value of the observation does not \
				correspond with the number of attributes of the table.");
	}

	//todo: validate the data types of the observation
	m_observations.push_back(observation);
}
