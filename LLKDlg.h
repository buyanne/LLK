
// LLKDlg.h : header file
//
#pragma once





// CLLKDlg dialog
class CLLKDlg : public CDialogEx
{
	// Construction
public:
	CLLKDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	CDC m_dcMem;
	void InitBackground();

	int background;

public:
	afx_msg void OnClickedBtnBasic();


	afx_msg void OnClickedBtnRelax();
	afx_msg void OnClickedBtnLevel();

	
	afx_msg void OnClickedBtnHelp();
	afx_msg void OnClickedBtnRank();
	afx_msg void OnClickedBtnSetting();
	int level;
};
