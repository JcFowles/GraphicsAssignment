//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : Vectex.h 
// Description : Contains the header file for Vectex Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

#pragma once

// Library Includes
#include <d3dx9.h>

class CVertex
{
public:
	// Member Functions

	CVertex();
	CVertex(float _fX, float _fY, float _fZ);
	~CVertex();

	//Getters
	float GetX() const;
	float GetZ() const;
	float GetY() const;
	COLORREF GetColor();

	//Setters
	void SetX(float _f);
	void SetY(float _f);
	void SetZ(float _f);
	void SetColor(int _iR, int _iG, int _iB);
	
protected:
	// Member Variables
	float m_fX;
	float m_fY;
	float m_fZ;

	COLORREF m_color;
};
