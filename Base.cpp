#include "pch.h"
#include "Base.h"

Base::Base()
{
	nCols = 0;
	nRows = 0;
	nPicNum = 0;
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

int Base::GetElement(int row, int col)
{
	return 0;
}

void Base::ClearStack()
{
}

void Base::UpdateArc(int row,int col)
{
}

int Base::GetVertex(int nIndex)
{
	return 0;
}

