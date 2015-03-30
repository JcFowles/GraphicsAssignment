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


	m_fRotationYaw = 0.0f;
	m_fRotationPitch = 0.0f;
	m_fRotationRoll = 0.0f;
	

	vector<CPolygon>* meshPolygons =  m_pMesh->GetPolygons();
	for(unsigned int uiPolyIndex = 0; uiPolyIndex < meshPolygons->size(); uiPolyIndex++)	// Loop all Meshes Polygons
	{
		for( unsigned int uiVertIndex = 0; uiVertIndex < (*(*meshPolygons)[uiPolyIndex].GetVertices()).size(); uiVertIndex++)	// Loop all Polygons Verts
		{
			m_vectAllVertices.push_back( (*(*meshPolygons)[uiPolyIndex].GetVertices())[uiVertIndex]);
		}
	}

	return true;
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
* ReadyVertexBuffer: Readies the vertex buffer
* @author: Jc Fowles
* @return: IDirect3DVertexBuffer9* : a pointer to the vertex buffer
********************/
void C3DObject::ReadyVertexBuffer()
{
	m_pD3DVertexBuffer = NULL;

	m_pD3DDevice->CreateVertexBuffer((m_vectAllVertices.size())*sizeof(CVertex),
                               0,
                               (D3DFVF_XYZ | D3DFVF_DIFFUSE),
                               D3DPOOL_MANAGED,
                               &m_pD3DVertexBuffer,
                               NULL);

    VOID* pVoid;    // a void pointer
		
    // lock v_buffer and load the vertices into it
    m_pD3DVertexBuffer->Lock(0, (m_vectAllVertices.size())*sizeof(CVertex) , (void**)&pVoid, 0);

	memcpy(pVoid, &m_vectAllVertices.front(), (m_vectAllVertices.size())*sizeof(CVertex));

    m_pD3DVertexBuffer->Unlock();

}

/***********************
* Draw: Draws the Object
* @author: Jc Fowles
* @return: void
********************/
void C3DObject::Draw()
{

	ReadyVertexBuffer();

	CalcWorldMatrix();

	// select which vertex format we are using
    m_pD3DDevice->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE));

    // select the vertex buffer to display
	m_pD3DDevice->SetStreamSource(0, m_pD3DVertexBuffer, 0, sizeof(CVertex));

    // copy the vertex buffer to the back buffer
    m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, (m_vectAllVertices.size()/3));
}

/***********************
* Process: Processes the 3DObject
* @author: Jc Fowles
* @parameter: _fDeltaTick: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void C3DObject::Process(float _fDeltaTick)
{
	CalcWorldMatrix();
}


/***********************
* CalcWorldMatrix: Calculates to the world matrix
* @author: Jc Fowles
* @return: void
********************/
void C3DObject::CalcWorldMatrix()
{
	//Set the world matrix to the identity 	
    D3DXMatrixIdentity(&m_matWorld);    

   D3DXMatrixRotationYawPitchRoll(&m_matWorld, m_fRotationYaw, m_fRotationPitch, m_fRotationRoll);
	
	D3DXMATRIX tempMat;
	D3DXMatrixTranslation(&tempMat, m_fX, m_fY, m_fZ);
	
	
	m_matWorld *= tempMat;

	//static float index = 0.0f; index+=0.05f;    // an ever-increasing float value
    // build a matrix to rotate the model based on the increasing float value
	//D3DXMatrixRotationX(&matRotateX, index);
    //D3DXMatrixRotationY(&matRotateX, index);
	//D3DXMatrixRotationZ(&matRotateX, index);
	
	////Setting the camera
	// D3DXMatrixLookAtLH(&m_CameraView,
 //                      &D3DXVECTOR3 (0.0f, 0.0f, -1000.0f),		// the camera position
 //                      &D3DXVECTOR3 (0.0f, 0.0f, 1.0f),			// the look-at position
 //                      &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));		// the up direction


    // tell Direct3D about our matrix
    m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	    

    m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_CameraView);    // set the view transform to matView

    D3DXMATRIX matProjection;							// the projection transform matrix

    D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),			// the horizontal field of view
                               (FLOAT)1920 / (FLOAT)1200, // aspect ratio
                               100.0f,    // the near view-plane
                               1500.0f);    // the far view-plane

    m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection
}
