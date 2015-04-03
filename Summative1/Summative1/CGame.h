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

//Local Includes
#include "Mesh.h"
#include "C3DObject.h"
#include "Clock.h"

#pragma once
class CGame
{
public:
	//Member Function
	//Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

	~CGame(void);

	void Initialize(HWND _hWnd, int m_iScreenWidth, int m_iScreenHeight);    //Initializes the Direct3D
		
	void Draw();
	void Process(float _fDeltaTick);
	void RenderFrame(void);				//Renders a single frame
	
	void DrawObjects();

	IDirect3DDevice9* GetDevice();

	void ToggleShader();
	void ToggleFillMode();

	D3DXVECTOR3* GetCameraPosition();
	void SetCameraPosition(D3DXVECTOR3 _CameraPosition);
	D3DXVECTOR3* GetLookAt();
	void SetLookAt(D3DXVECTOR3 _LookAt);
	COLORREF GetRandomColor();

protected:
	CGame();

	CMesh* CreateMesh();
	void CreateObject();
	
private:
	// Member Variables
	static CGame* s_pGame;

	CClock* m_pClock;

	IDirect3D9* m_pD3DInterface;
	IDirect3DDevice9* m_pD3DDevice;
	
	CMesh* m_pCubeMesh;
	
	vector<C3DObject> m_vectObject;

	D3DXMATRIX m_CameraView;

	bool m_bShadeFlat;
	bool m_bFillSolid;

	D3DXVECTOR3 m_CameraPosition;
	D3DXVECTOR3 m_LookUp;
	D3DXVECTOR3 m_LookAt;
	
	float m_fScreenWidth ;
	float m_fScreenHeight ;

	float m_fCubeSize;
};

