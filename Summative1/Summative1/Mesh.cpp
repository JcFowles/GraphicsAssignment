//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CMesh.cpp 
// Description : Contains the main funtionality of Mesh Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

//This Include
#include "Mesh.h"

/***********************
* CMesh: Defualt Constructor of the Mesh 
* @author: Jc Fowles
* @return: 
********************/
CMesh::CMesh()
{

}

/***********************
* ~CMesh: Destructor of the Mesh
* @author: Jc Fowles
* @return: 
********************/
CMesh::~CMesh()
{
}

/***********************
* AddPolygon: Adds a polygon to the mesh
* @author: Jc Fowles
* @parameter: _pPolygon: Pointer to the polygon to be added
* @return: void
********************/
void CMesh::AddPolygon(CPolygon* _pPolygon)
{
	m_vecPolygons.push_back(*_pPolygon);
}

/***********************
* GetPolygon: Returns the set of polygon pointers
* @author: Jc Fowles
* @return: vector<CPolygon*>: Returns the Set of polygon pointers that make the mesh
********************/
vector<CPolygon>* CMesh::GetPolygons()
{
	return &m_vecPolygons;
}

/***********************
* Draw: Draws the mesh based on a world matrix
* @author: Jc Fowles
* @parameter: _WorldMatrix: The world matrix to transform the mesh
* @return: void
********************/
void CMesh::Draw(D3DXMATRIX _WorldMatrix)
{

}