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
* GetPolygon: Returns the set of polygon pointers
* @author: Jc Fowles
* @return: vector<CPolygon*>: Returns the Set of polygon pointers that make the mesh
********************/
vector<CVertex> CMesh::GetVertices()
{
	return m_vectAllVertices;
}

/***********************
* Draw: Draws the mesh based on a world matrix
* @author: Jc Fowles
* @parameter: _WorldMatrix: The world matrix to transform the mesh
* @return: void
********************/
void CMesh::Draw(IDirect3DDevice9* _pD3DDevice)
{
	int iNumOfPolygons = (GetVertices().size())/3;
	
	// Set the vertex format
    _pD3DDevice->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));

    //Set the display vertex buffer to our vertex buffer of cube vertices
	_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(CVertex));

    //Draw the vertex buffer into the backbuffer
    _pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, iNumOfPolygons);
}

/***********************
* SetVertices: Sets all the vertices of the polygons into an array of vertices
* @author: Jc Fowles
* @return: void
********************/
void CMesh::SetVertices()
{
	for(unsigned int i = 0; i < m_vecPolygons.size(); i++)
	//Loop through all Meshes Polygons
	{
		for( unsigned int k = 0; k < (*(m_vecPolygons)[i].GetVertices()).size(); k++)
		//Loop through all Polygons Vertices
		{
			m_vectAllVertices.push_back( (*(m_vecPolygons)[i].GetVertices())[k]);
		}
	}
}

/***********************
* ReadyVertexBuffer: Readies the vertex buffer
* @author: Jc Fowles
* @return: IDirect3DVertexBuffer9* : a pointer to the vertex buffer
********************/
void CMesh::ReadyVertexBuffer(IDirect3DDevice9* _pD3DDevice)
{
	SetVertices();
	int iNumOfVetices = GetVertices().size();

	//Create the Vertex buffer
	m_pD3DVertexBuffer = NULL;
	_pD3DDevice->CreateVertexBuffer(iNumOfVetices*sizeof(CVertex), 0, (D3DFVF_XYZ | D3DFVF_DIFFUSE), D3DPOOL_MANAGED, &m_pD3DVertexBuffer, NULL);

    VOID* pVoidPointer;
		
    //Lock the vertex buffer
    m_pD3DVertexBuffer->Lock(0, iNumOfVetices*sizeof(CVertex) , (void**)&pVoidPointer, 0);
	//Load the vertices into vertex buffer
	memcpy(pVoidPointer, &GetVertices().front(), iNumOfVetices*sizeof(CVertex));
	//Unlock the vertex buffer
    m_pD3DVertexBuffer->Unlock();
}