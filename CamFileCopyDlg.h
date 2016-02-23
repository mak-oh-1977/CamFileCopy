// CamFileCopyDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_CAMFILECOPYDLG_H__D4CF9432_44C1_4B0E_BD9F_96F16755C0BA__INCLUDED_)
#define AFX_CAMFILECOPYDLG_H__D4CF9432_44C1_4B0E_BD9F_96F16755C0BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyDlg �_�C�A���O
typedef struct {
	CString strSrcDir;
	int	iDateType;
	CString strDstDir;
	CString strDstFix;
	int iDateFormat;
	CStatic* pMsgObj;
	CButton* pbtnStart;
	int iExecute;		// 0:��~�� 1:���s�� 2:��~�v��
} COPY_INFO;

class CCamFileCopyDlg : public CDialog
{
// �\�z
public:
	CCamFileCopyDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
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

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCamFileCopyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CAMFILECOPYDLG_H__D4CF9432_44C1_4B0E_BD9F_96F16755C0BA__INCLUDED_)
