#pragma once
#include <vector>
#include <variant>

class Observation
{
public:
	Observation(const std::vector<std::variant<double, std::string>>& values);

	int getNumberOfValues() const;
	std::variant<double, std::string> getValueByIndex(const int& index) const;
	void display() const;
	bool operator==(const Observation& other) const;

	~Observation();
private:
	std::vector<std::variant<double, std::string>> m_values;
};

//todo: should getters and setters be inline?

//todo: document also the classes

class ObservationComparator
{
public:
	//todo: inline constructor?
	ObservationComparator(const int& valueIndex)
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