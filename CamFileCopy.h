// CamFileCopy.h : CAMFILECOPY �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_CAMFILECOPY_H__A3999BF6_26CA_4752_96E7_1D58A11BB5BA__INCLUDED_)
#define AFX_CAMFILECOPY_H__A3999BF6_26CA_4752_96E7_1D58A11BB5BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CCamFileCopyApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� CamFileCopy.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CCamFileCopyApp : public CWinApp
{
public:
	CCamFileCopyApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCamFileCopyApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CCamFileCopyApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CAMFILECOPY_H__A3999BF6_26CA_4752_96E7_1D58A11BB5BA__INCLUDED_)
