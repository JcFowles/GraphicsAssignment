//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CMesh.h 
// Description : Contains the header file for Mesh Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

#pragma once

//Local Includes
#include "Polygon.h"

class CPolygon;
class CMesh
{
public:
	// Member Functions
	CMesh();
	~CMesh();
	void Release();

	void AddPolygon(CPolygon* _pPolygon);
	vector<CPolygon>* GetPolygons();
	vector<CVertex> GetVertices();

	void Draw(IDirect3DDevice9* _pD3DDevice);

	void SetVertices();

	void ReadyVertexBuffer(IDirect3DDevice9* _pD3DDevice);
	
private:
	// Member Variables
	vector<CPolygon> m_vecPolygons;
	vector<CVertex> m_vectAllVertices;
	IDirect3DVertexBuffer9* m_pD3DVertexBuffer;
};
