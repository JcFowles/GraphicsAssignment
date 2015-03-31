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

CGame* CGame::s_pGame = 0;

/***********************
* CDirect3DObject: Constructor of the Game instance
* @author: Jc Fowles
* @return: 
********************/
CGame::CGame(void): m_pClock(0) // , //m_hMainWindow(0)
{
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
	
	//Delete m_pCubeMesh;
}

/***********************
* GetInstance: Returns a refrence to the singleton game object, if one does not excist create one
* @author: Jc Fowles
* @return: CGame& : Returns a refrence to the singleton game object
********************/
CGame& CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

/***********************
* DestroyInstance: Destroys the singleton game object
* @author: Jc Fowles
* @return: void
********************/
void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

/***********************
* InitizeD3D: Initializes the Game instance
* @author: Jc Fowles
* @parameter: _hWnd: Handle to the window
* @return: void
********************/
void CGame::Initialize(HWND _hWnd)
{
	m_bShadeFlat = true;
	m_bFillSolid = true;
	
	//m_hMainWindow = _hWnd;
	m_pClock = new CClock();
	m_pClock ->Initialise();
	m_pClock->Process();

	int iScreenWidth = 1920;
	int iScreenHeight = 1200;

	//Setting the camera
	m_CameraPosition = D3DXVECTOR3 (0.0f, 0.0f, -1000.0f);
	m_LookUp = D3DXVECTOR3 (0.0f, 0.0f, 1.0f);
	m_LookAt = D3DXVECTOR3 (0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_CameraView, &m_CameraPosition, &m_LookUp, &m_LookAt);

	//Create the Device
	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);	
	
	//Holder for various device information
	D3DPRESENT_PARAMETERS D3DPresentParameter;	
	
	//Set some of the device infomation
	ZeroMemory(&D3DPresentParameter, sizeof(D3DPRESENT_PARAMETERS));	//Clears up memory to be used
	
	//Windowed Mode
	D3DPresentParameter.Windowed = TRUE;
	//FullScreen Mode
	//D3DPresentParameter.Windowed = FALSE;							//Program is Full Screen//Program is Windowed
	D3DPresentParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;			//Gets rid of old frames
	D3DPresentParameter.hDeviceWindow = _hWnd;						//The window that direct#D will use
	D3DPresentParameter.BackBufferFormat = D3DFMT_X8R8G8B8;			//Set the back buffer format to 32-bit
	D3DPresentParameter.BackBufferWidth = iScreenWidth;				//Set the width of the buffer
	D3DPresentParameter.BackBufferHeight = iScreenHeight;			//Set the height of the buffer
			
	//Create the device Using the set device information
	m_pD3DInterface->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
								   _hWnd,
								   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								   &D3DPresentParameter,
								   &m_pD3DDevice);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			
	m_pCubeMesh = CreateMesh();
	
	//Rigth Cube
	C3DObject objCube1 = C3DObject();
	objCube1.Initialise(m_pCubeMesh, m_pD3DDevice,&m_CameraView, 250, 0, 0);
	objCube1.SetTilt(0, 10, 10);
	objCube1.SetPitch(1.0f);
	objCube1.SetSpeed(90.0f);

	m_vectObject.push_back(objCube1);

	//Left Cube
	C3DObject objCube2 = C3DObject();
	objCube2.Initialise(m_pCubeMesh, m_pD3DDevice,&m_CameraView, -250, 0, 0);
	objCube2.SetTilt(10, 0, 10);
	objCube2.SetYaw(1.0f);
	objCube2.SetSpeed(180.0f);

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
	Process(fDT);
	Draw();
	 
}

/***********************
* RenderFrame: Render a single frame to the screen
* @author: Jc Fowles
* @return: void
********************/
void CGame::Draw()
{
	//Clear the window to a white background
    m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	//Start the Current frame
    m_pD3DDevice->BeginScene();    
	
	//Draw all objects
    DrawObjects();

	//End the Current frame
    m_pD3DDevice->EndScene();    

	//Send the Frame to the D3D device and it will present it to the screen
    m_pD3DDevice->Present(NULL, NULL, NULL, NULL);  
}

