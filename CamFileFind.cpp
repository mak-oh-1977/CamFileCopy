// CamFileFind.cpp: CCamFileFind クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CamFileCopy.h"
#include "CamFileFind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CCamFileFind::CCamFileFind()
{

}

CCamFileFind::~CCamFileFind()
{

}

int CCamFileFind::Find(const CString& strDirName, CStringArray& strList, CStatic* pObjMsg, int* piStop)
{
	pObjMsg->SetWindowText(strDirName + "\nを検索中・・・");

	if (*piStop == 2)
		return 0;

	CFileFind FileFind;

	// すべてのファイルを検索
	CString strSearchFile = strDirName + _T("\\*.*");

	if(!FileFind.FindFile(strSearchFile)) 
		return 0; 

	BOOL bContinue = TRUE;
	while(bContinue)
	{ 
		if (*piStop == 2)
			return 0;
    
		bContinue = FileFind.FindNextFile();
    
		// ドット("." , "..")の場合 無視
		if(FileFind.IsDots()) 
			continue; 
    
		// ディレクトリの場合、そのディレクトリ内を検索するため再起呼び出し
		if(FileFind.IsDirectory()) 
		{
			Find(FileFind.GetFilePath(), strList, pObjMsg, piStop); 
		}
		else 
		{
			CString strFileName;
			strFileName = FileFind.GetFilePath();
			CString strExt;
			int iIndex;
			iIndex = strFileName.ReverseFind('.');
			if (iIndex != -1)
			{
				strExt = strFileName.Mid(iIndex + 1);
				strExt.MakeUpper();
				if (strExt == "CRW" || strExt == "CR2" || strExt == "JPEG" || strExt == "JPG")
					strList.Add(strFileName);
			}
		}
	}; 
	return 0;
}
