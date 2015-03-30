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

// Library Includes
#include <d3dx9.h>
#include <vector>

//Local Includes
#include "Polygon.h"

using namespace std; 

class CPolygon;
class CMesh
{
public:
	// Member Functions
	CMesh();
	~CMesh();

	void AddPolygon(CPolygon* _pPolygon);
	vector<CPolygon>* GetPolygons();

	void Draw(D3DXMATRIX _WorldMatrix);
	
private:
	// Member Variables
	vector<CPolygon> m_vecPolygons;
};
