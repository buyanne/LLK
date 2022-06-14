// CGameRankDlg.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameRankDlg.h"
#include <fstream>


// CGameRankDlg dialog

IMPLEMENT_DYNAMIC(CGameRankDlg, CDialogEx)

CGameRankDlg::CGameRankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RANK, pParent)
{

}

CGameRankDlg::~CGameRankDlg()
{
}

void CGameRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}




BEGIN_MESSAGE_MAP(CGameRankDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameRankDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGameRankDlg message handlers


BOOL CGameRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	DWORD dwStyle = m_list.GetExtendedStyle();   //listcontrol����  
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_list.SetExtendedStyle(dwStyle);
	m_list.InsertColumn(0, _T("����"), LVCFMT_CENTER, 120);
	m_list.InsertColumn(1, _T("�÷�"), LVCFMT_CENTER, 110);
	m_list.InsertColumn(2, _T("ʣ��ʱ��"), LVCFMT_CENTER, 110);




	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CGameRankDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	vector <CString>* m_vecMessage = NULL;
	//m_vecMessage = new vector <CString>;//����һ���������������ÿһ����¼
	////�������ݿ�,����������
	//int cnt = 3;
	//CString s;
	//s.Format(_T("%d"),cnt);
	//m_vecMessage->push_back(s);
	//m_vecMessage->push_back(_T("100"));
	//m_vecMessage->push_back(_T("2"));

	//NormalMessageVector(A2W(sTempVaule.c_str()), m_vecMessage); 
	vet.clear();
	string s("input.txt");
	int a, b;
	ifstream in(s);

	while (in >> a >> b) {
		vet.push_back({ a,b });
	}

	sort(vet.begin(), vet.end(), [](pair<int, int> a, pair<int, int> b){
		if (a.first == b.first) {
			return a.second > b.second;
		}
		return a.first > b.first;
		});


	for (int i = 0; i < vet.size(); ++i)
	{
		CString s;
		s.Format(_T("%d"), i + 1);
		m_list.InsertItem(i, s);//������
		s.Format(_T("%d"), vet[i].first);
		m_list.SetItemText(i, 1, s);
		s.Format(_T("%d"), vet[i].second);
		m_list.SetItemText(i, 2, s);

	}

	in.close();
}
