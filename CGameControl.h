#pragma once
#ifndef CGAMECONTROL
#define CGAMECONTROL
#include"CGameLogic.h"
#include "CGraph.h"
#include "Base.h"
#include"CGameMap.h"
#include"CGameGraph.h"

class CGameControl
{
public:
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;

	Base* base = new CGameGraph();

	//CGraph m_graph;

	// the first selected vertex
	Vertex m_svSelFst;
	// the second selected vertex
	Vertex m_svSelSec;

	// the map of game
	/*int** m_pGameMap;
	CGameLogic m_GameLogic;*/

public:
	// construction 
	CGameControl();
	~CGameControl();
public:
	void StartGame();
	int GetElement(int nRow, int nCol);
	void Reoriganize();
	bool GetGameHelp(Vertex avPath[4], int& nVexNum);
	bool IsValidPoint(int row, int col);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecondPoint(int nRow, int nCol);
	bool Link(Vertex avPath[4], int& nVexNum);
	bool IsWin(void);
	void Lose();
};
#endif // !CGAMECONTROL
