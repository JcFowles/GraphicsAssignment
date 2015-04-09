//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : Vectex.cpp 
// Description : Contains the main funtionality of Vertex Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

//This Include
#include "Vertex.h"

/***********************
* CVertex: Defualt Constructor of the Vertex 
* @author: Jc Fowles
* @return: 
********************/
CVertex::CVertex()
{
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fZ = 0.0f;
}

/***********************
* CVertex: Overloaded Constructor of the Vertex
* @author: Jc Fowles
* @parameter: _fX: X position of the vertex
* @parameter: _fY: Y position of the vertex
* @parameter: _fZ: Z position of the vertex
* @return: 
********************/
CVertex::CVertex(float _fX, float _fY, float _fZ)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fZ = _fZ;

	COLORREF black = D3DCOLOR_XRGB(0, 0, 0);
	m_color = black;
}

/***********************
* ~CVertex: Destructor of the Vertex
* @author: Jc Fowles
* @return: 
********************/
CVertex::~CVertex()
{

}

/***********************
* GetX: Returns the X coordinate of the position vector
* @author: Jc Fowles
* @return: float: Returns the X coordinate of the position vector as a float
********************/
float CVertex::GetX() const
{
	return m_fX;
}

/***********************
* GetY: Returns the Y coordinate of the position vector
* @author: Jc Fowles
* @return: float: Returns the Y coordinate of the position vector as a float
********************/
float CVertex::GetY() const
{
	return m_fY;
}

/***********************
* GetZ: Returns the Z coordinate of the position vector
* @author: Jc Fowles
* @return: float: Returns the Z coordinate of the position vector as a float
********************/
float CVertex::GetZ() const
{
	return m_fZ;
}

/***********************
* GetColor: Returns the color of the position vector
* @author: Jc Fowles
* @return: COLORREF: Returns the color of the position vector
********************/
COLORREF CVertex::GetColor()
{
	return m_color;
}

/***********************
* SetX: Sets the X coordinate of the position vector
* @author: Jc Fowles
* @parameter: _f: The Float value to be set as the X coordinate
* @return: void
********************/
void CVertex::SetX(float _f)
{
	m_fX = _f;
}

/***********************
* SetY: Sets the Y coordinate of the position vector
* @author: Jc Fowles
* @parameter: _f: The Float value to be set as the Y coordinate
* @return: void
********************/
void CVertex::SetY(float _f)
{
	m_fY = _f;
}

/***********************
* SetZ: Sets the Z coordinate of the position vector
* @author: Jc Fowles
* @parameter: _f: The Float value to be set as the Z coordinate
* @return: void
********************/
void CVertex::SetZ(float _f)
{
	m_fZ = _f;
}

/***********************
* SetColor: Sets the color of the position vector
* @author: Jc Fowles
* @parameter: _iR: The Red value of the color
* @parameter: _iG: The Green value of the color
* @parameter: _iB: The Blue value of the color
* @return: void
********************/
void CVertex::SetColor(int _iR, int _iG, int _iB)
{
	COLORREF newColor;
	newColor = RGB(_iR, _iG, _iB);
	m_color = newColor;
}

/***********************
* SetColor: Sets the color of the position vector
* @author: Jc Fowles
* @parameter: _Color: RGB color to set the vertex to
* @return: void
********************/
void CVertex::SetColor(COLORREF _Color)
{
	m_color = _Color;
}

