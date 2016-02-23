// CamFileCopy.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "CamFileCopy.h"
#include "CamFileCopyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyApp

BEGIN_MESSAGE_MAP(CCamFileCopyApp, CWinApp)
	//{{AFX_MSG_MAP(CCamFileCopyApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyApp クラスの構築

CCamFileCopyApp::CCamFileCopyApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CCamFileCopyApp オブジェクト

CCamFileCopyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyApp クラスの初期化

BOOL CCamFileCopyApp::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif
	// INIファイルのパス名を変更する
	if( m_pszProfileName ) 
	{
		delete ((void*)m_pszProfileName);
		m_pszProfileName = new char[MAX_PATH];
		if( !m_pszProfileName ) {
			AfxMessageBox("メモリ不足エラーです。");
			return FALSE;
		}
		::GetCurrentDirectory(MAX_PATH, (LPTSTR)m_pszProfileName);
		strcat((LPTSTR)m_pszProfileName, "\\CamFileCopy.INI");
	}


	CCamFileCopyDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

int CCamFileCopyApp::ExitInstance() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	if( m_pszProfileName ) 
	{
		delete ((void*)m_pszProfileName);
		m_pszProfileName = NULL;
	}
	
	return CWinApp::ExitInstance();
}
