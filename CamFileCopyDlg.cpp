// CamFileCopyDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "CamFileCopy.h"
#include "CamFileCopyDlg.h"

#include "FolderSelect.h"
#include "CamFileFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyDlg ダイアログ

CCamFileCopyDlg::CCamFileCopyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCamFileCopyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamFileCopyDlg)
	m_strSrcDir = _T("");
	m_strDstDir = _T("");
	m_iDateType = -1;
	m_iDateFormat = -1;
	m_strDstFix = _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCamFileCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamFileCopyDlg)
	DDX_Control(pDX, IDC_START, m_btnStart);
	DDX_Control(pDX, IDC_MSG, m_objMsg);
	DDX_Text(pDX, IDC_SRC_DIR, m_strSrcDir);
	DDX_Text(pDX, IDC_DST_DIR, m_strDstDir);
	DDX_Radio(pDX, IDC_DATE_TYPE, m_iDateType);
	DDX_CBIndex(pDX, IDC_DATE_FORMAT, m_iDateFormat);
	DDX_Text(pDX, IDC_DST_FIX, m_strDstFix);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCamFileCopyDlg, CDialog)
	//{{AFX_MSG_MAP(CCamFileCopyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SRC_SEL, OnSrcSel)
	ON_BN_CLICKED(IDC_DST_SEL, OnDstSel)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_END, OnEnd)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyDlg メッセージ ハンドラ

BOOL CCamFileCopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	CWinApp* pApp = AfxGetApp();
	m_strSrcDir = pApp->GetProfileString("Data", "SrcDir", "");
	m_strDstDir = pApp->GetProfileString("Data", "DstDir", "");
	m_strDstFix = pApp->GetProfileString("Data", "DstFix", "");

	m_iDateType = pApp->GetProfileInt("Data", "DateType", 0);
	m_iDateFormat = pApp->GetProfileInt("Data", "DateFormat", 0);

	m_Info.iExecute = 0;

	UpdateData(FALSE);
	
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CCamFileCopyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CCamFileCopyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CCamFileCopyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCamFileCopyDlg::OnSrcSel() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData();

	CFolderSelect fs;
	CString	strFolder;
	if (fs.Show(&strFolder, m_strSrcDir, false) == true)
		m_strSrcDir = strFolder;

	UpdateData(FALSE);
}

void CCamFileCopyDlg::OnDstSel() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData();

	CFolderSelect fs;
	CString	strFolder;
	if (fs.Show(&strFolder, m_strDstDir, false) == true)
		m_strDstDir = strFolder;

	UpdateData(FALSE);
}

