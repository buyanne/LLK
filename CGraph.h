#pragma once


class CGraph
{
public:
	CGraph();
	~CGraph();

	int AddVertex(int info);
	int GetVertex(int nIndex);
	void AddArc(int nV1Index, int nV2Index);
	bool GetArc(int nV1index, int nV2Index);
	void UPdateVertex(int nIndex, int info);
	int GetVexNum();
	void ClearGraph();
	void ChangeVertex(int nIndex1, int nIndex2);

	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
protected:
	Vertices m_Vertices;
	AdjMatrix m_AdjMatrix;
	int m_nVexNum;
	int m_nArcNum;

protected:
	void InitGraph(void);
};

