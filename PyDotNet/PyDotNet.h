// PyDotNet.h

#pragma once
#include "../PyUtil/ITfsAPI.h"
using namespace System;
using namespace Microsoft::TeamFoundation::WorkItemTracking::Client;
using namespace Microsoft::TeamFoundation::Client; 
using namespace Microsoft::TeamFoundation::Framework::Common;
using namespace Microsoft::TeamFoundation::Framework::Client;

namespace Tfs
{
	class CTfsAPI : public ITfsAPI
	{
	public:
		virtual bool Connect(const char* p_szURL, const char* p_szCollection) override;
		virtual TfsTaskList* Query(const char* p_szQuery) override;
		virtual bool Create(const char* p_szName, const char* p_szDescription, const char* p_szProject, const char* p_szType, long p_lParentID) override;
	};

	public ref class TfsHolder
	{
	private:
		static TfsHolder^ m_Instance;
	public:
		static TfsHolder^ GetInstance()
		{
			if(!m_Instance)
				m_Instance = gcnew TfsHolder();

			return m_Instance;
		}

	//Non static stuff
	private:
		TfsHolder()
		{

		}

		WorkItemStore^ m_WorkItems;
	public:
		~TfsHolder()
		{

		}

		WorkItemStore^ GetWorkItems()
		{
			return m_WorkItems;
		}

		void SetWorkItems(TfsTeamProjectCollection^ TfsCollection)
		{
			m_WorkItems = gcnew WorkItemStore(TfsCollection);
		}
	};
}

extern "C" __declspec(dllexport) void* GetTfs()
{
	return static_cast<void*>(new Tfs::CTfsAPI());
}