UINT ThreadProcess( LPVOID pParam )
{

	ASSERT(pParam != NULL);

	COPY_INFO* pInfo;
	pInfo = (COPY_INFO*)pParam;
	pInfo->iExecute = 1;

	CCamFileFind rff;
	CStringArray strList;
	rff.Find(pInfo->strSrcDir, strList, pInfo->pMsgObj, &pInfo->iExecute);
	
	if (pInfo->iExecute == 2)
	{
		pInfo->iExecute = 0;
		return 0;
	}

	if (pInfo->iDateType == 0)
	{
		CString strDstDir;
		strDstDir = pInfo->strDstDir + pInfo->strDstFix;
		::CreateDirectory(strDstDir, NULL);
		int iSize;
		iSize = strList.GetSize();
		for(int i = 0; i < iSize; i++)
		{
			if (pInfo->iExecute == 2)
			{
				pInfo->iExecute = 0;
				return 0;
			}
			CString strSrcFile;
			strSrcFile = strList.GetAt(i);

			CString strDstFile;
			strDstFile = strDstDir + strSrcFile.Mid(strSrcFile.ReverseFind('\\'));
			CString s;
			s.Format("%d/%d\n%s\n==>\n%s", i + 1, iSize, strSrcFile, strDstFile);
			pInfo->pMsgObj->SetWindowText(s);

			::CopyFile(strSrcFile, strDstFile, TRUE);
		}
	}
	else
	{
		int iSize;
		iSize = strList.GetSize();
		CString strBeforeDir;
		strBeforeDir = "";
		for(int i = 0; i < iSize; i++)
		{
			if (pInfo->iExecute == 2)
			{
				pInfo->iExecute = 0;
				return 0;
			}

			CString strSrcFile;
			strSrcFile = strList.GetAt(i);

			HANDLE hFile;
			hFile = CreateFile(strSrcFile, GENERIC_READ, FILE_SHARE_WRITE, 
					NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		    FILETIME fTime;
			GetFileTime(hFile, NULL, NULL, &fTime);

			CloseHandle(hFile);

		    FILETIME fLocalTime;
			FileTimeToLocalFileTime(&fTime , &fLocalTime);

			SYSTEMTIME stTime;
			FileTimeToSystemTime(&fLocalTime , &stTime);

			CString strDstDate;
			switch(pInfo->iDateFormat)
			{
				case 0:
					strDstDate.Format("%04d_%02d_%02d", stTime.wYear, stTime.wMonth, stTime.wDay);
					break;
				case 1:
					strDstDate.Format("%04d%02d%02d", stTime.wYear, stTime.wMonth, stTime.wDay);
					break;
				case 2:
					strDstDate.Format("%02d%02d%02d", stTime.wYear % 100, stTime.wMonth, stTime.wDay);
					break;
				default:
					break;
			}

			CString strDstDir;
			strDstDir = pInfo->strDstDir + strDstDate;

			if (strBeforeDir != strDstDir)
			{
				::CreateDirectory(strDstDir, NULL);
				strBeforeDir = strDstDir;
			}

			CString strDstFile;
			strDstFile = strDstDir + strSrcFile.Mid(strSrcFile.ReverseFind('\\'));
			CString s;
			s.Format("%d/%d\n%s\n==>\n%s", i + 1, iSize, strSrcFile, strDstFile);
			pInfo->pMsgObj->SetWindowText(s);

			::CopyFile(strSrcFile, strDstFile, TRUE);
		}
		
	}

	AfxMessageBox("コピー終了", MB_ICONINFORMATION);

	pInfo->iExecute = 0;
	pInfo->pbtnStart->SetWindowText("開始");

	return TRUE;
}

void CCamFileCopyDlg::OnStart() 
{
	if (m_Info.iExecute == 1)
	{
		m_Info.iExecute = 2;
		while(m_Info.iExecute != 0)
			Sleep(1);
		AfxMessageBox("中断しました", MB_ICONINFORMATION);
		m_btnStart.SetWindowText("開始");

		return;
	}

	UpdateData();

	if (m_strSrcDir.GetLength() == 0)
	{
		AfxMessageBox("コピー元を指定してください", MB_ICONEXCLAMATION);
		return;
	}
	if (m_strDstDir.GetLength() == 0)
	{
		AfxMessageBox("コピー先を指定してください", MB_ICONEXCLAMATION);
		return;
	}

	m_Info.strSrcDir = m_strSrcDir;
	m_Info.iDateType = m_iDateType;
	m_Info.strDstDir = m_strDstDir;
	m_Info.strDstFix = m_strDstFix;
	m_Info.iDateFormat = m_iDateFormat;
	m_Info.pMsgObj = &m_objMsg;
	m_Info.pbtnStart = &m_btnStart;

	m_pThread = AfxBeginThread(ThreadProcess, &m_Info);

	m_btnStart.SetWindowText("中断");

}

void CCamFileCopyDlg::OnEnd() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData();

	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString("Data", "SrcDir", m_strSrcDir);
	pApp->WriteProfileString("Data", "DstDir", m_strDstDir);
	pApp->WriteProfileInt("Data", "DateType", m_iDateType);	
	pApp->WriteProfileString("Data", "DstFix", m_strDstFix);
	pApp->WriteProfileInt("Data", "DateFormat", m_iDateFormat);

	CDialog::OnCancel();
	
}
