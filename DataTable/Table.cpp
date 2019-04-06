#include "stdafx.h"
#include "Table.h"
#include <iostream>
#include <string>

//todo: pairs can be used to validate the input of the values added later correpond with data from the constructor
Table::Table(std::string name, std::vector<std::string> attributes, int pkIndex)
	:m_name(name),
	m_primaryKeyIndex(pkIndex)
{
	//todo: make sure you use the map the right way here because we iterate a map
	//todo: what is size t
	for (size_t index = 0; index < attributes.size(); index++)
	{
		m_attributeToIndex[attributes[index]] = index;
	}
}

Table::~Table()
{
}

int Table::getNumberOfAttributes() const
{
	return m_attributeToIndex.size();
}

int Table::getNumberOfObservations() const
{
	return m_observations.size();
}

int Table::getPrimaryKeyIndex() const
{
	return m_primaryKeyIndex;
}

//todo: be consistent with using functions of members
void Table::display() const
{

	//todo: display the attribute?
	//todo: difference between map and unordered map
	
	int index = 0;
	for (auto iterator = m_attributeToIndex.begin(); iterator != m_attributeToIndex.end(); iterator++)
	{
		if (iterator->second == index)
		{
			std::cout << iterator->first + " | ";
		}
		index++;
	}

	std::cout <<  "\n----------------------------\n";

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
