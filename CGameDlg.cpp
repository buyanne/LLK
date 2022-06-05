// CGameDlg.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include"CGameSetingDlg.h"
#include <fstream>





// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = MAP_TOP;
	m_ptGameTop.y = MAP_LETF;

	//初始化图片元素大小
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	m_bFirstPoint = true;

	m_bPlaying = false;

	m_bFirstEnterPause = true;

	m_bModule = LEISURE_MODE;

	level = 1;

	m_bLevelModule = false;

	if (timeCount == 0) {
		timeCount = MAX_TIME;
	}

}

CGameDlg::~CGameDlg()
{

}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_STARTGAME, &CGameDlg::OnClickedBtnStartgame)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_RELOADMAP, &CGameDlg::OnClickedBtnReloadmap)
	ON_BN_CLICKED(IDC_BTN_GAMETIPS, &CGameDlg::OnClickedBtnGametips)
	ON_BN_CLICKED(IDC_BTN_PAUSEGAME, &CGameDlg::OnClickedBtnPausegame)
	ON_BN_CLICKED(IDC_BTN_GAMESETTING, &CGameDlg::OnClickedBtnGamesetting)
	ON_BN_CLICKED(IDC_BTN_HELPINGAME, &CGameDlg::OnClickedBtnHelpingame)
	ON_EN_CHANGE(IDC_EDIT_TIME, &CGameDlg::OnChangeEditTime)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGameDlg message handlers


void CGameDlg::InitBackground() {
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\CGameBackground.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CClientDC dc(this);

	m_dcBG.CreateCompatibleDC(&dc);

	//select bitmap
	m_dcBG.SelectObject(bmp);

	//init memory dc 
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, GAMEWND_WIDTH, GAMEWND_HEIGHT);
	m_dcMem.SelectObject(&bmpMem);


	m_dcMem.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcBG, 0, 0, SRCCOPY);


	UpdateWindow();
}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages


	dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT,
		&m_dcMem, 0, 0, SRCCOPY);
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitBackground();
	InitElement();
	if (m_bModule == BASIC_MODE) {
		this->SetWindowTextW(CString("欢乐连连看--基本模式"));


		this->GetDlgItem(IDC_BTN_GAMETIPS)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BTN_RELOADMAP)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BTN_PAUSEGAME)->EnableWindow(FALSE);
	}
	else if (m_bModule == LEISURE_MODE) {
		this->SetWindowTextW(CString("欢乐连连看--休闲模式"));

		this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);
		this->GetDlgItem(IDC_STATIC)->ShowWindow(FALSE);
	}
	else if (m_bModule == BREAKTHROUGH_MODE) {
		this->SetWindowTextW(CString("欢乐连连看--闯关模式"));
		this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);
		this->GetDlgItem(IDC_STATIC)->ShowWindow(FALSE);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameDlg::OnClickedBtnStartgame() {
	m_gameControl.StartGame();
	m_bPlaying = true;
	if (level == 1) {
		timeCount = 300;
	}
	else if (level == 2) {
		timeCount = 250;
	}
	else {
		timeCount = 200;
	}
	UpdateMap();
	Invalidate(FALSE);
	if (m_bModule == BASIC_MODE) {
		this->SetTimer(1, 1000, NULL);
		this->GetDlgItem(IDC_EDIT_TIME)->EnableWindow(TRUE);
	}
	else if (m_bModule == LEISURE_MODE) {
		// TODO..
	}
	else {
		// TODO..
		CString s;
		cnt++;
		s.Format(_T("第 %d 关"),  cnt);
		this->SetWindowTextW(s);
		
	}
	this->GetDlgItem(IDC_BTN_STARTGAME)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BTN_GAMETIPS)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BTN_RELOADMAP)->EnableWindow(TRUE);

	this->GetDlgItem(IDC_BTN_PAUSEGAME)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BTN_GAMESETTING)->EnableWindow(FALSE);

}


void CGameDlg::setModule(INT module) {
	this->m_bModule = module;
}

void CGameDlg::UpdateWindow()
{
	// TODO: Add your implementation code here.

	CRect rtWin;
	CRect rtClient;

	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);

	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);

	CenterWindow();
}


void CGameDlg::InitElement()
{
	// TODO: Add your implementation code here.

	CClientDC dc(this);

	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElement.CreateCompatibleDC(&dc);

	m_dcElement.SelectObject(hBmp);


	//load the source of mask
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);

	m_dcMask.SelectObject(hMask);
}


