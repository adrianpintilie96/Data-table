#pragma once
#include <unordered_set>
#include <unordered_map>
#include "Observation.h"

class Table
{
public:

	/* Additional, the names of the attributes can be received as pairs, where the second element
		represents the data type. This approach is useful to validate the format of the new observations */
	Table(std::string name, std::vector<std::string> attributes, int pkIndex);
	~Table();

	/* Returns the number of attributes of the table */
	int getNumberOfAttributes() const;
	/* Returns the number of observations of a table */
	int getNumberOfObservations() const;
	/* Returns the index of the primary key attribute */
	int getPrimaryKeyIndex() const;
	/* Returns the names of the attributes */
	std::vector<std::string> getAttributeNames() const;
	/* Displays all the observations of the table */
	void display() const;

	/* Adds a new observation to the table */
	void addObservation(const Observation& observation);
	/* Adds multiple observations to the table */
	void addObservations(const std::vector<Observation>& observations);

	Table(const Table&) = default;
	Table& operator=(const Table&) = default;
	Table(Table && table) = default;
	Table& operator=(Table&&) = default;

private:
	std::vector<Observation> m_observations;

	/*if boost is available, multi-index containers can be used to 
	 to avoid using multiple containers for the attribute names */
	std::unordered_map<std::string, int> m_attributeNamesToIndex;
	std::vector<std::string> m_attributeNames;

	// used to validate the uniqueness of the keys
	std::unordered_set<std::variant<double, std::string>> m_primaryKeyValues;
	int m_primaryKeyIndex;

	std::string m_name;

	friend class TableUtils;
};

