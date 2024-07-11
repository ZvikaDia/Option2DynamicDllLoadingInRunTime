#pragma once
class ConcreateCommonInfra:public ICommomInfrastructure
{
public:
	HRESULT QueryInterface(REFIID riid, LPVOID* ppvObj);
	ULONG AddRef();
	ULONG Release();
	std::string get_text(std::string pName);

private:
	long m_cRef = 0;
};

