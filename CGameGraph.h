#pragma once
#include "Base.h"
class CGameGraph :
    public Base
{
public:
    CGameGraph();
  
    ~CGameGraph();

public:

    void InitMap();

    void ReleaseMap();

    void Clear(Vertex v1, Vertex v2);

    bool IsLink(Vertex v1, Vertex v2);

    bool IsBlank();

    bool SearchHelpPath();

    void ResetGraph();

    int GetVexPath(Vertex avPath[4]);

    void PushVertex(int nIndex);

    void PopVertex();

    void ClearStack();

    int AddVertex(int info);

    void UpdateVertex(int index, int info);

    int GetVertex(int nIndex);

    void ChangeVertex(int nIndex1, int nIndex2);

    bool IsCorner();


public:
    typedef int Vertices[MAX_VERTEX_NUM];
    typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
public:
    Vertices m_Vertices;
    AdjMatrix m_AdjMatrix;
    int m_nVexNum;
    int m_nArcNum;

    int m_anPath[100];
    int m_nCorner;
    /*int nRows;
    int nCols;
    int nPicNum;*/
};

