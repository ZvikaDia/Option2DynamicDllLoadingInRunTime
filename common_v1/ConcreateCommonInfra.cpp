#include "pch.h"
#include "D:\Projects\Option2DynamicDllLoadingInRunTime\CommonInterfaces\commom_infrastructure.h"

#include "ConcreateCommonInfra.h"

HRESULT ConcreateCommonInfra::QueryInterface(REFIID   riid,
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

ULONG ConcreateCommonInfra::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}
ULONG ConcreateCommonInfra::Release()
{
    // Decrement the object's internal counter.
    ULONG ulRefCount = InterlockedDecrement(&m_cRef);
    if (0 == ulRefCount)
    {
        delete this;
    }
    return ulRefCount;
}

std::string ConcreateCommonInfra::get_text(std::string pName)
{
    std::string ret_value = "Hello in english " + pName;
    return ret_value;

}
