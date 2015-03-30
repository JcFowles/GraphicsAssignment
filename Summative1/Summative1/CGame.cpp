//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CGame.cpp
// Description : Contains the main funtionality of Game Class
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

//This include
#include "CGame.h"

/***********************
* CDirect3DObject: Constructor of the Game instance
* @author: Jc Fowles
* @return: 
********************/
CGame::CGame(void)
{
	m_D3DVertexBuffer = NULL;
}

/***********************
* CDirect3DObject: Destructor of the Game instance
* @author: Jc Fowles
* @return: 
********************/
CGame::~CGame(void)
{
	//Release both the 3D device and Direct3D interface
	m_pD3DInterface->Release();    
    m_pD3DDevice->Release();
	m_D3DVertexBuffer->Release();

	//Delete m_pCubeMesh;
}

/***********************
* InitizeD3D: Initializes the Game instance
* @author: Jc Fowles
* @parameter: _hWnd: Handle to the window
* @return: void
********************/
void CGame::Initialize(HWND _hWnd)
{
	//m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;
	m_pClock = new CClock();
	m_pClock ->Initialise();
	m_pClock->Process();

	int iScreenWidth = 1920;
	int iScreenHeight = 1200;

	//Setting the camera
	 D3DXMatrixLookAtLH(&m_CameraView,
                       &D3DXVECTOR3 (0.0f, 0.0f, -1000.0f),		// the camera position
                       &D3DXVECTOR3 (0.0f, 0.0f, 1.0f),			// the look-at position
                       &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));		// the up direction

	//Create the Device
	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);	
	
	//Holder for various device information
	D3DPRESENT_PARAMETERS D3DPresentParameter;	
	
	//Set some of the device infomation
	ZeroMemory(&D3DPresentParameter, sizeof(D3DPRESENT_PARAMETERS));	//Clears up memory to be used
	
	//Windowed Mode
	D3DPresentParameter.Windowed = TRUE;							//Program is Windowed
	D3DPresentParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;			//Gets rid of old frames
	D3DPresentParameter.hDeviceWindow = _hWnd;						//The window that direct#D will use

	//FullScreen Mode
	//D3DPresentParameter.Windowed = FALSE;							//Program is Full Screen
	//D3DPresentParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;			//Gets rid of old frames
	//D3DPresentParameter.hDeviceWindow = _hWnd;						//The window that direct#D will use
	//D3DPresentParameter.BackBufferFormat = D3DFMT_X8R8G8B8;			//Set the back buffer format to 32-bit
	//D3DPresentParameter.BackBufferWidth = iScreenWidth;				//Set the width of the buffer
	//D3DPresentParameter.BackBufferHeight = iScreenHeight;			//Set the height of the buffer
		
	//Create the device Using the set device information
	m_pD3DInterface->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
								   _hWnd,
								   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								   &D3DPresentParameter,
								   &m_pD3DDevice);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, FALSE);
	//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	m_pCubeMesh = CreateMesh();

	C3DObject objCube1 = C3DObject();
	objCube1.Initialise(m_pCubeMesh, m_pD3DDevice,&m_CameraView, 150,0,0);
	objCube1.SetPitch(1.0f);
	m_vectObject.push_back(objCube1);
	C3DObject objCube2 = C3DObject();
	objCube2.Initialise(m_pCubeMesh, m_pD3DDevice,&m_CameraView, -150, 0,0);
	objCube2.SetYaw(1.0f);
	m_vectObject.push_back(objCube2);
	
}

/***********************
* RenderFrame: Render a single frame to the screen
* @author: Jc Fowles
* @return: void
********************/
void CGame::RenderFrame(void)
{
	m_pClock->Process();
	float fDT = m_pClock->GetDeltaTick();
	//Process(fDT);
	Draw();
	 
}

/***********************
* RenderFrame: Render a single frame to the screen
* @author: Jc Fowles
* @return: void
********************/
void CGame::Draw()
{
	// clear the window to a deep blue
    m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	//Start of curretn frame to be drawn
    m_pD3DDevice->BeginScene();    

    DrawObjects();

	//Frame is now complete, so end it
    m_pD3DDevice->EndScene();    

	//Present The Frame to the screen
    m_pD3DDevice->Present(NULL, NULL, NULL, NULL);  
}

