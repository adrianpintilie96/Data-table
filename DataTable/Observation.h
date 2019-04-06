#pragma once
#include <vector>
#include <variant>

class Observation
{
public:
	Observation(std::vector<std::variant<double, std::string>> values);

	int getNumberOfValues() const;
	void display() const;
	std::variant<double, std::string> getValueByIndex(int index) const;

	bool operator==(const Observation& other) const;

	~Observation();
private:
	std::vector<std::variant<double, std::string>> m_values;
};

//todo: should getters and setters be inline?

class ObservationComparator
{
public:
	ObservationComparator(int valueIndex)
		:m_valueIndex(valueIndex) {};
	~ObservationComparator() {};

	//todo: error at comparison is possibile?
	inline bool operator() (const Observation& firstObservation, const Observation& secondObservation)
	{
		return firstObservation.getValueByIndex(m_valueIndex) < secondObservation.getValueByIndex(m_valueIndex);
	}

private:
	int m_valueIndex;
};

//todo: move to cpp functons of comparator?