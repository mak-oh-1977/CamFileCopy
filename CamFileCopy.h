// CamFileCopy.h : CAMFILECOPY アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_CAMFILECOPY_H__A3999BF6_26CA_4752_96E7_1D58A11BB5BA__INCLUDED_)
#define AFX_CAMFILECOPY_H__A3999BF6_26CA_4752_96E7_1D58A11BB5BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyApp:
// このクラスの動作の定義に関しては CamFileCopy.cpp ファイルを参照してください。
//

class CCamFileCopyApp : public CWinApp
{
public:
	CCamFileCopyApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCamFileCopyApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CCamFileCopyApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CAMFILECOPY_H__A3999BF6_26CA_4752_96E7_1D58A11BB5BA__INCLUDED_)
