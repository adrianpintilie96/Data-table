#pragma once
#include <map>
#include "Observation.h"

class Table
{
public:
	//todo: const references
	Table(std::string name, std::vector<std::string> attributes);
	~Table();

	//todo: verify setters and getters
	int getNumberOfAttributes() const;
	int getNumberOfObservations() const;

	void display() const;

	//todo: when use map with new key, validate that no new key is added

	//todo: primary key?

	//todo: make const functions const
	//todo: check the comments from the other project
	void addObservation(Observation observation);
private:
	std::vector<Observation> m_observations;
	std::map<std::string, int> m_attributeToIndex;
	std::string m_name;
};

