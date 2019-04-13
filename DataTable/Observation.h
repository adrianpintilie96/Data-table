#pragma once
#include <vector>
#include <variant>

/*
	Represents generic instances of information.
*/
class Observation
{
public:
	//todo: make sure to add assigment operator and the rule of 5
	Observation(const std::vector<std::variant<double, std::string>>& values);
	Observation(const Observation&) = default;
	Observation& operator=(const Observation&) = default;
	Observation(Observation&&) = default;
	Observation& operator=(Observation&&) = default;
	bool operator==(const Observation& other) const;
	~Observation();

	/* Returns the number of values in an observation */
	int getNumberOfValues() const;
	/* Returns the value of the observation that corresponds to the index */
	std::variant<double, std::string> getValueByIndex(const int& index) const;
	/* Adds value at the end of the observation */
	void addValue(const std::variant<double, std::string>& value);
	/* Displays the values of the observation */
	void display() const;

private:
	std::vector<std::variant<double, std::string>> m_values;
};

class ObservationComparator
{
public:
	ObservationComparator(const int& valueIndex)
		:m_valueIndex(valueIndex) {};
	~ObservationComparator() {};

	bool operator() (const Observation& firstObservation, const Observation& secondObservation)
	{
		return firstObservation.getValueByIndex(m_valueIndex) < secondObservation.getValueByIndex(m_valueIndex);
	}

private:
	int m_valueIndex;
};