#pragma once
#include "Base.h"
class CGameMap :
    public Base
{
public:
    CGameMap();
    ~CGameMap();
public:
    int** pGameMap;
    //int nRows;
    //int nCols;
    //int nPicNum;

public:
    int m_nVexNum;

    Vertex m_avPath[MAX_VERTEX_NUM];

public:
    void InitMap();

    void ReleaseMap();

    void Clear(Vertex v1, Vertex v2);

    bool IsBlank();

    bool SearchHelpPath();

    int GetElement(int nRow, int nCol);

    int GetVexPath(Vertex avPath[4]);
    
    void PushVertex(Vertex v);

    void PopVertex();
    
    void ClearStack();

    bool LineX(int nRow, int nCol1, int nCol2);

    bool LinkInRow(Vertex v1, Vertex v2);

    bool LineY(int nRow1, int nRow2, int nCol);

    bool LinkInCol(Vertex v1, Vertex v2);

    bool OneCornerLink(Vertex v1, Vertex v2);

    bool TwoCornerLink(Vertex v1, Vertex v2);

    bool IsLink(Vertex v1, Vertex v2);

    void ClearMap();

    void ResetGraph();
    


};

