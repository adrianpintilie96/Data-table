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

