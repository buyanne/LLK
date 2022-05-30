#pragma once
#include"pch.h"
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

public:

	void InitMap(CGraph& g);
	// TODO
	void UpdateArc(CGraph& g, int nRow, int nCol);

	bool IsLink(CGraph& g, Vertex v1, Vertex v2);
	void Clear(CGraph& g, Vertex v1, Vertex v2);
	bool SearchPath(CGraph& g, int nV0, int nV1);
	bool IsExsit(int nVi);
	bool IsCornor();
	void PushVertex(int nV);
	void PopVertexGraph(void);
	bool IsBlank(CGraph& g);
	bool SearchHelpPath(CGraph& g);
	void ResetGraph(CGraph& g);
public:
	int m_nVexNum;

	int m_nCorner;

	Vertex m_avPath[100];

	int m_anPath[100];
public:
	int** InitMap();
	void ReleaseMap(int**& pGameMap);
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);
	void Clear(int** pGameMap, Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[4]);
	//clear the path array
	void ClearStack();
	bool IsBlank(int** pGameMap);
	void Reoriganize(int** pGameMap);
	bool FindHelpPath(int **pGameMap);
	void ClearMap(int** pGameMap);
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol);
	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2);
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);
	void PushVertex(Vertex v);
	void PopVertex();
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2);

};

