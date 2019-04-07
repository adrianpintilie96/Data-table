#pragma once
#include <vector>
#include <variant>

class Observation
{
public:
	Observation(const std::vector<std::variant<double, std::string>>& values);

	int getNumberOfValues() const;
	std::variant<double, std::string> getValueByIndex(const int& index) const;
	void addValue(const std::variant<double, std::string>& value);
	void display() const;
	bool operator==(const Observation& other) const;

	~Observation();
private:
	std::vector<std::variant<double, std::string>> m_values;
};

//todo: document also the classes

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