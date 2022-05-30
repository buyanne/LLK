#include "pch.h"
#include "Base.h"

Base::Base()
{
}

Base::~Base()
{
}

void Base::InitMap()
{
}

void Base::ReleaseMap()
{
}

void Base::Clear(Vertex v1, Vertex v2)
{

}

bool Base::IsLink(Vertex v1, Vertex v2)
{
	return false;
}



bool Base::IsBlank()
{
	return false;
}


bool Base::SearchHelpPath()
{
	return false;
}

bool Base::SearchPath(int nIndex1, int nIndex2)
{
	return false;
}


void Base::ResetGraph()
{
	
}

int Base::GetVexPath(Vertex avPath[4])
{
	return 0;
}

int Base::GetElement(int nRow, int nCol)
{
	return 0;
}

void Base::ClearStack()
{
}

int Base::AddVertex(int info)
{
	return 0;
}

void Base::UpdateVertex(int nIndex, int info)
{
}


int Base::GetVertex(int nIndex)
{
	return 0;
}

void Base::AddArc(int nV1Index, int nV2Index)
{
}

void Base::UpdateArc(int row, int col)
{
}
