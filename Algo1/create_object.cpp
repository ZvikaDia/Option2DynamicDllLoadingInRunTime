#include "pch.h"
#include "v1.h"
#include "v2.h"

extern "C" {
	__declspec(dllexport) HRESULT CreateObject(std::string pObjectName, void** ppv);
}

HRESULT CreateObject(std::string pObjectName , void** ppv)
{
	if (pObjectName == "v1")
	{
		ISayHello * ret_value = new v1();

		*ppv = ret_value;
		
		return S_OK;
	}
	if (pObjectName == "v2")
	{
		ISayHello* ret_value = new v2();

		*ppv = ret_value;

		return S_OK;
	}
}

