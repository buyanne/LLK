
// LLKDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CGameDlg.h"


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg dialog



CLLKDlg::CLLKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_RELAX, &CLLKDlg::OnClickedBtnRelax)
	ON_BN_CLICKED(IDC_BTN_LEVEL, &CLLKDlg::OnClickedBtnLevel)
	ON_BN_CLICKED(IDC_BTN_HELP, &CLLKDlg::OnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_RANK, &CLLKDlg::OnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CLLKDlg::OnClickedBtnSetting)
END_MESSAGE_MAP()


// CLLKDlg message handlers

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	InitBackground();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






inline void CLLKDlg::InitBackground() {
	//Load the bitmap 
	CBitmap bmpMain;

	bmpMain.LoadBitmapW(IDB_MAIN_BG);


	//create an compatible DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);


	//select bitmap into DC
	m_dcMem.SelectObject(&bmpMain);

	//adjust the size of window
	CRect rtWin;
	CRect rtClient;
	//get the size of window
	this->GetWindowRect(rtWin);
	//get the size of client
	this->GetClientRect(rtClient);

	int nSpanWitdh = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	MoveWindow(0, 0, 800 + nSpanWitdh, 600 + nSpanHeight);
}

void CLLKDlg::OnClickedBtnBasic()
{
	// TODO: Add your control notification handler code here

	this->ShowWindow(SW_HIDE);

	CGameDlg dlg;
	dlg.setModule(BASIC_MODE);
	dlg.DoModal();

	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedBtnRelax()
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	

	dlg.setModule(LEISURE_MODE);
	dlg.DoModal();
	
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedBtnLevel()
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.setModule(BREAKTHROUGH_MODE);
	dlg.DoModal();

	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedBtnHelp()
{
	// TODO: Add your control notification handler code here

	MessageBox(_T("帮助栏\n"
		"1)游戏开始之后不可重新开始只可重新排列图案\n"
		"2)点击暂停游戏使游戏中断，暂停时不可点击提示和重排按键，可再次点击暂停游戏继续游戏\n"
		"3)点击提示按钮可以显示一个自上而下的第一对可连接的图案\n"
		"4)点击重排可对剩下图形进行随机重排序，其中已经消除方块不会重新出现"));
}


void CLLKDlg::OnClickedBtnRank()
{
	// TODO: Add your control notification handler code here
	MessageBox(_T("这是排行榜"));
}


void CLLKDlg::OnClickedBtnSetting()
{
	// TODO: Add your control notification handler code here
	MessageBox(_T("这是设置框"));
}
