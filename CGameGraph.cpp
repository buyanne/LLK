#include "pch.h"
#include "CGameGraph.h"

CGameGraph::CGameGraph()
{
	m_nArcNum = 0;
	m_nCorner = 0;
	m_nVexNum = 0;
	InitGraph();
	
}

CGameGraph::~CGameGraph()
{
	ReleaseMap();
}



void CGameGraph::InitGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
}

void CGameGraph::InitMap()
{
	nRows = CGameControl::s_nRows;
	nCols = CGameControl::s_nCols;
	nPicNum = CGameControl::s_nPicNum;

	int* pGameMap;
	pGameMap = new int[nRows * nCols];
	memset(pGameMap, 0, sizeof(pGameMap));

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
	if (m_Vertices != nullptr) {
		delete[] m_Vertices;
	}
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

bool CGameGraph::SearchPath(int nV0, int nV1)
{
	int nVexNum = m_nVexNum;

	for (int nVi = 0; nVi < nVexNum; nVi++) {
		if (GetArc(nV0, nVi) && IsExist(nVi)) {
			PushVertex(nVi);
			if (m_nCorner > 2) {
				PopVertex();
				continue;
			}
			if (nVi != nV1) {
				if (GetVertex(nVi) != BLANK) {
					PopVertex();
					continue;
				}
				if (SearchPath(nVi, nV1)) {
					return  true;
				}
			}
			else {
				return true;
			}
			PopVertex();
		}
	}

	return false;
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
	Vertex point;

	for (int i = 0; i < m_nVexNum; i++) {
		for (point.col = 0; point.col < MAX_COL; point.col++) {
			for (point.row = 0; point.row < MAX_ROW; point.row++) {
				if (point.row * MAX_COL + point.col == m_anPath[i]) {
					avPath[i] = point;
				}
			}
		}
	}
	return m_nVexNum;
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

int CGameGraph::AddVertex(int info)
{
	if (m_nVexNum >= MAX_VERTEX_NUM) {
		return 0;
	}
	m_Vertices[m_nVexNum] = info;
	m_nVexNum++;
	return m_nVexNum;
}

void CGameGraph::AddArc(int nIndex1, int nIndex2)
{
	m_AdjMatrix[nIndex1][nIndex2] = true;

	m_AdjMatrix[nIndex2][nIndex1] = true;
}

void CGameGraph::UpdateVertex(int index, int info)
{
	m_Vertices[index] = info;
}

void CGameGraph::UpdateArc(int nRow, int nCol)
{
	int nIndex1 = nRow * MAX_COL + nCol;

	//左边相邻
	if (nCol > 0) {
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = GetVertex(nIndex1);
		int nInfo2 = GetVertex(nIndex2);
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			AddArc(nIndex1, nIndex2);
		}
	}
	//右边相邻
	if (nCol < MAX_COL - 1) {
		int nV2Index = nIndex1 + 1;
		int nV1Info = GetVertex(nIndex1);
		int nV2Info = GetVertex(nV2Index);

		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK) {
			AddArc(nIndex1, nV2Index);
		}
	}

	//正上方相邻
	if (nRow > 0) {
		int nV2Index = nIndex1 - MAX_COL;
		int nInfo1 = GetVertex(nIndex1);
		int nInfo2 = GetVertex(nV2Index);

		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			AddArc(nIndex1, nV2Index);
		}
	}
	//正下方相邻	
	if (nRow < MAX_ROW - 1) {
		int nIndex2 = nIndex1 + MAX_COL;
		int nInfo1 = GetVertex(nIndex1);
		int nInfo2 = GetVertex(nIndex2);

		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
			AddArc(nIndex1, nIndex2);
		}
	}
}


int CGameGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

int CGameGraph::GetElement(int row, int col)
{
	return GetVertex(row * MAX_COL + col);
}

bool CGameGraph::GetArc(int nIndex1, int nIndex2)
{
	return m_AdjMatrix[nIndex1][nIndex2];
}

bool CGameGraph::IsExist(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++) {
		if (m_anPath[i] == nVi) {
			return true;
		}
	};

	return false;
}

void CGameGraph::ChangeVertex(int nIndex1, int nIndex2)
{
	int temp = m_Vertices[nIndex1];
	m_Vertices[nIndex1] = m_Vertices[nIndex2];
	m_Vertices[nIndex2] = temp;
}

bool CGameGraph::IsCorner()
{
	if (m_nVexNum >= 3) {
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2]) {
			return true;
		}
	}
	return false;
}
