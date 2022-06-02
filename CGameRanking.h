#pragma once
#include "afxdialogex.h"


// CGameRanking dialog

class CGameRanking : public CDialogEx
{
	DECLARE_DYNAMIC(CGameRanking)

public:
	CGameRanking(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGameRanking();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
