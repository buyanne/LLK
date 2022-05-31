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
	//���¶���
	UpdateVertex(nIndex1, BLANK);
	UpdateVertex(nIndex2, BLANK);
	//���±ߵ���Ϣ
	UpdateArc( v1.row, v1.col);
	UpdateArc( v2.row, v2.col);
}

bool CGameGraph::IsLink(Vertex v1, Vertex v2)
{
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;

	//ѹ���һ����
	PushVertex(nIndex1);
	//����������бߣ���������
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
	//�õ�������
	int nVexnum = m_nVexNum;
	//����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (GetArc(nV0, nVi) && !IsExist(nVi))
		{
			//ѹ�뵱ǰ���㣬����Ϊ·����һ����Ч����
			PushVertex(nVi);
			//���յ�������2 ʱ��ֱ�ӷ����ö���
			if (m_nCorner > 2)
			{
				PopVertex();          //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
				continue;
			}
			//��ǰ���㲻��nViʱ��������Ѱ��һ����������ͨ�Ķ���
			if (nVi != nV1)
			{
				//���м䶥�㲻Ϊ��ʱ����ʾ����·����ͨ
				if (GetVertex(nVi) != BLANK)
				{
					PopVertex();      //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
					continue;
				}
				//���nVi��һ���������ĵ㣬���жϣ�nVi��nV1���Ƿ���ͨ
				if (SearchValidPath(nVi, nV1))
				{
					//SearchPath(garph, nVi, nV1) == true,��ʾ�Ѿ��ҵ�һ����ͨ·�����򷵻�true
					return true;
				}
			}
			else
			{
				return true;
			}

			PopVertex();     //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
		}
	}
	return false;
}

bool CGameGraph::SearchHelpPath()
{
	//�õ�������
	int nVexnum = m_nVexNum;
	for (int i = 0; i < nVexnum; i++)
	{
		//�õ���һ���ǿն���
		if (GetVertex(i) == BLANK)
		{
			continue;
		}
		//�����õ��ڶ���ͬɫ����
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				//�����i����͵�j����ͬɫ
				if (GetVertex(i) == GetVertex(j))
				{
					//ѹ���һ����
					PushVertex(i);
					if (SearchValidPath( i, j) == true)
					{
						return true;
					}
					//ȡ��ѹ��Ķ���ʱ����PushVertex(i)��Ӧ
					PopVertex();
				}
			}
		}
	}
	return false;
}

void CGameGraph::ResetGraph()
{
	//��������������������������ֵ
	for (int i = 0; i < 2000; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		//����������ֵ
		ChangeVertex(nIndex1, nIndex2);
	}

	//���»���Ϣ
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
	m_anPath[m_nStackVexNum++] = nIndex;
	if (IsCorner()) {
		m_nCorner--;
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
	if (nCol > 0)   //�������
	{
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = GetVertex(nIndex1);
		int nInfo2 = GetVertex(nIndex2);
		//�ж���������ڵ��Ƿ��й�ϵ
		if (nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			AddArc(nIndex1, nIndex2);
		}
	}
	if (nCol < MAX_COL - 1)   //�ұ�����
	{
		int nV2Index = nIndex1 + 1;
		int nV1Info = GetVertex(nIndex1);
		int nV2Info = GetVertex(nV2Index);

		//�ж����ұ����ڵ��Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			AddArc(nIndex1, nV2Index);
		}
	}
	if (nRow > 0)   //���Ϸ�����
	{
		int nV2Index = nIndex1 - MAX_COL;
		int nV1Info = GetVertex(nIndex1);
		int nV2Info = GetVertex(nV2Index);

		//�ж������Ϸ����Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			AddArc(nIndex1, nV2Index);
		}
	}
	if (nRow < MAX_ROW - 1)   //���·�����
	{
		int nV2Index = nIndex1 + MAX_COL;
		int nV1Info = GetVertex(nIndex1);
		int nV2Info = GetVertex(nV2Index);

		//�ж������·����Ƿ��й�ϵ
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
	if (m_nStackVexNum >= 3) {
		if ((m_anPath[m_nStackVexNum - 1] + m_anPath[m_nStackVexNum - 3]) / 2 != m_anPath[m_nStackVexNum - 2]) {
			return true;
		}
	}

	return false;
}
