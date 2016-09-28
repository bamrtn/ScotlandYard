#include "openGL.h"
#include "MlinkWIN.h"
#include "IlinkWIN.h"
#include <stdio.h>

bool e = TRUE;
bool rbutton = false;

struct timespec {
	time_t   tv_sec;
	long     tv_nsec;
};

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM	wParam,LPARAM lParam){
	switch (uMsg){
		case WM_SYSCOMMAND:{
			switch (wParam){
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
			return 0;
			}
		break;
		}
		case WM_MOUSEMOVE:{
							  MouseMove(LOWORD(lParam),HIWORD(lParam));
							  break;
		}
		case WM_RBUTTONDOWN:{
								rbutton = true;
							  break;
		}
		case WM_RBUTTONUP:{
							  rbutton = false;
							  break;
		}
		case WM_LBUTTONUP:{
							  Click();
							  break;
		}
		/*case WM_CHAR:
			switch (wParam)
			{
			case 0x08:
				break;

			case 0x0A:
				break;

			case 0x1B:
				Escape();
				break;

			case 0x09:
				break;

			case 0x0D:
				break;

			default:
				Key((TCHAR)wParam);
				break;
			}*/
		case WM_KEYDOWN:{
							Key(wParam);
							break;
		}
		case WM_CLOSE:{
			PostQuitMessage(0);
			return 0;
		}
		case WM_SIZE:{
			wwidth = LOWORD(lParam);
			wheight = HIWORD(lParam);
			ReSizeGLScene();
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG	msg;
	timespec tstart = {0,0}, tend = {0,0};
	LARGE_INTEGER ST, ET, EM;
	LARGE_INTEGER F;
	EM.QuadPart = 0;
	freopen("myfile.txt", "w", stdout);
	QueryPerformanceFrequency(&F);
	Init();
	if (!CreateGLWindow("OpenGL Window", 1248, 702, 16, fullscreen))
	{
		return 0;
	}
	while (e)
	{
		QueryPerformanceCounter(&ST);
		Cycle(EM.QuadPart);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				e = FALSE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		DrawGLScene();
		SwapBuffers(hDC);
		QueryPerformanceCounter(&ET);
		EM.QuadPart = ET.QuadPart - ST.QuadPart;
		EM.QuadPart *= 1000;
		EM.QuadPart /= F.QuadPart;
	}
	KillGLWindow();
	return (msg.wParam);
}
