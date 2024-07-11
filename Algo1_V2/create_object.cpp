#include "pch.h"
#include "SayHelloImplAlgo1_v2.h"

extern "C" {
	__declspec(dllexport) HRESULT CreateObject(std::string pObjectName, void** ppv);
}

HRESULT CreateObject(std::string pObjectName , void** ppv)
{
	if (pObjectName == "SayHello")
	{
		ISayHello * ret_value = new SayHelloImplAlgo1_v2();

		*ppv = ret_value;
		
		return S_OK;
	}
}

