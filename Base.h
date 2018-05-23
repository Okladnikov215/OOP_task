#pragma once

#include <string>

class Printable
{
public:
	virtual std::string print() const = 0;
};

class Named : public Printable
{
public:
	Named(const std::string & name)
		: name(name)
	{}

	virtual std::string print() const override
	{
		return name;
	}

private:
	std::string name;
};