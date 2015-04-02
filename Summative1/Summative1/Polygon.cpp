//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CPolygon.h 
// Description : Contains the main funtionality of Polygon Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

//This Include
#include "Polygon.h"

/***********************
* CPolygon: Defualt Constructor of the Polygon 
* @author: Jc Fowles
* @return: 
********************/
CPolygon::CPolygon()
{
}

/***********************
* CPolygon: Defualt Constructor of the Polygon 
* @author: Jc Fowles
* @return: 
********************/
CPolygon::CPolygon(CVertex* _pVertA, CVertex* _pVertB, CVertex* _pVertC)
{
	m_vecVertices.push_back(*_pVertA);
	m_vecVertices.push_back(*_pVertB);
	m_vecVertices.push_back(*_pVertC);
}

/***********************
* ~CPolygon: Destructor of the Polygon
* @author: Jc Fowles
* @return: 
********************/
CPolygon::~CPolygon()
{
}

/***********************
* AddVertex: Adds a vertex to the polygon
* @author: Jc Fowles
* @parameter: _pVert: Pointer to the vertex to be added
* @return: void
********************/
void CPolygon::AddVertex(CVertex* _pVert)
{
	//only adds 3 points(triangls)
	if (m_vecVertices.size() < 3)
	{
		m_vecVertices.push_back(*_pVert);
	}
}

/***********************
* GetVertices: Gets the sets of vertices of the polygon
* @author: Jc Fowles
* @return: vector<CVertex>*: a pointer to the set of vertices
********************/
vector<CVertex>* CPolygon::GetVertices()
{
	return &m_vecVertices;
}