void CGameDlg::UpdateMap() {
	//计算图片的顶点坐标与图片大小
	int x = m_ptGameTop.x;
	int y = m_ptGameTop.y;
	int width = m_sizeElem.cx;
	int height = m_sizeElem.cy;

	int nRows = MAX_ROW;
	int nCols = MAX_COL;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			int nVal = m_gameControl.GetElement(i, j);
			if (nVal == BLANK) {
				continue;
			}
			m_dcMem.BitBlt(x + j * width, y + i * height, width, height,
				&m_dcMask, 0, nVal * height, SRCPAINT);
			m_dcMem.BitBlt(x + j * width, y + i * height, width, height,
				&m_dcElement, 0, nVal * height, SRCAND);

		}
	}
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (m_bPause) {
		return;
	}

	//judge wheather the point in the gamemap
	int x = point.x;
	int y = point.y;

	if (y<m_rtGameRect.top || y>m_rtGameRect.bottom || x<m_rtGameRect.left || x>m_rtGameRect.right) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int row = (y - m_ptGameTop.y) / m_sizeElem.cy;
	int col = (x - m_ptGameTop.x) / m_sizeElem.cx;
	if (!m_gameControl.IsValidPoint(row, col)) {
		return;
	}

	// 
	if (m_bFirstPoint) {
		DrawTipFrame(row, col);
		m_gameControl.SetFirstPoint(row, col);
		m_bFirstPoint = false;
	}
	else {
		DrawTipFrame(row, col);
		m_gameControl.SetSecondPoint(row, col);
		Vertex avPath[MAX_VERTEX_NUM];
		int nVexNum = 0;
		if (m_gameControl.Link(avPath, nVexNum)) {
			DrawTipLine(avPath, nVexNum);
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
		m_bFirstPoint = true;

		if (m_gameControl.IsWin()) {
			MessageBox(_T("恭喜你获胜了！"));
			
			m_bPlaying = false;

			ofstream out;
			out.open("input.txt", ios::app);
			out << timeCount << " " << level << endl;
			out.close();


			return;
		}

	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);

}

void CGameDlg::DrawTipLine(Vertex avPath[4], int nVexNum)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);

	for (int i = 1; i < nVexNum; i++) {
		dc.LineTo(m_ptGameTop.x + avPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

void CGameDlg::GetNode(int& time, int& l)
{
	time = timeCount;
	l = level;
	
}



void CGameDlg::OnClickedBtnReloadmap()
{
	// TODO: Add your control notification handler code here

	m_gameControl.Reoriganize();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
	m_bFirstPoint = true;
}


void CGameDlg::OnClickedBtnGametips()
{
	// TODO: Add your control notification handler code here

	Vertex avPath[MAX_VERTEX_NUM];
	int nVexNum = 0;
	if (m_gameControl.GetGameHelp(avPath, nVexNum)) {
		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);
		//画第一个点的提示框
		DrawTipFrame(avPath[nVexNum - 1].row, avPath[nVexNum - 1].col);
		//画提示线
		DrawTipLine(avPath, nVexNum);
		Sleep(500);    //延迟
		UpdateMap();	//更新地图
		InvalidateRect(m_rtGameRect, FALSE);
	}
	else {
		MessageBox(_T("没有找到路径请进行重排"));
	}
}


void CGameDlg::OnClickedBtnPausegame()
{
	// TODO: Add your control notification handler code here
	if (m_bFirstEnterPause) {
		this->GetDlgItem(IDC_BTN_STARTGAME)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BTN_GAMETIPS)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BTN_RELOADMAP)->EnableWindow(FALSE);
		m_bPause = true;
		m_bFirstEnterPause = false;
	}
	else {
		m_bPause = false;
		m_bFirstEnterPause = true;
		this->GetDlgItem(IDC_BTN_GAMETIPS)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_BTN_RELOADMAP)->EnableWindow(TRUE);

	}

}


void CGameDlg::OnClickedBtnGamesetting()
{
	// TODO: Add your control notification handler code here

	CGameSetingDlg dlg;
	dlg.DoModal();

	level = dlg.m_bLevel;
	
	
}


void CGameDlg::OnClickedBtnHelpingame()
{
	// TODO: Add your control notification handler code here

	MessageBox(_T("帮助栏\n"
		"1)游戏开始之后不可重新开始只可重新排列图案\n"
		"2)点击暂停游戏使游戏中断，暂停时不可点击提示和重排按键，可再次点击暂停游戏继续游戏\n"
		"3)点击提示按钮可以显示一个自上而下的第一对可连接的图案\n"
		"4)点击重排可对剩下图形进行随机重排序，其中已消除方块不会重新出现"));
}


void CGameDlg::OnChangeEditTime()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1 && m_bPause == false) {
		if (timeCount > -1) {
			CString s;
			s.Format(_T("%d"), timeCount);
			SetDlgItemText(IDC_EDIT_TIME, s);
			UpdateData(false);
			--timeCount;
			if (m_gameControl.IsWin()) {
				KillTimer(1);
				CString s;
				s.Format(_T("%d"), 0);
				SetDlgItemText(IDC_EDIT_TIME, s);
				UpdateData(false);
				InvalidateRect(FALSE);
				this->GetDlgItem(IDC_BTN_STARTGAME)->EnableWindow(TRUE);
				this->GetDlgItem(IDC_BTN_GAMETIPS)->EnableWindow(FALSE);
				this->GetDlgItem(IDC_BTN_RELOADMAP)->EnableWindow(FALSE);
				this->GetDlgItem(IDC_BTN_PAUSEGAME)->EnableWindow(FALSE);
			}
			if (timeCount == 0) {

				KillTimer(1);
				CString s;
				s.Format(_T("%d"), 0);
				SetDlgItemText(IDC_EDIT_TIME, s);
				UpdateData(FALSE);
				
				m_gameControl.Lose();
				
				UpdateMap();
				InvalidateRect(m_rtGameRect, false);
				this->GetDlgItem(IDC_BTN_STARTGAME)->EnableWindow(TRUE);
				this->GetDlgItem(IDC_BTN_GAMETIPS)->EnableWindow(FALSE);
				this->GetDlgItem(IDC_BTN_RELOADMAP)->EnableWindow(FALSE);
				this->GetDlgItem(IDC_BTN_PAUSEGAME)->EnableWindow(FALSE);
				this->GetDlgItem(IDC_BTN_SETTING)->EnableWindow(TRUE);
				MessageBox(
					_T("很遗憾超时了")
				);
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
