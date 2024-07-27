#include "pch.h"
#include "v1.h"
#include "D:\Projects\Option2DynamicDllLoadingInRunTime\CommonInterfaces\commom_infrastructure.h"
#include "D:\Projects\Option2DynamicDllLoadingInRunTime\ComSupport\comsupport.h"


HRESULT v1::QueryInterface(REFIID   riid,
    LPVOID* ppvObj)
{
    // Always set out parameter to NULL, validating it first.
    /*
    if (!ppvObj)
        return E_INVALIDARG;
    *ppvObj = NULL;
    if (riid == IID_IUnknown || riid == IID_IMAPIProp ||
        riid == IID_IMAPIStatus)
    {
        // Increment the reference count and return the pointer.
        *ppvObj = (LPVOID)this;
        AddRef();
        return NOERROR;
    }
    return E_NOINTERFACE;
    */
    return S_OK;
}

ULONG v1::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}
ULONG v1::Release()
{
    // Decrement the object's internal counter.
    ULONG ulRefCount = InterlockedDecrement(&m_cRef);
    if (0 == ulRefCount)
    {
        delete this;
    }
    return ulRefCount;
}

void v1::Hello()
{
    //Calls the hello c exported function 
    return legacy_hello_function ()
}

    ICommomInfrastructure* theCommomInfrastructure = (ICommomInfrastructure*)CreateObjectFromYaml("common_infra", "ICommomInfrastructure");

    std::string theblese = theCommomInfrastructure->get_text("monica bellucci");

    std::cout << "\nHello " << theblese << "from ver 2 !\n" << __FILE__;
}