/***********************
* RenderFrame: Render a single frame to the screen
* @author: Jc Fowles
* @return: void
********************/
void CGame::Process(float _fDeltaTick)
{
	//Process the camera View
	//Not implimented yet
	//To be added later when able to manipulate the camera
	 D3DXMatrixLookAtLH(&m_CameraView, &m_CameraPosition, &m_LookUp, &m_LookAt);


	 //Process all the cubes
	 for(unsigned int i = 0; i < m_vectObject.size(); i++)
	 {
		 m_vectObject[i].Process(_fDeltaTick,m_CameraView);
	 }	
	 
	

	  if(m_bFillSolid)
	 {
		  m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		  m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	 }
	 else
	 {
		 m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		 m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	 }

	  if(m_bShadeFlat)
	 {
		m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	 }
	 else
	 {
		m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	 }
}

/***********************
* CreateMesh: Creates a mesh of a Cube
* @author: Jc Fowles
* @return: void
********************/
CMesh* CGame::CreateMesh()
{
	int iRandomRed;
	int iRandomGreen; 
	int iRandomBlue;
	float fCubeSize = 150.0f;

	CMesh* pCubeMesh = new CMesh;

	vector<CPolygon> vectPolygons;
	
	CVertex vertA = CVertex(-fCubeSize/2, fCubeSize/2, -fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertA.SetColor(iRandomRed,iRandomGreen,iRandomBlue);
	CVertex vertB = CVertex(fCubeSize/2, fCubeSize/2, -fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertB.SetColor(iRandomRed,iRandomGreen,iRandomBlue);
	CVertex vertC = CVertex(fCubeSize/2, -fCubeSize/2, -fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertC.SetColor(iRandomRed,iRandomGreen,iRandomBlue);
	CVertex vertD = CVertex(-fCubeSize/2, -fCubeSize/2, -fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertD.SetColor(iRandomRed,iRandomGreen,iRandomBlue);

	CVertex vertE = CVertex(-fCubeSize/2, fCubeSize/2, fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertE.SetColor(iRandomRed,iRandomGreen,iRandomBlue);
	CVertex vertF = CVertex(fCubeSize/2, fCubeSize/2, fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertF.SetColor(iRandomRed,iRandomGreen,iRandomBlue);
	CVertex vertG = CVertex(fCubeSize/2, -fCubeSize/2, fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertG.SetColor(iRandomRed,iRandomGreen,iRandomBlue);
	CVertex vertH = CVertex(-fCubeSize/2, -fCubeSize/2, fCubeSize/2);
	iRandomRed = rand() % 255;
	iRandomGreen = rand() % 255;
	iRandomBlue = rand() % 255;
	vertH.SetColor(iRandomRed,iRandomGreen,iRandomBlue);

	
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

 /***********************
* GetDevice: Returns a pointer to the D3DDevice
* @author: Jc Fowles
* @return:  IDirect3DDevice9*: a pointer to the D3DDevice
********************/
 IDirect3DDevice9* CGame::GetDevice()
 {
	 return m_pD3DDevice;
 }

 /***********************
* ToggleShader: Toggles between Flat shader and Gouraud shader
* @author: Jc Fowles
* @return: void
********************/
void CGame::ToggleShader()
{
	m_bShadeFlat = !m_bShadeFlat;
}

  /***********************
* ToggleFillMode: Toggles between Solid Fill mode and wireframe fill mode
* @author: Jc Fowles
* @return: void
********************/
void CGame::ToggleFillMode()
{
	m_bFillSolid = !m_bFillSolid;
	
}


D3DXVECTOR3* CGame::GetCameraPosition()
{
	return &m_CameraPosition;
}

void CGame::SetCameraPosition(D3DXVECTOR3 _CameraPosition)
{
	m_CameraPosition = _CameraPosition;
}