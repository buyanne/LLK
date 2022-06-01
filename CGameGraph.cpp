#include "CGameGraph.h"
#include"pch.h"

CGameGraph::CGameGraph()
{
	m_nVexNum = 0;
	m_nCorner = 0;
	m_nArcNum = 0;
	m_nStackVexNum = 0;
	InitGraph();
}

CGameGraph::~CGameGraph()
{
}

void CGameGraph::InitGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = 0;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}
}

void CGameGraph::InitMap()
{
	int pGameMap[MAX_VERTEX_NUM];

	for (int i = 0; i < MAX_PIC_NUM; i++) {
		for (int j = 0; j < REPEAT_NUM; j++) {
			pGameMap[i * REPEAT_NUM + j] = i;
		}
	}

	srand((int)time(NULL));


	for (int i = 0; i < 200; i++) {
		int index1 = rand() % MAX_VERTEX_NUM;

		int index2 = rand() % MAX_VERTEX_NUM;

		int temp = pGameMap[index1];
		pGameMap[index1] = pGameMap[index2];
		pGameMap[index2] = temp;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		AddVertex(pGameMap[i]);
	}

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(i, j);
		}
	}
}

void CGameGraph::ReleaseMap()
{
}

void CGameGraph::Clear(Vertex v1, Vertex v2)
{
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;
	//更新顶点
	UpdateVertex(nIndex1, BLANK);
	UpdateVertex(nIndex2, BLANK);
	//更新边的信息
	UpdateArc( v1.row, v1.col);
	UpdateArc( v2.row, v2.col);
}

void CGameGraph::ClearMap()
{
	int nVexNum = nRows * nCols;
	for (int i = 0; i < nVexNum; i++) {
		m_Vertices[i] = BLANK;
	}
}

void CGameGraph::ClearStack()
{
	m_nStackVexNum = 0;
	m_nCorner = 0;
}

bool CGameGraph::IsLink(Vertex v1, Vertex v2)
{
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	//压入第一个点
	PushVertex(nIndex1);
	//如果两个点有边，可以相连
	if (SearchValidPath(nIndex1, nIndex2)) {
		PushVertex(nIndex2);
		return true;
	}
	PopVertex();
	return false;
}

bool CGameGraph::IsBlank()
{
	for (int i = 0; i < m_nVexNum; i++) {
		if (GetVertex(i) != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameGraph::SearchValidPath(int nV0, int nV1)
{
	//得到顶点数
	int nVexnum = m_nVexNum;
	//遍历图中nV0行，从0列到nVexnum列，值为true的点
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (GetArc(nV0, nVi) && !IsExist(nVi))
		{
			//压入当前顶点，假设为路径的一个有效顶点
			PushVertex(nVi);
			//当拐点数大于2 时，直接放弃该顶点
			if (m_nCorner > 2)
			{
				PopVertex();          //取出压入的顶点，与PushWertex(nVi)对应
				continue;
			}
			//当前顶点不是nVi时，继续搜寻下一个相邻且连通的顶点
			if (nVi != nV1)
			{
				//当中间顶点不为空时，表示该条路径不通
				if (GetVertex(nVi) != BLANK)
				{
					PopVertex();      //取出压入的顶点，与PushWertex(nVi)对应
					continue;
				}
				//如果nVi是一个已消除的点，则判断（nVi，nV1）是否连通
				if (SearchValidPath(nVi, nV1))
				{
					//SearchPath(garph, nVi, nV1) == true,表示已经找到一条连通路径，则返回true
					return true;
				}
			}
			else
			{
				return true;
			}

			PopVertex();     //取出压入的顶点，与PushWertex(nVi)对应
		}
	}
	return false;
}

bool CGameGraph::SearchHelpPath()
{
	//得到顶点数
	int nVexnum = m_nVexNum;
	for (int i = 0; i < nVexnum; i++)
	{
		//得到第一个非空顶点
		if (GetVertex(i) == BLANK)
		{
			continue;
		}
		//遍历得到第二个同色顶点
		for (int j = 0; j < nVexnum; j++)
		{
			if (i == j) {
				continue;
			}
			//如果第i个点和第j个点同色
			if (GetVertex(i) == GetVertex(j))
			{
				//压入第一个点
				PushVertex(i);
				if (SearchValidPath(i, j) == true)
				{
					return true;
				}
				//取出压入的顶点时，与PushVertex(i)对应
				PopVertex();
			}
		}
	}
	return false;
}

void CGameGraph::ResetGraph()
{
	//随机交换顶点数组中两个顶点的值
	for (int i = 0; i < 2000; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		//交换两个数值
		ChangeVertex(nIndex1, nIndex2);
	}

	//更新弧信息
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			UpdateArc( i, j);
		}
	}
}

