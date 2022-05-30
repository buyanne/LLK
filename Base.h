#pragma once
class Base
{
public:
	Base();
	~Base();
public:
	virtual void InitMap(); 

	virtual void ReleaseMap();

	virtual void Clear(Vertex v1,Vertex v2);

	virtual bool IsLink(Vertex v1, Vertex v2);

	virtual bool IsBlank();

	virtual bool SearchHelpPath();

	void ResetGraph();

	int GetVexPath(Vertex avPath[4]);

};

