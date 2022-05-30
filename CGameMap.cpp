#include "pch.h"
#include "CGameMap.h"

CGameMap::CGameMap()
{

	InitMap();

	m_nVexNum = 0;
}

CGameMap::~CGameMap()
{
	ReleaseMap();
}
void CGameMap::InitMap() {
	nRows = CGameControl::s_nRows;
	nCols = CGameControl::s_nCols;
	nPicNum = CGameControl::s_nPicNum;

	pGameMap = new int* [nRows];

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
		ReleaseMap();
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
	
}

 void CGameMap::ReleaseMap()
 {
	 if (pGameMap == nullptr) {
		 return;
	 }
	 for (int i = 0; i < nRows; i++) {
		 if (pGameMap[i] = nullptr) {
			 continue;
		 }
		 delete[]pGameMap[i];
	 }
	 delete[] pGameMap;
 }

 void CGameMap::Clear(Vertex v1, Vertex v2)
 {
	 pGameMap[v1.row][v1.col] = BLANK;

	 pGameMap[v2.row][v2.col] = BLANK;
 }

 bool CGameMap::IsLink(Vertex v1, Vertex v2)
 {
	 PushVertex(v1);
	 if (v1.row == v2.row) {
		 if (LinkInRow(v1, v2)) {
			 PushVertex(v2);
			 return true;
		 }
	 }

	 if (v1.col == v2.col) {
		 if (LinkInCol(v1, v2)) {
			 PushVertex(v2);

			 return true;
		}
	 }

	 if (OneCornerLink(v1, v2)) {
		 PushVertex(v2);
		 return true;
	 }

	 if (TwoCornerLink(v1, v2)) {
		 PushVertex(v2);
		 return true;
	 }

	 PopVertex();
	 return false;



	 return false;
 }

 bool CGameMap::IsBlank()
 {
	 for (int i = 0; i < nRows; i++) {
		 for (int j = 0; j < nCols; j++) {
			 if (pGameMap[i][j] != BLANK) {
				 return false;
			 }
		 }
	 }
	 return true;
 }

 bool CGameMap::SearchHelpPath()
 {
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
					 if ((i == k && j == l) || v2.info == BLANK) {
						 continue;
					 }
					 else {
						 if (IsLink( v1, v2)) {
							 return true;
						 }
					 }
				 }
			 }
		 }
	 }

	 return false;
 }

 int CGameMap::GetElement(int nRow, int nCol)
 {
	 return pGameMap[nRow][nCol];
 }


 int CGameMap::GetVexPath(Vertex avPath[4])
 {
	 for (int i = 0; i < m_nVexNum; i++) {
		 avPath[i] = m_avPath[i];
	 }
	 return m_nVexNum;
 }

 void CGameMap::PushVertex(Vertex v)
 {
	 m_avPath[m_nVexNum++] = v;
 }

 void CGameMap::PopVertex()
 {
	 m_nVexNum--;
 }
#include<iostream>
 void CGameMap::ClearStack() {
	 memset(m_avPath, 0, sizeof(m_avPath));
	 m_nVexNum = 0;
 }

 bool CGameMap::LineX(int nRow, int nCol1, int nCol2)
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

 bool CGameMap::LinkInRow(Vertex v1, Vertex v2)
 {
	 int nCol1 = v1.col;
	 int nCol2 = v2.col;
	 int nRow = v1.row;

	 return LineX(nRow, nCol1, nCol2) && v1.info == v2.info;
 }

 bool CGameMap::LineY(int nRow1, int nRow2, int nCol)
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

 bool CGameMap::LinkInCol(Vertex v1, Vertex v2)
 {
	 int nRow1 = v1.row;
	 int nRow2 = v2.row;
	 int nCol = v1.col;

	 return LineY(nRow1, nRow2, nCol) && v1.info == v2.info;
 }

 bool CGameMap::OneCornerLink(Vertex v1, Vertex v2)
 {
	 if (pGameMap[v1.row][v2.col] == BLANK) {
		 if (LineY(v1.row, v2.row, v2.col)
			 &&LineX(v1.row,v1.col,v2.col)
			 &&v1.info==v2.info) {
			 Vertex v = { v1.row,v2.col,BLANK };
			 PushVertex(v);
			 return true;
		 }
	 }
	 if (pGameMap[v2.row][v1.col] == BLANK) {
		 if (LineY(v1.row, v2.row, v1.col)
			 && LineX(v2.row, v1.col, v2.col)
			 && v1.info == v2.info) {
			 Vertex v = { v2.row,v1.col,BLANK };
			 PushVertex(v);

			 return true;
		 }
	 }
	 return false;
 }

 bool CGameMap::TwoCornerLink(Vertex v1, Vertex v2)
 {
	 for (int nCol = 0; nCol < nCols; nCol++) {
		 if (pGameMap[v1.row][nCol] == BLANK && pGameMap[v2.row][nCol] == BLANK) {
			 if (LineY(v1.row, v2.row, nCol)) {
				 if (LineX(v1.row, v1.col, nCol) 
					 && LineX(v2.row, v2.col, nCol)
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

	 for (int nRow = 0; nRow < nRows; nRow++) {
		 if (pGameMap[nRow][v1.col] == BLANK && pGameMap[nRow][v2.col] == BLANK) {
			 if (LineX(nRow, v1.col, v2.col)) {
				 if (LineY(v1.row, nRow, v1.col)
					 && LineY(v2.row, nRow, v2.col)
					 && v1.info == v2.info) {
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

 void CGameMap::ClearMap()
 {
	 for (int i = 0; i < nRows; i++) {
		 for(int j = 0; j < nCols; j++) {
			 pGameMap[i][j] = BLANK;
		 }
	 }
 }

 void CGameMap::ResetGraph()
 {
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