int CGameGraph::GetVexPath(Vertex avPath[4])
{
	Vertex point;
	for (int i = 0; i < m_nStackVexNum; i++)
		for (point.col = 0; point.col < MAX_COL; point.col++)
		{
			for (point.row = 0; point.row < MAX_ROW; point.row++)
			{
				if (point.row * MAX_COL + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}
	return m_nStackVexNum;
}

void CGameGraph::PushVertex(int nIndex)
{
	m_anPath[m_nStackVexNum] = nIndex;
	m_nStackVexNum++;
	//判断是否形成新的拐点
	if (IsCorner())
	{
		m_nCorner++;
	}
}

void CGameGraph::PopVertex()
{
	if (IsCorner()) {
		m_nCorner--;
	}
	m_nStackVexNum--;
}

int CGameGraph::AddVertex(int info)
{
	if (m_nVexNum >= MAX_VERTEX_NUM) {
		return 0;
	}
	m_Vertices[m_nVexNum] = info;
	m_nVexNum++;
	return m_nVexNum;
}

void CGameGraph::AddArc(int nIndex1, int nIndex2)
{
	m_AdjMatrix[nIndex1][nIndex2] = true;
	m_AdjMatrix[nIndex2][nIndex1] = true;
}

void CGameGraph::UpdateVertex(int index, int info)
{
	m_Vertices[index] = info;
}

void CGameGraph::UpdateArc(int nRow, int nCol)
{
	int nIndex1 = nRow * MAX_COL + nCol;
	if (nCol > 0)   //左边相邻
	{
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = GetVertex(nIndex1);
		int nInfo2 = GetVertex(nIndex2);
		//判断与左边相邻的是否有关系
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			AddArc(nIndex1, nIndex2);
		}
	}
	if (nCol < MAX_COL - 1)   //右边相邻
	{
		int nV2Index = nIndex1 + 1;
		int nV1Info = GetVertex(nIndex1);
		int nV2Info = GetVertex(nV2Index);

		//判断与右边相邻的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			AddArc(nIndex1, nV2Index);
		}
	}
	if (nRow > 0)   //正上方相邻
	{
		int nV2Index = nIndex1 - MAX_COL;
		int nV1Info = GetVertex(nIndex1);
		int nV2Info = GetVertex(nV2Index);

		//判断与正上方的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			AddArc(nIndex1, nV2Index);
		}
	}
	if (nRow < MAX_ROW - 1)   //正下方相邻
	{
		int nV2Index = nIndex1 + MAX_COL;
		int nV1Info = GetVertex(nIndex1);
		int nV2Info = GetVertex(nV2Index);

		//判断与正下方的是否有关系
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			AddArc(nIndex1, nV2Index);
		}
	}
}

int CGameGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

int CGameGraph::GetElement(int row, int col)
{
	return GetVertex(row * MAX_COL + col);
}

bool CGameGraph::GetArc(int nIndex1, int nIndex2)
{
	return m_AdjMatrix[nIndex1][nIndex2];
}

bool CGameGraph::IsExist(int nVi)
{
	for (int i = 0; i < m_nStackVexNum; i++) {
		if (m_anPath[i] == nVi) {
			return true;
		}
	}
	return false;
}

void CGameGraph::ChangeVertex(int nIndex1, int nIndex2)
{
	int temp = m_Vertices[nIndex1];
	m_Vertices[nIndex1] = m_Vertices[nIndex2];
	m_Vertices[nIndex2] = temp;
}

bool CGameGraph::IsCorner()
{
	//判断最近加入栈的三个节点是否存在拐点
	if (m_nStackVexNum >= 3)
	{
		if ((m_anPath[m_nStackVexNum - 1] + m_anPath[m_nStackVexNum - 3]) / 2 != m_anPath[m_nStackVexNum - 2])
		{
			return true;
		}
	}
	return false;
}
