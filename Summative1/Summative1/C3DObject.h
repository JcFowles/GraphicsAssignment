// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : C3DObject.h 
// Description : Contains the header file for 3DObject Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

#pragma once

// Library Includes
#include <d3dx9.h>
#include <math.h>

//local includes
#include "Mesh.h"
#include "Vertex.h"

class C3DObject
{
public:
	// Member Functions
	C3DObject();
	~C3DObject();

	bool Initialise(CMesh* _pMesh, IDirect3DDevice9* _d3dDev, D3DXMATRIX* _CameraView, float _fX, float _fY, float _fZ);
	
	void SetTilt(float _fYTilt, float _fXTilt, float _fZTilt);
	void SetMesh(CMesh* _pMesh);
	
	void SetX(float _f);
	void SetY(float _f);
	void SetZ(float _f);
	void SetSpeed(float _f);
		
	void SetYaw(float _f);		//Rotation on Y
	void SetPitch(float _f);	//Rotation on X
	void SetRoll(float _f);		//Rotation on Z

	void ReadyVertexBuffer();
	void Draw();
	void Process(float _fDeltaTick, D3DXMATRIX _CameraView);
	void CalcTransformMatrix();
		

private:

	float m_fOneDegree; 

	// Member Variables
	CMesh* m_pMesh;
	
	IDirect3DVertexBuffer9* m_pD3DVertexBuffer;
	IDirect3DDevice9* m_pD3DDevice;
		
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matCube;

	float m_fTiltYAxis;
	float m_fTiltXAxis;
	float m_fTiltZAxis;

	float m_fRotationYaw;
	float m_fRotationPitch;
	float m_fRotationRoll;

	float m_fX;
	float m_fY;
	float m_fZ;

	D3DXMATRIX m_CameraView;

	float m_fRotationSpeed;
};
