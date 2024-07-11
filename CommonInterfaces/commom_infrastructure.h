#pragma once

class ICommomInfrastructure :public IUnknown
{
public:
	virtual std::string get_text(std::string pName) = 0;
};