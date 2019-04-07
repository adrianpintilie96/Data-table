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

	int getNumberOfAttributes() const;
	int getNumberOfObservations() const;
	int getPrimaryKeyIndex() const;
	std::vector<std::string> getAttributeNames() const;
	std::vector<std::variant<double, std::string>> getValuesByAttributeName(const std::string& name) const;

	void display() const;

	void addObservation(const Observation& observation);
	void addObservations(const std::vector<Observation>& observations);

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

