#include "stdafx.h"
#include "Observation.h"
#include <iostream>
#include <string>

Observation::Observation(const std::vector<std::variant<double, std::string>>& values)
	:m_values(values)
{
}

Observation::~Observation()
{
}


int Observation::getNumberOfValues() const
{
	return m_values.size();
}

void Observation::display() const
{
	// display the values of the observation using a visitor

	auto printVisitor = [](const auto& value) { 
		std::cout << value << " | "; 
	};

	for (auto &value : m_values)
	{
		std::visit(printVisitor, value);
	}

	std::cout << std::endl;
}

std::variant<double, std::string> Observation::getValueByIndex(const int& index) const
{
	return m_values[index];
}

void Observation::addValue(const std::variant<double, std::string>& value)
{
	m_values.push_back(value);
}

bool Observation::operator==(const Observation & other) const
{
	if (this->m_values.size() != other.getNumberOfValues())
	{
		return false;
	}

	for (size_t index = 0; index < this->m_values.size(); index++)
	{
		if (this->m_values[index] != other.getValueByIndex(index))
		{
			return false;
		}
	}

	return true;
}

