//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : Source.cpp 
// Description : Hold the main functionality for the program
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//


//Library includes
#include <ctime>
#include <windows.h>
#include <windowsx.h>
#include "vld.h"

//Local includes
#include "CGame.h"

#define WIN32_LEAN_AND_MEAN
#define WINDOW_CLASS_NAME L"SUMMATIVE1"


using namespace std;

/***********************
* WindowProc: This is the message handler for the Window, 
* @author: Jc Fowles
* @Parameter: _hWnd: Handle to the Window sending the message
* @Parameter: _uiMsg: The message ID being sent
* @Parameter: _wParam: Additional detail about the message being sent
* @Parameter: _lParam: Additional detail about the message being sent
* @return: LRESULT: Program termination value
********************/
LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{

	//Procces the given message
    switch(_uiMsg)
    {
	case WM_ACTIVATEAPP:
		{

		}
		break;
        //Closing the window
        case WM_DESTROY:
            {
                //Send message to close the entire application
                PostQuitMessage(0);
                return 0;
            } break;
		case WM_KEYDOWN:
			{
				switch(_wParam)
				{
				case VK_ESCAPE:
					{
						//Send message to close the entire application
						PostQuitMessage(0);
						return 0;
					}
					break;
				case VK_NUMPAD1:
					{
						CGame::GetInstance().ToggleFillMode();
					}
					break;
				case VK_NUMPAD2:
					{
						CGame::GetInstance().ToggleShader();
					}
					break;
				case VK_LEFT:
					{
						D3DXVECTOR3 LookAt;
						LookAt = *(CGame::GetInstance().GetLookAt());
						LookAt.x += -1;
						(CGame::GetInstance().SetLookAt(LookAt));
						
						D3DXVECTOR3 CamPos;
						CamPos = *(CGame::GetInstance().GetCameraPosition());
						CamPos.x += -1;
						(CGame::GetInstance().SetCameraPosition(CamPos));

					}
					break;
				case VK_RIGHT:
					{
						
						D3DXVECTOR3 LookAt;
						LookAt = *(CGame::GetInstance().GetLookAt());
						LookAt.x += 1;
						(CGame::GetInstance().SetLookAt(LookAt));
						
						D3DXVECTOR3 CamPos;
						CamPos = *(CGame::GetInstance().GetCameraPosition());
						CamPos.x += 1;
						(CGame::GetInstance().SetCameraPosition(CamPos));
						
					}
					break;
				case VK_UP:
					{
						D3DXVECTOR3 LookAt;
						LookAt = *(CGame::GetInstance().GetLookAt());
						LookAt.y += -1;
						(CGame::GetInstance().SetLookAt(LookAt));
						
						D3DXVECTOR3 CamPos;
						CamPos = *(CGame::GetInstance().GetCameraPosition());
						CamPos.y += -1;
						(CGame::GetInstance().SetCameraPosition(CamPos));

					}
					break;
				case VK_DOWN:
					{
						D3DXVECTOR3 LookAt;
						LookAt = *(CGame::GetInstance().GetLookAt());
						LookAt.y += 1;
						(CGame::GetInstance().SetLookAt(LookAt));
						
						D3DXVECTOR3 CamPos;
						CamPos = *(CGame::GetInstance().GetCameraPosition());
						CamPos.y += 1;
						(CGame::GetInstance().SetCameraPosition(CamPos));
					}
					break;
				}
			}
			break;
    }


	 //Handles any messages the switch statement doesn't
	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

/***********************
* CreateAndRegisterWindow: Create and register the window of the application 
* @author: Jc Fowles
* @Parameter: _hInstance: Instance handler for the application
* @Parameter: _iWidth: Width of the window
* @Parameter: _iHeight: Height of the window
* @Parameter: _pcTitle: Title of the window
* @return: HWND: Handle to the window
********************/
HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
	WNDCLASSEX winclass;

	//Clear out the window class for use
    ZeroMemory(&winclass, sizeof(WNDCLASSEX));

	//Fill in the struct with the needed information
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Register the window class
	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	//Create the window and return the result as the handle
	HWND hWnd;
	
	////Non-Full Screen
	hWnd = CreateWindowEx(	NULL,												// Extend style.
							WINDOW_CLASS_NAME,									// Class.		
							_pcTitle,											// Title.
							WS_OVERLAPPEDWINDOW | WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,	//Window stlye
							CW_USEDEFAULT, CW_USEDEFAULT,						// Initial x,y.
							_iWidth, _iHeight,									// Initial width, height.
							NULL,												// Handle to parent.
							NULL,												// Handle to menu.
							_hInstance,											// Instance of this application.
							NULL);												// Extra creation parameters.
	

	//Full Screen
	//hWnd = CreateWindowEx(	NULL,												// Extend style.
	//						WINDOW_CLASS_NAME,									// Class.		
	//						_pcTitle,											// Title.
	//						WS_EX_TOPMOST | WS_POPUP,							// Window stlye (fullscreen values)
	//						0, 0,												// Initial x,y.
	//						_iWidth, _iHeight,									// Initial width, height.
	//						NULL,												// Handle to parent.
	//						NULL,												// Handle to menu.
	//						_hInstance,											// Instance of this application.
	//						NULL);												// Extra creation parameters.
	

	//Check if window was created succesfully
	if (!hWnd)
	{
		// Failed to create.
		return (0);
	}

	//Return the handle to the window
	return (hWnd);
}

/***********************
* WinMain: The entry point for any Windows program
* @author: Jc Fowles
* @Parameter: _hInstance: Instance handle that Windows generates for your application
* @Parameter: _hPrevInstance: Tracker for the previous instance for the application
* @Parameter: _lpCmdline: Wide char string that contains the passed in arguments 
* @Parameter: _iCmdshow: Integer passed in during launch, indicating how the application window is opened
* @return: int: Program termination value
********************/
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	//Seed the random generator
	srand ((unsigned int)time(NULL));

	//Screen Resolution
	const int kiWidth = 1680; 
	const int kiHeight = 1050;
	
	//This holds Windows event messages
	MSG msg;

	//Clear out the event message for use
	ZeroMemory(&msg, sizeof(MSG));
	
	//Create and register the window
	HWND hWnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"2-Cube Renderer");
	
	// display the window on the screen
    ShowWindow(hWnd, _iCmdshow);

	//Create and initialize the Direct3D Device
	CGame& rGame = CGame::GetInstance();

	rGame.Initialize(hWnd, kiWidth, kiHeight);
			

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Render a single frame
			rGame.RenderFrame();		
		}
	}

	//rGame.Release();
	//Destroy the game instance
	rGame.DestroyInstance();


    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

