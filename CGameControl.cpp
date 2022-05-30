#include "pch.h"
#include"CGameControl.h"
#include"global.h"
#include<iostream>



int CGameControl::s_nRows = MAX_ROW;
int CGameControl::s_nCols = MAX_COL;
int CGameControl::s_nPicNum = MAX_PIC_NUM;

CGameControl::CGameControl() {
	m_pGameMap = nullptr;
}

void CGameControl::StartGame() {
	m_pGameMap = m_GameLogic.InitMap();
}

int CGameControl::GetElement(int nRow, int nCol) {
	return m_pGameMap[nRow][nCol];
}

CGameControl::~CGameControl()
{
	m_GameLogic.ReleaseMap(m_pGameMap);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}

void CGameControl::Reoriganize()
{
	m_GameLogic.Reoriganize(m_pGameMap);
	
}

void CGameControl::SetSecondPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

bool CGameControl::GetGameHelp(Vertex avPath[4],int & nVexNum)
{
	if (m_GameLogic.FindHelpPath(m_pGameMap)) {
		nVexNum = m_GameLogic.GetVexPath(avPath);
		m_GameLogic.ClearStack();
		return true;
	}
	return false;
}


bool CGameControl::Link(Vertex avPath[4], int& nVexNum)
{
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col) {
		return false;
	}
	int nInfo1 = m_pGameMap[m_svSelFst.row][m_svSelFst.col];
	int nInfo2 = m_pGameMap[m_svSelSec.row][m_svSelSec.col];
	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
		return false;
	}

	if (m_GameLogic.IsLink(m_pGameMap, m_svSelFst, m_svSelSec)) {
		
		//clear the selected picture in gamemap
		m_GameLogic.Clear(m_pGameMap, m_svSelFst, m_svSelSec);		
		//copy the path to avPath
		nVexNum = m_GameLogic.GetVexPath(avPath);
		// clear the CGameLogic's avPath 
		m_GameLogic.ClearStack();

		return true;
	}

	return false;

}

bool CGameControl::IsValidPoint(int row, int col) {
	return m_pGameMap[row][col] != BLANK;
}

bool CGameControl::IsWin(void)
{
	//return m_GameLogic.IsBlank(m_Graph)
	return m_GameLogic.IsBlank(m_pGameMap);
}

void CGameControl::Lose()
{
	m_GameLogic.ClearMap(m_pGameMap);
	
}



