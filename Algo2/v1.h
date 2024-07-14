#pragma once
#include <Windows.h>

#include <string>
#include <stdexcept>
#include <iostream>

#include "D:\Projects\Option2DynamicDllLoadingInRunTime\CommonInterfaces\DemoComminInterfaces.h" 


class v1 : public ISayHello
{
public: 
	HRESULT QueryInterface(REFIID riid, LPVOID* ppvObj);
	ULONG AddRef();
	ULONG Release();
	void Hello();
private:
	long m_cRef = 0 ;
};

