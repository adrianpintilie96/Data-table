#include "stdafx.h"
#include "Observation.h"
#include <iostream>
#include <string>

//todo: make sure that you make a copy or you do not when you assing the values
Observation::Observation(const std::vector<std::variant<double, std::string>>& values)
	:m_values(values)
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

Observation::~Observation()
{
}
