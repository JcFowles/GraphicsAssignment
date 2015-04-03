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
C3DObject::C3DObject(float _fScreenWidth, float _fScreenHeight)
{
	m_fOneDegree = (float)(std::atan(1.0)*4)/180;
	m_fScreenWidth = _fScreenWidth;
	m_fScreenHeight = _fScreenHeight;
	m_fTiltYAxis = 0;
	m_fTiltXAxis = 0;
	m_fTiltZAxis = 0;
}

/***********************
* ~C3DObject: Destructor of the 3DObject
* @author: Jc Fowles
* @return: 
********************/
C3DObject::~C3DObject()
{
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

	return true;
}

/***********************
* SetMesh: Sets the particular mesh for this object
* @author: Jc Fowles
* @parameter: _pMesh: Pointer to the Mesh data
* @return: void
********************/
void C3DObject::SetTilt(float _fXTilt, float _fYTilt, float _fZTilt)
{
	m_fTiltYAxis = _fYTilt*m_fOneDegree;
	m_fTiltXAxis = _fXTilt*m_fOneDegree;
	m_fTiltZAxis = _fZTilt*m_fOneDegree;
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
	
}

/***********************
* CalcTransformMatrix: Calculates to the transform matrix by calculating and setting the World, view and projection matrix
* @author: Jc Fowles
* @return: void
********************/
void C3DObject::CalcTransformMatrix()
{
	D3DXMATRIX RotateX;
	D3DXMATRIX RotateY;
	D3DXMATRIX RotateZ;
	
	//Set the world matrix to the identity, reset the world matrix 	
    D3DXMatrixIdentity(&m_matWorld);  
		
	//Translate the Cube
	D3DXMATRIX translateMat;
	D3DXMatrixTranslation(&translateMat, m_fX, m_fY, m_fZ);
	
	//Rotate the Cube
	D3DXMatrixRotationYawPitchRoll(&m_matWorld, m_fTiltYAxis, m_fTiltXAxis, m_fTiltZAxis);
	
	//Combine THe translation with the rotation 
	m_matWorld *= translateMat;
	float fAspectRatio = m_fScreenWidth/m_fScreenHeight;

	//Calculate the Projection matrix of our D3D Device
    D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45*fAspectRatio),	//Tthe horizontal field of view
                               (FLOAT)fAspectRatio,				//Aspect ratio
                               1.0f,							//The near view-plane
                               10000.0f);						//The far view-plane

    //Set the world matrix of our D3D Device
    m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	
	//Set the view matrix of our D3D Device
    m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_CameraView);	
	
	//Set the Projection matrix of our D3D Device
    m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjection);
}
