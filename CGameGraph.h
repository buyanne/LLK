#pragma once
#include "Base.h"
class CGameGraph :
    public Base
{
public:
    CGameGraph();
  
    ~CGameGraph();

public:

    void InitGraph();

    void InitMap();

    void ReleaseMap();

    void Clear(Vertex v1, Vertex v2);

    bool IsLink(Vertex v1, Vertex v2);

    bool IsBlank();

    bool SearchValidPath(int nIndex1, int nIndex2);

    bool SearchHelpPath();

    void ResetGraph();

    int GetVexPath(Vertex avPath[4]);

    void PushVertex(int nIndex);

    void PopVertex();

    int AddVertex(int info);

    void AddArc(int nIndex1, int nIndex2);

    void UpdateVertex(int index, int info);

    void UpdateArc(int nRow, int nCol);

    int GetVertex(int nIndex);

    int GetElement(int row, int col);

    bool GetArc(int nIndex1, int nIndex2);

    bool IsExist(int nVi);

    void ChangeVertex(int nIndex1, int nIndex2);

    bool IsCorner();


public:
    typedef int Vertices[MAX_VERTEX_NUM];
    typedef bool AdjMatrix[MAX_VERTEX_NUM<<2][MAX_VERTEX_NUM<<2];
public:
    Vertices m_Vertices{};
    AdjMatrix m_AdjMatrix{};
    int m_nVexNum;
    int m_nArcNum;
    int m_nStackVexNum;


    int m_anPath[100];
    int m_nCorner;
};

