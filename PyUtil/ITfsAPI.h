#pragma once

namespace Tfs
{
	struct TfsTask
	{
		const char* m_szTitle;
		const char* m_szDescription;
		long m_lID;

		~TfsTask()
		{
			delete m_szTitle;
			delete m_szDescription;
		}
	};

	struct TfsTaskList
	{
		TfsTask m_Task;
		TfsTaskList* m_pNext;
		TfsTaskList()
			: m_pNext(nullptr)
		{

		}

		~TfsTaskList()
		{
			if(m_pNext)
				delete m_pNext;
		}
	};

	class ITfsAPI
	{
	public:
		virtual ~ITfsAPI(){};

		virtual bool Connect(const char* p_szURL, const char* p_szCollection) = 0;
		virtual TfsTaskList* Query(const char* p_szQuery) = 0;
		virtual bool Create(const char* p_szName, const char* p_szDescription, const char* p_szProject, const char* p_szType, long p_lParentID) = 0;
	};
}