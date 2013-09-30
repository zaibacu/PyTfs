// This is the main DLL file.

#include "stdafx.h"

#include "PyDotNet.h"
#include <string>

using namespace System::Runtime::InteropServices;
using namespace System::Collections::ObjectModel;


namespace Tfs
{
	bool CTfsAPI::Connect(const char* p_szURL, const char* p_szCollection)
	{
		try
		{
			String^ UrlStr = Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char*>(p_szURL)));
			String^ CollectionStr =Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char*>(p_szCollection)));
			Uri^ tfsUri = gcnew Uri(UrlStr);
			TfsConfigurationServer^ Config = TfsConfigurationServerFactory::GetConfigurationServer(tfsUri);
			Config->Authenticate();
			if(!Config->HasAuthenticated)
			{
				Console::WriteLine("Auth Fail");
				return false;
			}

			TfsTeamProjectCollection^ TfsCollection = gcnew TfsTeamProjectCollection(gcnew Uri(UrlStr + "/" + CollectionStr));
			TfsCollection->Authenticate();
			if(!TfsCollection->HasAuthenticated)
			{
				Console::WriteLine("Auth Fail");
				return false;
			}

			TfsHolder::GetInstance()->SetWorkItems(TfsCollection);
		}
		catch(Exception^ ex)
		{
			Console::WriteLine(ex->ToString());
			return false;
		}
		
		return true;
	}

	TfsTaskList* CTfsAPI::Query(const char* p_szQuery)
	{
		TfsTaskList* pStart = new TfsTaskList();
		TfsTaskList* pCurrent = pStart;
		try
		{
			String^ QueryStr = Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char*>(p_szQuery)));
			WorkItemCollection^ Result = TfsHolder::GetInstance()->GetWorkItems()->Query(QueryStr);
			for each(WorkItem^ workItem in Result)
			{
				pCurrent->m_Task.m_lID = workItem->Id;
				pCurrent->m_Task.m_szDescription = (char*)Marshal::StringToHGlobalAnsi(workItem->Description).ToPointer();
				pCurrent->m_Task.m_szTitle = (char*)Marshal::StringToHGlobalAnsi(workItem->Title).ToPointer();

				pCurrent->m_pNext = new TfsTaskList();
				pCurrent = pCurrent->m_pNext;
			}
		}
		catch(Exception^ ex)
		{
			Console::WriteLine(ex->ToString());
			return false;
		}

		return pStart;
	}

	bool CTfsAPI::Create(const char* p_szName, const char* p_szDescription, const char* p_szProject, const char* p_szType, long p_lParentID)
	{
		try
		{
			String^ ProjectStr = Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char*>(p_szProject)));
			String^ TypeStr = Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char*>(p_szType)));
			WorkItemStore^ Items = TfsHolder::GetInstance()->GetWorkItems();
			Project^ TeamProject = Items->Projects[ProjectStr];

			WorkItem^ NewTask = gcnew WorkItem(TeamProject->WorkItemTypes[TypeStr]);
			NewTask->Title = Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char*>(p_szName)));
			NewTask->Description = Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char*>(p_szDescription)));
		}
		catch(Exception^ ex)
		{
			Console::WriteLine(ex->ToString());
			return false;
		}

		return true;
	}

}