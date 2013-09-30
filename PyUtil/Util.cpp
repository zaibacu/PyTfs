#include "stdafx.h"
#include "Util.h"
#include "ITfsAPI.h"

using namespace Util;

CUtil theApp;

Util::CUtil::CUtil()
	: m_hDllHandle(nullptr)
{
	m_hDllHandle = LoadLibrary(L"PyDotNet.dll");
	typedef void* (* DLL_INTERFACE)();

	DLL_INTERFACE pDllInterface = reinterpret_cast<DLL_INTERFACE>(GetProcAddress(m_hDllHandle, "GetTfs"));
	if(pDllInterface)
	{
		m_spTfs.reset(reinterpret_cast<Tfs::ITfsAPI*>(pDllInterface()));
	}

}

Util::CUtil::~CUtil()
{
	if(m_hDllHandle)
	{
		FreeLibrary(m_hDllHandle);
	}
}

Tfs::TfsTaskList* Util::CUtil::QueryTfs(String p_szQuery)
{
	if(m_spTfs)
		return m_spTfs->Query(p_szQuery);

	return nullptr;
}

bool Util::CUtil::CreateTfsItem(String p_szTitle, String p_szDescription, String p_szProject, String p_szType, long p_lParentID)
{
	if(m_spTfs)
		return m_spTfs->Create(p_szTitle, p_szDescription, p_szProject, p_szType, p_lParentID);

	return false;
}




bool CUtil::ConnectToTfs(String p_szURL, String p_szCollection)
{
	if(m_spTfs)
		return m_spTfs->Connect(p_szURL, p_szCollection);

	return false;
}

//Exports
DLLEXPORT bool ConnectToTfs(String p_szURL, String p_szCollection)
{
	return theApp.ConnectToTfs(p_szURL, p_szCollection);
}

DLLEXPORT Tfs::TfsTaskList* QueryTfs(String p_szQuery)
{
	return theApp.QueryTfs(p_szQuery);
}

DLLEXPORT bool CreateTfsItem(String p_szTitle, String p_szDescription, String p_szProject, String p_szType, long p_lParentID)
{
	return theApp.CreateTfsItem(p_szTitle, p_szDescription, p_szProject, p_szType, p_lParentID);
}
