
#include <Windows.h>
#include <objbase.h>
#include <map>
#include <string>
#include <vector>

// {00000000-FEED-ACDC-0000-000000000000}
extern "C" const GUID CLSID_LittleObject{ 0x00000000, 0xfeed, 0xacdc, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

class LittleObject : public IDispatch
{
private:
	int m_refcnt;

	// Valid function names for this object
	std::vector<std::wstring> mapping = {
		L"Say"
	};

public:
	LittleObject() { m_refcnt = 0; };
	~LittleObject() {};

	// IUnknown Methods

	STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv)
	{
		*ppv = NULL;
		if (riid == IID_IUnknown || riid == IID_IDispatch)
		{
			*ppv = (IDispatch*)this;
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return ++m_refcnt;
	}

	STDMETHODIMP_(ULONG) Release(void)
	{
		--m_refcnt;

		if (0 == m_refcnt)
		{
			delete this;
			return 0;
		}

		return m_refcnt;
	}

	// IDispatch Methods

	STDMETHODIMP GetTypeInfoCount(UINT* pctinfo)
	{
		*pctinfo = 0;
		return S_OK;
	}

	STDMETHODIMP GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid)
	{
		if (cNames != 1)
			return DISP_E_UNKNOWNNAME;

		std::vector<std::wstring>::iterator it;
		for (it = mapping.begin(); it != mapping.end(); ++it) {
			if (*it == rgszNames[0]) {
				*rgdispid = DISPID(it - mapping.begin());
				return S_OK;
			}
		}

		return DISP_E_UNKNOWNNAME;
	}

	// Here is where we actually get invoked

	STDMETHODIMP Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr)
	{
		std::wstring fName = mapping.at(dispidMember);

		if (fName.empty())
			return ERROR;

		std::vector<VARIANTARG> args;
		for (int i = 0; i < pdispparams->cArgs; i++) {
			args.push_back(*pdispparams->rgvarg);
		}
		

		// Code here !
		

		return S_OK;
	}

};

class Factory : public IClassFactory
{
private:
	int m_refcnt;

public:

	// IUnknown Methods

	STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv)
	{
		*ppv = NULL;
		if (riid == IID_IUnknown || riid == IID_IClassFactory)
		{
			*ppv = (IClassFactory*)this;
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}


	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return ++m_refcnt;
	}

	STDMETHODIMP_(ULONG) Release(void)
	{
		--m_refcnt;

		if (0 == m_refcnt)
		{
			delete this;
			return 0;
		}

		return m_refcnt;
	}

	// IClassFactory Methods

	STDMETHODIMP CreateInstance(IUnknown* pUnknown, REFIID riid, void** ppv)
	{
		HRESULT result;
		LittleObject* pLittleObj = NULL;
		*ppv = NULL;

		if (pUnknown != NULL)
			return CLASS_E_NOAGGREGATION;

		pLittleObj = new LittleObject();

		if (pLittleObj == NULL)
			return E_OUTOFMEMORY;

		result = pLittleObj->QueryInterface(riid, ppv);
		if (FAILED(result))
		{
			delete pLittleObj;
			pLittleObj = NULL;
		}

		return result;
	}

	STDMETHODIMP LockServer(BOOL fLock)
	{
		return NOERROR;
	}

	Factory() { m_refcnt = 0; }
	~Factory() {}
};

// Retrieve the class factory

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppvOut)
{
	*ppvOut = NULL;
	HRESULT result = CLASS_E_CLASSNOTAVAILABLE;
	Factory* factory = NULL;

	if (rclsid == CLSID_LittleObject )
	{
		factory = new Factory();

		if (NULL == factory)
			return E_OUTOFMEMORY;

		result = factory->QueryInterface(riid, ppvOut);

		if (FAILED(result)) {
			delete factory;
			factory = NULL;
		}
	}

	return result;
}


// Boilerplate DLL functions

STDAPI DllCanUnloadNow(void) {	
	return FALSE;
}

STDAPI DllRegisterServer(void){
	return S_OK;
}

STDAPI DllUnregisterServer(void) {
	return S_OK;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason, LPVOID lpReserved)
{
	return TRUE;
}