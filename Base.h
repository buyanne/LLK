#pragma once
class Base
{
public:
	Base();
	~Base();
public:
	int nRows;
	int nCols;
	int nPicNum;

	virtual void InitMap(); 

	virtual void ReleaseMap();

	virtual void Clear(Vertex v1,Vertex v2);

	virtual bool IsLink(Vertex v1, Vertex v2);

	virtual bool IsBlank();

	virtual bool SearchHelpPath();

	virtual bool SearchPath(int nIndex1,int nIndex2);

	virtual void ResetGraph();

	virtual int GetVexPath(Vertex avPath[4]);

	virtual int GetElement(int nRow, int nCol);

	virtual void ClearStack();

	virtual int AddVertex(int info);

	virtual void UpdateVertex(int nIndex, int info);

	virtual int GetVertex(int nIndex);

	virtual void AddArc(int nV1Index,int nV2Index);

	virtual void UpdateArc(int row, int col);

	
};

