//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CPolygon.h 
// Description : Contains the header file for Polygon Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

#pragma once

// Library Includes
#include <vector>

// Local Includes
#include "Vertex.h"

using namespace std; 

class CPolygon
{
public:
	// Member Functions
	CPolygon();
	CPolygon(CVertex* _pVertA, CVertex* _pVertB, CVertex* _pVertC);
	~CPolygon();
		
	void AddVertex(CVertex* _pVert);

	vector<CVertex>* GetVertices();

	void Draw(D3DXMATRIX _WorldMatrix);//based on world matrix
	

private:
	// Member Variables
	vector<CVertex> m_vecVertices;
};
