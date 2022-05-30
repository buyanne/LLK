#include "pch.h"
#include <vector>

bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2) {
	PushVertex(v1);
	if (v1.row == v2.row) {
		if (LinkInRow(pGameMap, v1, v2)) {
			PushVertex(v2);
			return true;
		}
	}
	if (v1.col == v2.col) {
		if (LinkInCol(pGameMap, v1, v2)) {
			PushVertex(v2);
			return true;
		}
	}
	if (OneCornerLink(pGameMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}

	if (TwoCornerLink(pGameMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}

	PopVertex();
	return false;
}

void CGameLogic::Clear(int** pGameMap, Vertex v1, Vertex v2)
{

	pGameMap[v1.row][v1.col] = BLANK;
	pGameMap[v2.row][v2.col] = BLANK;

}

void CGameLogic::Clear(CGraph& g, Vertex v1, Vertex v2)
{
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	g.UPdateVertex(nIndex1, BLANK);
	g.UPdateVertex(nIndex2, BLANK);

	UpdateArc(g, v1.row, v1.col);
	UpdateArc(g, v2.row, v2.col);
}



bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1)
{
	int nVexNum = g.GetVexNum();
	for (int nVi = 0; nVi < m_nVexNum; nVi++) {
		if (g.GetArc(nV0, nVi) && !IsExsit(nVi)) {
			PushVertex(nVi);
			if (m_nCorner > 2) {
				PopVertexGraph();
				continue;
			}

			if (nVi != nV1) {
				if (g.GetVertex(nVi) != BLANK) {
					PopVertexGraph();
					continue;
				}
				if (SearchPath(g, nVi, nV1)) {
					return true;
				}
			}
			else {
				return true;
			}
		}

		return false;
	}

	return false;
}

bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++) {
		if (m_anPath[i] == nVi) {
			return true;
		}
	}
	return false;
}


void CGameLogic::PushVertex(int nV)
{
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;
	if (IsCornor()) {
		m_nCorner++;
	}
}

bool CGameLogic::IsCornor()
{
	if (m_nVexNum >= 3) {
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2]) {
			return true;
		}
	}
	return false;
}

void CGameLogic::PopVertexGraph(void)
{
	if (IsCornor()) {
		m_nCorner--;
	}
	m_nVexNum--;
}

bool CGameLogic::IsBlank(CGraph& g)
{
	int nVexNum = g.GetVexNum();
	for (int i = 0; i < nVexNum; i++) {
		if (g.GetVertex(i) != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogic::SearchHelpPath(CGraph& g)
{
	int nVexNum = g.GetVexNum();

	for (int i = 0; i < nVexNum; i++) {
		if (g.GetVertex(i) == BLANK) {
			continue;
		}
		for (int j = 0; j < nVexNum; j++) {
			if (i == j) {
				continue;
			}
			if (g.GetVertex(i) == g.GetVertex(j)) {
				PushVertex(i);
				if (SearchPath(g, i, j)) {
					return true;
				}
				PopVertexGraph();
			}
		}
	}

	return false;

}

void CGameLogic::ResetGraph(CGraph& g)
{
	srand((int)time(NULL));
	for (int i = 0; i < 200; i++) {
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		g.ChangeVertex(nIndex1, nIndex2);
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(g, i, j);
		}
	}
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;
	return LineX(pGameMap, nRow, nCol1, nCol2) && v1.info == v2.info;
}

bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;
	return LineY(pGameMap, nRow1, nRow2, nCol) && v1.info == v2.info;
}

bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol)
{
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}

	for (int i = nRow1 + 1; i < nRow2; i++) {
		if (pGameMap[i][nCol] != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2)
{
	if (nCol1 > nCol2) {
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}

	for (int j = nCol1 + 1; j < nCol2; j++) {
		if (pGameMap[nRow][j] != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	if (pGameMap[v1.row][v2.col] == BLANK) {
		if (LineY(pGameMap, v1.row, v2.row, v2.col) 
			&& LineX(pGameMap, v1.row, v1.col, v2.col)
			&&v1.info==v2.info) {
			Vertex v = { v1.row,v2.col,BLANK };
			PushVertex(v);
			return true;
		}
	}
	if (pGameMap[v2.row][v1.col] == BLANK) {
		if (LineY(pGameMap, v1.row, v2.row, v1.col) 
			&& LineX(pGameMap, v2.row, v1.col, v2.col)
			&&v1.info==v2.info) {
			Vertex v = { v2.row,v1.col,BLANK };
			PushVertex(v);
			return true;
		}
	}

	return false;
}

CGameLogic::CGameLogic() {
	m_nVexNum = 0;
}

CGameLogic::~CGameLogic()
{
	
}

int** CGameLogic::InitMap() {
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

	int** pGameMap = new int* [nRows];

	if (nullptr == pGameMap) {
		throw new CGameException(_T("内存操作异常！\n"));
	}
	else {
		for (int i = 0; i < nRows; i++) {
			pGameMap[i] = new int[nCols];
			if (nullptr == pGameMap[i]) {
				throw new CGameException(_T("内存操作异常！\n"));
			}
			memset(pGameMap[i], 0, sizeof(int) * nCols);
		}
	}

	//if the color is not matching the map
	if ((nRows * nCols % (nPicNum * 2) != 0)) {
		ReleaseMap(pGameMap);
		throw new CGameException(_T("游戏花色和地图大小不匹配！\n"));
	}

	//Each Picture's number
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;

	//Init the map with different color sign 
	for (int i = 0; i < nPicNum; i++) {
		for (int j = 0; j < nRepeatNum; j++) {

			pGameMap[nCount / nCols][nCount % nCols] = i;
			nCount++;
		}
	}

	srand((int)time(NULL));

	//that is Picture number
	int nVertexNum = nRows * nCols;
	// random swap two vertexs info
	for (int i = 0; i < nVertexNum; i++) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;


		int nTemp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];

		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTemp;
	}

	return pGameMap;
}
void CGameLogic::InitMap(CGraph& g) {
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;


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

	srand((unsigned int)time(NULL));

	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		int nTemp = pGameMap[nIndex1];
		pGameMap[nIndex1] = pGameMap[nIndex2];
		pGameMap[nIndex2] = nTemp;
	}

	for (int i = 0; i < nVertexNum; i++) {
		g.AddVertex(pGameMap[i]);
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(g, i, j);
		}
	}
}

