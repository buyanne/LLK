#include "pch.h"
#include "CGraph.h"

CGraph::CGraph()
{
    InitGraph();
}

CGraph::~CGraph()
{
}

int CGraph::AddVertex(int info)
{
    if (m_nVexNum >= MAX_VERTEX_NUM) {
        return 0;
    }
    m_Vertices[m_nVexNum] = info;
    m_nVexNum++;
    return m_nVexNum;

}

int CGraph::GetVertex(int nIndex)
{
    return m_Vertices[nIndex];
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
    m_AdjMatrix[nV1Index][nV2Index] = m_AdjMatrix[nV2Index][nV1Index] = true;
}

bool CGraph::GetArc(int nV1index, int nV2Index)
{
    return m_AdjMatrix[nV1index][nV2Index];
}

void CGraph::UPdateVertex(int nIndex, int info)
{
    m_Vertices[nIndex] = info;
}

int CGraph::GetVexNum()
{
    return m_nVexNum;
}

void CGraph::ClearGraph()
{
    InitGraph();
}

void CGraph::ChangeVertex(int nIndex1, int nIndex2)
{
    int nTemp = m_Vertices[nIndex1];
    m_Vertices[nIndex1] = m_Vertices[nIndex2];
    m_Vertices[nIndex2] = nTemp;
}

void CGraph::InitGraph(void)
{
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        m_Vertices[i] = -1;
    }

    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        for (int j = 0; j< MAX_VERTEX_NUM; j++) {
            m_AdjMatrix[i][j] = false;
        }
    }

}
