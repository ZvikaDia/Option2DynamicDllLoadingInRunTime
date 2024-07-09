#pragma once
class ISayHello :public IUnknown
{
public:
	virtual void Hello() = 0;
};