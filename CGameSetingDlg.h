#pragma once
#include "afxdialogex.h"


// CGameSetingDlg dialog

class CGameSetingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameSetingDlg)

public:
	CGameSetingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGameSetingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETING };
#endif

public:
	int m_bLevel;

	void SetLevel(int level);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonSamplelevel();
	afx_msg void OnClickedButtonMiddlelevel();
	afx_msg void OnClickedButtonDifficultlevel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
