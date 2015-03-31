//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : C3DObject.cpp
// Description : Contains the header file for Polygon Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

//This Include
#include "C3DObject.h"

/***********************
* C3DObject: Defualt Constructor of the 3DObject 
* @author: Jc Fowles
* @return: 
********************/
C3DObject::C3DObject()
{
	m_fOneDegree = (float)(std::atan(1.0)*4)/180;
}

/***********************
* ~C3DObject: Destructor of the 3DObject
* @author: Jc Fowles
* @return: 
********************/
C3DObject::~C3DObject()
{
	//CMesh* m_pMesh;
	
	//m_pD3DVertexBuffer->Release();
	//m_pD3DDevice->Release();
}

/***********************
* Initialise: Initialises the 3DObject with the passed in mesh data
* @author: Jc Fowles
* @parameter: _pMesh: Pointer to the Mesh data
* @return: bool: success bool
********************/
bool C3DObject::Initialise(CMesh* _pMesh, IDirect3DDevice9* _d3dDev, D3DXMATRIX* _CameraView, float _fX, float _fY, float _fZ)
{
	m_CameraView = *_CameraView;
	
	m_pMesh = _pMesh;
	m_pD3DDevice = _d3dDev;
	
	m_fX = _fX;
	m_fY = _fY;
	m_fZ = _fZ;
	
	m_fRotationSpeed = 1;

	m_fRotationYaw = 0.0f;
	m_fRotationPitch = 0.0f;
	m_fRotationRoll = 0.0f;

	m_pMesh->ReadyVertexBuffer(m_pD3DDevice);
		
	return true;
}

/***********************
* SetMesh: Sets the particular mesh for this object
* @author: Jc Fowles
* @parameter: _pMesh: Pointer to the Mesh data
* @return: void
********************/
void C3DObject::SetTilt(float _fYTilt, float _fXTilt, float _fZTilt)
{
	m_fTiltYAxis = _fYTilt;
	m_fTiltXAxis = _fXTilt;
	m_fTiltZAxis = _fZTilt;
}

/***********************
* SetMesh: Sets the particular mesh for this object
* @author: Jc Fowles
* @parameter: _pMesh: Pointer to the Mesh data
* @return: void
********************/
void C3DObject::SetMesh(CMesh* _pMesh)
{
	m_pMesh = _pMesh;
}

/***********************
* SetX: Sets the X coordinate of the 3DObject centre
* @author: Jc Fowles
* @parameter: _f: The Float value to be set as the X coordinate
* @return: void
********************/
void C3DObject::SetX(float _f)
{
	m_fX = _f;
}

/***********************
* SetY: Sets the Y coordinate of the 3DObject centre
* @author: Jc Fowles
* @parameter: _f: The Float value to be set as the Y coordinate
* @return: void
********************/
void C3DObject::SetY(float _f)
{
	m_fY = _f;
}

/***********************
* SetY: Sets the Z coordinate of the 3DObject centre
* @author: Jc Fowles
* @parameter: _f: The Float value to be set as the Z coordinate
* @return: void
********************/
void C3DObject::SetZ(float _f)
{
	m_fZ = _f;
}

/***********************
* SetSpeed: Set the rotation speed.
* @author: Jc Fowles
* @parameter: _f: How many degrees rotated by in a second
* @return: void
********************/
void C3DObject::SetSpeed(float _f)
{
	m_fRotationSpeed = _f;
}

/***********************
* SetYaw: How far to rotate around the Y axis
* @author: Jc Fowles
* @parameter: _f: The amount to rotate by
* @return: void
********************/
void C3DObject::SetYaw(float _f)
{
	m_fRotationYaw = _f;
}

/***********************
* SetPitch: How far to rotate around the X axis
* @author: Jc Fowles
* @parameter: _f: The amount to rotate by
* @return: void
********************/
void C3DObject::SetPitch(float _f)
{
	m_fRotationPitch = _f;
}

/***********************
* SetPitch: How far to rotate around the Z axis
* @author: Jc Fowles
* @parameter: _f: The amount to rotate by
* @return: void
********************/
void C3DObject::SetRoll(float _f)
{
	m_fRotationRoll = _f;
}

/***********************
* Draw: Draws the Object
* @author: Jc Fowles
* @return: void
********************/
void C3DObject::Draw()
{
	//Calculate the transform matrix
	CalcTransformMatrix();

	//Draw the mesh
	m_pMesh->Draw(m_pD3DDevice);
}

/***********************
* Process: Processes the 3DObject
* @author: Jc Fowles
* @parameter: _fDeltaTick: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void C3DObject::Process(float _fDeltaTick, D3DXMATRIX _CameraView)
{
	m_CameraView = _CameraView;

	//Speed to rotate by
	float fSpeed = m_fRotationSpeed*m_fOneDegree;
	
	//Rotation based on delta tick and speed of rotation
	m_fTiltYAxis += m_fRotationYaw *  (fSpeed*_fDeltaTick);
	m_fTiltXAxis += m_fRotationPitch * (fSpeed*_fDeltaTick);
	m_fTiltZAxis += m_fRotationRoll * (fSpeed*_fDeltaTick);

	

	//Random Rapid Changeing colors(Not Keeping but is cool)
	/*
	int iRandomRed;
	int iRandomGreen; 
	int iRandomBlue;
	for(unsigned int i = 0; i < m_vectAllVertices.size(); i++)
	{
		iRandomRed = rand() % 255;
		iRandomGreen = rand() % 255;
		iRandomBlue = rand() % 255;
		m_vectAllVertices[i].SetColor(iRandomRed,iRandomGreen,iRandomBlue);
	}*/
}

/***********************
* CalcTransformMatrix: Calculates to the transform matrix by calculating and setting the World, view and projection matrix
* @author: Jc Fowles
* @return: void
********************/
void C3DObject::CalcTransformMatrix()
{
	//Set the world matrix to the identity, reset the world matrix 	
    D3DXMatrixIdentity(&m_matWorld);  

	//Rotate the Cube
	D3DXMatrixRotationYawPitchRoll(&m_matWorld, m_fTiltYAxis, m_fTiltXAxis, m_fTiltZAxis);
	
	//Translate the Cube
	D3DXMATRIX tempMat;
	D3DXMatrixTranslation(&tempMat, m_fX, m_fY, m_fZ);
	m_matWorld *= tempMat;
	
	//Calculate the Projection matrix of our D3D Device
    D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),			//Tthe horizontal field of view
                               (FLOAT)1920 / (FLOAT)1200,	//Aspect ratio
                               100.0f,						//The near view-plane
                               1500.0f);					//The far view-plane


    //Set the world matrix of our D3D Device
    m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	
	//Set the view matrix of our D3D Device
    m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_CameraView);	
	
	//Set the Projection matrix of our D3D Device
    m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection
}
