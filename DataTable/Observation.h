#pragma once
#include <vector>
#include <variant>

class Observation
{
public:
	Observation(std::vector<std::variant<double, std::string>> values);

	int getNumberOfValues() const;
	void display() const;

	~Observation();
private:
	std::vector<std::variant<double, std::string>> m_values;
};

