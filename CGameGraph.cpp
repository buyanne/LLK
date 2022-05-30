#include "pch.h"
#include "CGameGraph.h"

CGameGraph::CGameGraph()
{
}

CGameGraph::~CGameGraph()
{
}

void CGameGraph::InitMap()
{
	nRows = CGameControl::s_nRows;
	nCols = CGameControl::s_nCols;
	nPicNum = CGameControl::s_nPicNum;

	int* pGameMap = new int[nRows * nCols];

	if ((nRows * nCols) % (nPicNum * 2) != 0) {
		delete[] pGameMap;
		throw new CGameException(_T("游戏花色与游戏地图大小不匹配"));
	}

	int nRepeatNum = nRows * nCols / nPicNum;

	int nCount = 0;

	for (int i = 0; i < nPicNum; i++) {
		for (int j = 0; j < nRepeatNum; j++) {
			pGameMap[nCount++] = i;
		}
	}

	srand((int)time(NULL));

	int nVertexNum = nRows * nCols;

	for (int i = 0; i < nVertexNum; i++) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		int  temp = pGameMap[nIndex1];
		pGameMap[nIndex1] = pGameMap[nIndex2];
		pGameMap[nIndex2] = temp;
	}

	for (int i = 0; i < nVertexNum; i++) {
		AddVertex(pGameMap[i]);
	}

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(i, j);
		}
	}
}

void CGameGraph::ReleaseMap()
{
	
	
}

void CGameGraph::Clear(Vertex v1, Vertex v2)
{
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	UpdateVertex(nIndex1, BLANK);
	UpdateVertex(nIndex2, BLANK);

	UpdateArc(v1.row, v1.col);
	UpdateArc(v2.row, v2.col);
}

bool CGameGraph::IsLink(Vertex v1, Vertex v2)
{
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	if (SearchPath( nIndex1, nIndex2) == true) {
		PushVertex(nIndex2);
		return true;

	}
	PopVertex();

	return false;
}

bool CGameGraph::IsBlank()
{
	int nVexNum = m_nVexNum;
	for (int i = 0; i < nVexNum; i++) {
		if (GetVertex(i) != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameGraph::SearchHelpPath()
{
	int nVexNum = m_nVexNum;

	for (int i = 0; i < nVexNum; i++) {
		if (GetVertex(i) == BLANK) {
			continue;
		}
		for (int j = 0; j < nVexNum; j++) {
			if (i == j) {
				continue;
			}
			if (GetVertex(i) == GetVertex(j)) {
				PushVertex(i);
				if (SearchPath( i, j)) {
					return true;
				}
				PopVertex();
			}
		}
	}

	return false;
}

void CGameGraph::ResetGraph()
{
	srand((int)time(NULL));
	for (int i = 0; i < 200; i++) {
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		ChangeVertex(nIndex1, nIndex2);
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(i, j);
		}
	}
}

int CGameGraph::GetVexPath(Vertex avPath[4])
{
	return 0;
}

void CGameGraph::PushVertex(int nIndex)
{
	m_anPath[m_nVexNum] = nIndex;
	m_nVexNum++;
	if (IsCorner()) {
		m_nCorner++;
	}
}

void CGameGraph::PopVertex()
{
	if (IsCorner()) {
		m_nCorner--;
	}
	m_nVexNum--;
}

void CGameGraph::ClearStack()
{
	m_nVexNum = 0;
}

int CGameGraph::AddVertex(int info)
{
	if (m_nVexNum >= MAX_VERTEX_NUM) {
		return 0;
	}
	m_Vertices[m_nVexNum] = info;
	m_nVexNum++;
	return m_nVexNum;
}

void CGameGraph::UpdateVertex(int index, int info)
{
}


int CGameGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

void CGameGraph::ChangeVertex(int nIndex1, int nIndex2)
{
}

bool CGameGraph::IsCorner()
{
	return false;
}
