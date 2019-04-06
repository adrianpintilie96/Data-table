#include "stdafx.h"
#include "Observation.h"
#include <iostream>
#include <string>

//todo: make sure that you make a copy or you do not when you assing the values
Observation::Observation(std::vector<std::variant<double, std::string>> values)
	:m_values(values)
{
}

int Observation::getNumberOfValues() const
{
	return m_values.size();
}

void Observation::display() const
{
	auto PrintVisitor = [](const auto& value) { std::cout << value << " | "; };
	for (auto &value : m_values)
	{
		std::visit(PrintVisitor, value);
	}

	std::cout << std::endl;
}

Observation::~Observation()
{
}