void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol)
{
	int nV1index = nRow * nCol + nCol;
	if (nCol > 0) {
		int nV2Index = nV1index - 1;
	}
}

void CGameLogic::ReleaseMap(int**& pGameMap) {
	
	int nRows = CGameControl::s_nRows;
	if (pGameMap == nullptr) {
		return;
	}
	for (int i = 0; i < nRows; i++) {
		if (pGameMap[i] == nullptr) {
			continue;
		}
		delete[]pGameMap[i];
	}
	
	delete[] pGameMap;

}

bool CGameLogic::IsLink(CGraph& g, Vertex v1, Vertex v2)
{
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	if (SearchPath(g, nIndex1, nIndex2) == true) {
		PushVertex(nIndex2);
		return true;

	}
	PopVertexGraph();

	return false;
}

void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNum++] = v;
}

void CGameLogic::PopVertex()
{
	m_nVexNum--;
}

void CGameLogic::ClearStack()
{
	memset(m_avPath, 0, sizeof(m_avPath));
	m_nVexNum = 0;
}

bool CGameLogic::IsBlank(int** pGameMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++) {
		for (int j = 0; j < CGameControl::s_nCols; j++) {
			if (pGameMap[i][j] != BLANK) {
				return false;
			}
		}
	}

	return true;
}

void CGameLogic::Reoriganize(int** pGameMap)
{
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nVertexNum = nRows * nCols;
	srand((unsigned int)time(NULL));
	// random swap two vertexs info
	for (int i = 0; i < nVertexNum; i++) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;


		int nTemp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];

		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTemp;
	}
}

bool  CGameLogic::FindHelpPath(int** pGameMap)
{

	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;

	bool** vis = new bool* [nRows];
	for (int i = 0; i < nRows; i++) {
		vis[i] = new bool[nCols];
		memset(vis[i], false, sizeof(bool) * nCols);
	}
	

	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			Vertex v1(i, j, pGameMap[i][j]);
			if (v1.info == BLANK) {
				continue;
			}
			for (int k = 0; k < nRows; k++) {
				for (int l = 0; l < nCols; l++) {
					Vertex v2(k, l, pGameMap[k][l]);
					if ((i==k&&j==l	)||v2.info==BLANK) {
						continue;
					}
					else {
						if (IsLink(pGameMap, v1, v2)) {
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void CGameLogic::ClearMap(int** pGameMap) {
	for (int i = 0; i < CGameControl::s_nRows; i++) {
		for (int j = 0; j < CGameControl::s_nCols; j++) {
			pGameMap[i][j] = BLANK;
		}
	}
}

bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	for (int nCol = 0; nCol < CGameControl::s_nCols; nCol++) {
		if (pGameMap[v1.row][nCol] == BLANK && pGameMap[v2.row][nCol] == BLANK) {
			if (LineY(pGameMap, v1.row, v2.row, nCol)) {
				if (LineX(pGameMap, v1.row, v1.col, nCol) 
					&& LineX(pGameMap, v2.row, v2.col, nCol)
					&&v1.info==v2.info) {
					Vertex _v1 = { v1.row,nCol,BLANK };
					Vertex _v2 = { v2.row,nCol,BLANK };
					PushVertex(_v1);
					PushVertex(_v2);
					return true;
				}
			}
		}
	}

	for (int nRow = 0; nRow < CGameControl::s_nRows; nRow++) {
		if (pGameMap[nRow][v1.col] == BLANK && pGameMap[nRow][v2.col] == BLANK) {
			if (LineX(pGameMap, nRow, v1.col, v2.col)) {
				if (LineY(pGameMap, nRow, v1.row, v1.col) 
					&& LineY(pGameMap, nRow, v2.row, v2.col)
					&&v1.info==v2.info) {
					Vertex _v1 = { nRow,v1.col,BLANK };
					Vertex _v2 = { nRow,v2.col,BLANK };
					PushVertex(_v1);
					PushVertex(_v2);
					return true;
				}
			}
		}
	}
	return false;
}

