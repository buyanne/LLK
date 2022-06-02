// CGameSetingDlg.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameSetingDlg.h"


// CGameSetingDlg dialog

IMPLEMENT_DYNAMIC(CGameSetingDlg, CDialogEx)

CGameSetingDlg::CGameSetingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETING, pParent)
{
	m_bLevel = 1;
}

CGameSetingDlg::~CGameSetingDlg()
{
}

void CGameSetingDlg::SetLevel(int level) {
	m_bLevel = level;
}

void CGameSetingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameSetingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAMPLELEVEL, &CGameSetingDlg::OnClickedButtonSamplelevel)
	ON_BN_CLICKED(IDC_BUTTON_MIDDLELEVEL, &CGameSetingDlg::OnClickedButtonMiddlelevel)
	ON_BN_CLICKED(IDC_BUTTON_DIFFICULTLEVEL, &CGameSetingDlg::OnClickedButtonDifficultlevel)
END_MESSAGE_MAP()


// CGameSetingDlg message handlers


void CGameSetingDlg::OnClickedButtonSamplelevel()
{
	// TODO: Add your control notification handler code here
	SetLevel(1);
	this->SetWindowTextW(CString(_T("¼òµ¥Ä£Ê½")));
	EndDialog(0);

}


void CGameSetingDlg::OnClickedButtonMiddlelevel()
{
	// TODO: Add your control notification handler code here
	SetLevel(2);
	EndDialog(0);
}


void CGameSetingDlg::OnClickedButtonDifficultlevel()
{
	// TODO: Add your control notification handler code here
	SetLevel(3);
	EndDialog(0);
}
