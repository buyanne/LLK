#pragma once
#include "afxdialogex.h"


// CGameRankDlg dialog

class CGameRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameRankDlg)

public:
	CGameRankDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGameRankDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	vector<pair<int, int> > vet;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
