//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CGame.h
// Description : Contains the header file for Game Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

//Library Includes
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//Local Includes
#include "Mesh.h"
#include "C3DObject.h"
#include "Clock.h"

#pragma once
class CGame
{
public:
	//Member Function

	CGame(void);
	~CGame(void);

	void Initialize(HWND _hWnd);    //Initializes the Direct3D
	
	void Draw();
	void Process(float _fDeltaTick);
	
	void RenderFrame(void);				//Renders a single frame

	CMesh* CreateMesh();
	void CreateObject();

	void DrawObjects();

	
private:
	// Member Variables
	CClock* m_pClock;
	HWND m_hMainWindow;

	IDirect3D9* m_pD3DInterface;
	IDirect3DDevice9* m_pD3DDevice;
	PDIRECT3DVERTEXBUFFER9 m_D3DVertexBuffer;
	CMesh* m_pCubeMesh;
	
	vector<C3DObject> m_vectObject;

	D3DXMATRIX m_CameraView;

};

