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
#include "Mesh.h"
#include "Vertex.h"

class C3DObject
{
public:
	// Member Functions
	C3DObject();
	~C3DObject();

	bool Initialise(CMesh* _pMesh, IDirect3DDevice9* _d3dDev, D3DXMATRIX* _CameraView, float _fX, float _fY, float _fZ);
	
	void SetMesh(CMesh* _pMesh);
	
	void SetX(float _f);
	void SetY(float _f);
	void SetZ(float _f);

	void SetYaw(float _f);		//Rotation on Y
	void SetPitch(float _f);	//Rotation on X
	void SetRoll(float _f);		//Rotation on Z

	void ReadyVertexBuffer();
	void Draw();
	void Process(float _fDeltaTick);
	void CalcWorldMatrix();

private:
	// Member Variables
	CMesh* m_pMesh;
	
	IDirect3DVertexBuffer9* m_pD3DVertexBuffer;
	IDirect3DDevice9* m_pD3DDevice;
	
	vector<CVertex> m_vectAllVertices;
	
	D3DXMATRIX m_matWorld;

	float m_fRotationYaw;
	float m_fRotationPitch;
	float m_fRotationRoll;

	float m_fX;
	float m_fY;
	float m_fZ;

	D3DXMATRIX m_CameraView;

};
