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

	virtual int GetElement(int row, int col);

	virtual void ClearStack();

	virtual void UpdateArc(int row,int col);

	virtual int GetVertex(int nIndex);
};