/***********************
* RenderFrame: Render a single frame to the screen
* @author: Jc Fowles
* @return: void
********************/
void CGame::Process(float _fDeltaTick)
{
	////Setting the camera View
	// D3DXMatrixLookAtLH(&m_CameraView,
	//                      &D3DXVECTOR3 (0.0f, 0.0f, -1000.0f),		// the camera position
	//                      &D3DXVECTOR3 (0.0f, 0.0f, 1.0f),			// the look-at position
	//                      &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));			// the up direction


	 for(unsigned int i = 0; i < m_vectObject.size(); i++)
	 {
		 m_vectObject[i].Process(_fDeltaTick);
	 }
	
}

/***********************
* CreateMesh: Creates a mesh of a Cube
* @author: Jc Fowles
* @return: void
********************/
CMesh* CGame::CreateMesh()
{
	float fCubeSize = 150.0f;

	CMesh* pCubeMesh = new CMesh;

	vector<CPolygon> vectPolygons;
	
	CVertex vertA = CVertex(-fCubeSize/2, fCubeSize/2, -fCubeSize/2);
	vertA.SetColor(0,255,0);
	CVertex vertB = CVertex(fCubeSize/2, fCubeSize/2, -fCubeSize/2);
	vertB.SetColor(0,255,0);
	CVertex vertC = CVertex(fCubeSize/2, -fCubeSize/2, -fCubeSize/2);
	vertC.SetColor(0,255,0);
	CVertex vertD = CVertex(-fCubeSize/2, -fCubeSize/2, -fCubeSize/2);
	vertD.SetColor(0,255,0);

	CVertex vertE = CVertex(-fCubeSize/2, fCubeSize/2, fCubeSize/2);
	vertE.SetColor(0,0,255);
	CVertex vertF = CVertex(fCubeSize/2, fCubeSize/2, fCubeSize/2);
	vertF.SetColor(0,0,255);
	CVertex vertG = CVertex(fCubeSize/2, -fCubeSize/2, fCubeSize/2);
	vertG.SetColor(0,0,255);
	CVertex vertH = CVertex(-fCubeSize/2, -fCubeSize/2, fCubeSize/2);
	vertH.SetColor(0,0,255);

	
	//CubeFaceA
	vectPolygons.push_back(CPolygon(&vertA, &vertB, &vertC));
	vectPolygons.push_back(CPolygon(&vertA, &vertC, &vertD));

	//CubeFaceB
	vectPolygons.push_back(CPolygon(&vertE, &vertA, &vertD));
	vectPolygons.push_back(CPolygon(&vertE, &vertD, &vertH));

	//CubeFaceC
	vectPolygons.push_back(CPolygon(&vertF, &vertE, &vertH));
	vectPolygons.push_back(CPolygon(&vertF, &vertH, &vertG));

	//CubeFaceD
	vectPolygons.push_back(CPolygon(&vertB, &vertF, &vertG));
	vectPolygons.push_back(CPolygon(&vertB, &vertG, &vertC));

	//CubeFaceE
	vectPolygons.push_back(CPolygon(&vertE, &vertF, &vertB));
	vectPolygons.push_back(CPolygon(&vertE, &vertB, &vertA));

	//CubeFaceF
	vectPolygons.push_back(CPolygon(&vertD, &vertC, &vertG));
	vectPolygons.push_back(CPolygon(&vertD, &vertG, &vertH));
	
	//Push all polygons into the mesh
	for (unsigned int k = 0; k < vectPolygons.size(); k++)
	{
		pCubeMesh->AddPolygon(&vectPolygons[k]);
	}
	
	return pCubeMesh;
	
}

/***********************
* DrawObjects: Draws the objects
* @author: Jc Fowles
* @return: void
********************/
 void CGame::DrawObjects()
 {
	 for(unsigned int i = 0; i < m_vectObject.size(); i++)
	 {
		 m_vectObject[i].Draw();
	 }
}

