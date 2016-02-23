// CamFileCopyDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
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
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyDlg �_�C�A���O

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
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
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
// CCamFileCopyDlg ���b�Z�[�W �n���h��

BOOL CCamFileCopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	CWinApp* pApp = AfxGetApp();
	m_strSrcDir = pApp->GetProfileString("Data", "SrcDir", "");
	m_strDstDir = pApp->GetProfileString("Data", "DstDir", "");
	m_strDstFix = pApp->GetProfileString("Data", "DstFix", "");

	m_iDateType = pApp->GetProfileInt("Data", "DateType", 0);
	m_iDateFormat = pApp->GetProfileInt("Data", "DateFormat", 0);

	m_Info.iExecute = 0;

	UpdateData(FALSE);
	
	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
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

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CCamFileCopyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CCamFileCopyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCamFileCopyDlg::OnSrcSel() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData();

	CFolderSelect fs;
	CString	strFolder;
	if (fs.Show(&strFolder, m_strSrcDir, false) == true)
		m_strSrcDir = strFolder;

	UpdateData(FALSE);
}

void CCamFileCopyDlg::OnDstSel() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
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

	AfxMessageBox("�R�s�[�I��", MB_ICONINFORMATION);

	pInfo->iExecute = 0;
	pInfo->pbtnStart->SetWindowText("�J�n");

	return TRUE;
}

void CCamFileCopyDlg::OnStart() 
{
	if (m_Info.iExecute == 1)
	{
		m_Info.iExecute = 2;
		while(m_Info.iExecute != 0)
			Sleep(1);
		AfxMessageBox("���f���܂���", MB_ICONINFORMATION);
		m_btnStart.SetWindowText("�J�n");

		return;
	}

	UpdateData();

	if (m_strSrcDir.GetLength() == 0)
	{
		AfxMessageBox("�R�s�[�����w�肵�Ă�������", MB_ICONEXCLAMATION);
		return;
	}
	if (m_strDstDir.GetLength() == 0)
	{
		AfxMessageBox("�R�s�[����w�肵�Ă�������", MB_ICONEXCLAMATION);
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

	m_btnStart.SetWindowText("���f");

}

void CCamFileCopyDlg::OnEnd() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData();

	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString("Data", "SrcDir", m_strSrcDir);
	pApp->WriteProfileString("Data", "DstDir", m_strDstDir);
	pApp->WriteProfileInt("Data", "DateType", m_iDateType);	
	pApp->WriteProfileString("Data", "DstFix", m_strDstFix);
	pApp->WriteProfileInt("Data", "DateFormat", m_iDateFormat);

	CDialog::OnCancel();
	
}
