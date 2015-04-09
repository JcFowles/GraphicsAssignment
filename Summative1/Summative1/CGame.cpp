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
CGame::CGame(void): m_pClock(0),m_fCubeSize(0) //m_hMainWindow(0)
{
}

/***********************
* CDirect3DObject: Destructor of the Game instance
* @author: Jc Fowles
* @return: 
********************/
CGame::~CGame(void)
{
	delete m_pCubeMesh;
	m_pCubeMesh = 0;
	delete m_pClock;
	m_pClock = 0;
	
	m_pD3DInterface->Release();  
	m_pD3DInterface = 0;
	m_pD3DDevice->Release();
	m_pD3DDevice = 0;
	
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
* Release: Releases the D3DirectX objects
* @author: Jc Fowles
* @return: void
********************/
void CGame::Release()
{

	m_pCubeMesh->Release();
	m_pD3DDevice->Release();
	m_pD3DDevice = 0;
	m_pD3DInterface->Release();  
	m_pD3DInterface = 0;
}

/***********************
* InitizeD3D: Initializes the Game instance
* @author: Jc Fowles
* @parameter: _hWnd: Handle to the window
* @return: void
********************/
void CGame::Initialize(HWND _hWnd, int _iScreenWidth, int _iScreenHeight)
{
	//float fFromCentre = 2*m_fCubeSize;

	m_bShadeFlat = true;
	m_bFillSolid = true;
	
	//m_hMainWindow = _hWnd;
	m_pClock = new CClock();
	m_pClock ->Initialise();
	m_pClock->Process();
	
	m_fScreenWidth = (float)_iScreenWidth;
	m_fScreenHeight = (float)_iScreenHeight;

	m_fAspect = m_fScreenWidth/m_fScreenHeight;
		
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
	D3DPresentParameter.BackBufferWidth = (UINT)m_fScreenWidth;				//Set the width of the buffer
	D3DPresentParameter.BackBufferHeight =(UINT)m_fScreenHeight;			//Set the height of the buffer
	D3DPresentParameter.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES ;

	//Create the device Using the set device information
	m_pD3DInterface->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
								   _hWnd,
								   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								   &D3DPresentParameter,
								   &m_pD3DDevice);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	
	m_pCubeMesh = CreateMesh();
	
	float fFromCentre = 2*m_fCubeSize;

	//Setting the camera
	m_CameraPosition = D3DXVECTOR3 (0.0f, 0.0f, -5);
	m_LookUp = D3DXVECTOR3 (0.0f, 1.0f, 0.0f);
	m_LookAt = D3DXVECTOR3 (0.f, 0.0f, 1.0f);
	
	//Right Cube
	C3DObject objCube1 = C3DObject(m_fScreenWidth,m_fScreenHeight);
	objCube1.Initialise(m_pCubeMesh, m_pD3DDevice,&m_CameraView, -1*fFromCentre, 0, 0);
	objCube1.SetTilt(0, 0, 0);
	objCube1.SetRoll(1.0f);
	objCube1.SetSpeed(30.0f);		//magic number 22403

	m_vectObject.push_back(objCube1);

	//Left Cube
	C3DObject objCube2 = C3DObject(m_fScreenWidth,m_fScreenHeight);
	objCube2.Initialise(m_pCubeMesh, m_pD3DDevice,&m_CameraView, fFromCentre, 0, 0);
	objCube2.SetTilt(0, 0, 90);
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
	D3DXMatrixLookAtLH(&m_CameraView, &m_CameraPosition, &m_LookAt, &m_LookUp);

	//Process all the cubes
	for(unsigned int i = 0; i < m_vectObject.size(); i++)
	{
		m_vectObject[i].Process(_fDeltaTick,m_CameraView);
	}	
	
}

/***********************
* GetRandomColor: Returns a random color, and prevents a whitish color
* @author: Jc Fowles
* @return: COLORREF: the random color returned
********************/
COLORREF CGame::GetRandomColor()
{
	int iRandomRed;
	int iRandomGreen; 
	int iRandomBlue;
	int iPreventWhite = 205;
	iRandomRed = rand() % iPreventWhite;
	iRandomGreen = rand() % iPreventWhite;
	iRandomBlue = rand() % iPreventWhite;
	COLORREF newColor;
	newColor = RGB(iRandomRed, iRandomGreen, iRandomBlue);
	return newColor;
}

/***********************
* CreateMesh: Creates a mesh of a Cube
* @author: Jc Fowles
* @return: void
********************/
CMesh* CGame::CreateMesh()
{
	//Unit Cube
	m_fCubeSize = 1;

	CMesh* pCubeMesh = new CMesh;

	vector<CPolygon> vectPolygons;
	
	CVertex vertA = CVertex(-m_fCubeSize/2, m_fCubeSize/2, -m_fCubeSize/2);
	vertA.SetColor(GetRandomColor());
	CVertex vertB = CVertex(m_fCubeSize/2, m_fCubeSize/2, -m_fCubeSize/2);
	vertB.SetColor(GetRandomColor());
	CVertex vertC = CVertex(m_fCubeSize/2, -m_fCubeSize/2, -m_fCubeSize/2);
	vertC.SetColor(GetRandomColor());
	CVertex vertD = CVertex(-m_fCubeSize/2, -m_fCubeSize/2, -m_fCubeSize/2);
	vertD.SetColor(GetRandomColor());

	CVertex vertE = CVertex(-m_fCubeSize/2, m_fCubeSize/2, m_fCubeSize/2);
	vertE.SetColor(GetRandomColor());
	CVertex vertF = CVertex(m_fCubeSize/2, m_fCubeSize/2, m_fCubeSize/2);
	vertF.SetColor(GetRandomColor());
	CVertex vertG = CVertex(m_fCubeSize/2, -m_fCubeSize/2, m_fCubeSize/2);
	vertG.SetColor(GetRandomColor());
	CVertex vertH = CVertex(-m_fCubeSize/2, -m_fCubeSize/2, m_fCubeSize/2);
	vertH.SetColor(GetRandomColor());
		
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
	

	pCubeMesh->ReadyVertexBuffer(m_pD3DDevice);
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
* ToggleFillMode: Toggles between Solid Fill mode and wireframe fill mode
* @author: Jc Fowles
* @return: void
********************/
void CGame::ToggleFillMode()
{
	m_bFillSolid = !m_bFillSolid;

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
	
}


D3DXVECTOR3* CGame::GetCameraPosition()
{
	return &m_CameraPosition;
}


void CGame::SetCameraPosition(D3DXVECTOR3 _CameraPosition)
{
	m_CameraPosition = _CameraPosition;
}


D3DXVECTOR3* CGame::GetLookAt()
{
	return &m_LookAt;
}


void CGame::SetLookAt(D3DXVECTOR3 _LookAt)
{
	m_LookAt = _LookAt;
}