#pragma once
#include "afxdialogex.h"
#include"pch.h"
#include"CGameSetingDlg.h"

// CGameDlg dialog

#define GAMEWND_WIDTH				900
#define GAMEWND_HEIGHT				700

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGameDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()



protected:
	// memory 
	CDC m_dcMem;
	CDC m_dcBG;
	CDC m_dcElement;
	CDC m_dcMask;
	// the left and top point ,that is the gamemap begining point 
	CPoint m_ptGameTop;
	// the size of every element
	CSize m_sizeElem;
	// the rect of gamemap
	CRect m_rtGameRect;
	// whether click the button of pause
	BOOL m_bPause=false;
	// whether is the first point 
	BOOL m_bFirstPoint;

	BOOL m_bPlaying;

	BOOL m_bFirstEnterPause;

	INT m_bModule;

	BOOL m_bLevelModule;

	INT timeCount;

	CGameControl m_gameControl;

	

	void InitBackground();
	void InitElement();

public:
	int level;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnStartgame();
	afx_msg void OnClickedBtnReloadmap();
	afx_msg void OnClickedBtnGametips();
	afx_msg void OnClickedBtnPausegame();
	afx_msg void OnClickedBtnGamesetting();
	afx_msg void OnClickedBtnHelpingame();
	afx_msg void OnChangeEditTime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void setModule(INT module);
	void UpdateWindow();
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[4], int nVexNum);	
};
