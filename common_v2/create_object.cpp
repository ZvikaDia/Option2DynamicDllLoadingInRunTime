#include "pch.h"
#include "D:\Projects\Option2DynamicDllLoadingInRunTime\CommonInterfaces\commom_infrastructure.h"
#include "ConcreateCommonInfra.h"

extern "C" {
	__declspec(dllexport) HRESULT CreateObject(std::string pObjectName, void** ppv);
}

HRESULT CreateObject(std::string pObjectName , void** ppv)
{
	if (pObjectName == "ICommomInfrastructure")
	{
		ICommomInfrastructure* ret_value = new ConcreateCommonInfra();

		*ppv = ret_value;
		
		return S_OK;
	}
}

