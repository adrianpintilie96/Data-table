#pragma once
#include <map>
#include "Observation.h"

class Table
{
public:
	//todo: const references
	Table(std::string name, std::vector<std::string> attributes, int pkIndex);
	~Table();

	//todo: verify setters and getters
	int getNumberOfAttributes() const;
	int getNumberOfObservations() const;
	int getPrimaryKeyIndex() const;
	std::vector<std::string> getAttributeNames() const;


	void display() const;
	bool operator==(const Table& other) const;

	//todo: when use map with new key, validate that no new key is added

	//todo: primary key?

	//todo: make const functions const
	//todo: check the comments from the other project
	void addObservation(Observation observation);
private:
	std::vector<Observation> m_observations;
	//todo: if boost was available, could use multi index containers
	std::map<std::string, int> m_attributeNamesToIndex;
	std::vector<std::string> m_attributeNames;

	std::string m_name;
	int m_primaryKeyIndex;

	friend class TableUtils;
};

