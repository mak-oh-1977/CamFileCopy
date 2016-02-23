// CamFileCopyDlg.h : ヘッダー ファイル
//

#if !defined(AFX_CAMFILECOPYDLG_H__D4CF9432_44C1_4B0E_BD9F_96F16755C0BA__INCLUDED_)
#define AFX_CAMFILECOPYDLG_H__D4CF9432_44C1_4B0E_BD9F_96F16755C0BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyDlg ダイアログ
typedef struct {
	CString strSrcDir;
	int	iDateType;
	CString strDstDir;
	CString strDstFix;
	int iDateFormat;
	CStatic* pMsgObj;
	CButton* pbtnStart;
	int iExecute;		// 0:停止中 1:実行中 2:停止要求
} COPY_INFO;

class CCamFileCopyDlg : public CDialog
{
// 構築
public:
	CCamFileCopyDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CCamFileCopyDlg)
	enum { IDD = IDD_CAMFILECOPY_DIALOG };
	CButton	m_btnStart;
	CStatic	m_objMsg;
	CString	m_strSrcDir;
	CString	m_strDstDir;
	int		m_iDateType;
	int		m_iDateFormat;
	CString	m_strDstFix;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCamFileCopyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCamFileCopyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSrcSel();
	afx_msg void OnDstSel();
	afx_msg void OnStart();
	afx_msg void OnEnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWinThread* m_pThread;
	COPY_INFO m_Info;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CAMFILECOPYDLG_H__D4CF9432_44C1_4B0E_BD9F_96F16755C0BA__INCLUDED_)
