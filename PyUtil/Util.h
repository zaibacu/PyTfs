#pragma once

#include "ITfsAPI.h"

namespace Util
{
	class CUtil
	{
	private:
		std::shared_ptr<Tfs::ITfsAPI> m_spTfs;
		HINSTANCE m_hDllHandle;
	public:
		CUtil();
		virtual ~CUtil();
		//Tfs
		bool ConnectToTfs(String p_szURL, String p_szCollection);
		Tfs::TfsTaskList* QueryTfs(String p_szQuery);
		bool CreateTfsItem(String p_szTitle, String p_szDescription, String p_szProject, String p_szType, long p_lParentID);
	};
}
//Tfs
DLLEXPORT bool ConnectToTfs(String p_szURL, String p_szCollection);
DLLEXPORT Tfs::TfsTaskList* QueryTfs(String p_szQuery);
DLLEXPORT bool CreateTfsItem(String p_szTitle, String p_szDescription, String p_szProject, String p_szType, long p_lParentID);