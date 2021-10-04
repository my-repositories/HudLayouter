#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <dwmapi.h>
#include <DXD9.hpp>
#include <hud.hpp>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

const MARGINS Margin = { -1 };

LRESULT CALLBACK Proc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
		return DwmExtendFrameIntoClientArea(hWnd, &Margin);
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR CmdLine, int CmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX OverlayWnd;
	OverlayWnd.cbSize = sizeof(WNDCLASSEX);
	OverlayWnd.style = CS_HREDRAW | CS_VREDRAW;
	OverlayWnd.lpfnWndProc = Proc;
	OverlayWnd.cbClsExtra = 0;
	OverlayWnd.cbWndExtra = 0;
	OverlayWnd.hInstance = hInstance;
	OverlayWnd.hIcon = LoadIcon(0, IDI_APPLICATION);
	OverlayWnd.hCursor = LoadCursor(0, IDC_ARROW);
	OverlayWnd.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	OverlayWnd.lpszMenuName = "HudLayouter";
	OverlayWnd.lpszClassName = "HudLayouter";
	OverlayWnd.hIconSm = LoadIcon(0, IDI_APPLICATION);

	if (!RegisterClassEx(&OverlayWnd))
	{
		exit(1);
	}

	int width, height;
	GetMonitorSizes(width, height);

	hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_COMPOSITED | WS_EX_TRANSPARENT, "HudLayouter", "HudLayouter", WS_EX_TOPMOST | WS_POPUP, 100, 100, width, height, NULL, NULL, NULL, NULL);

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
	ShowWindow(hWnd, SW_SHOW);
	D3DIniti(hWnd);

	bool isShow = true;
	int xx = 0, yy = 0;
	while (1)
	{
		if (!IsWindow(hWnd))
		{
			exit(1);
		}

		if (GetAsyncKeyState(VK_INSERT))
		{
			isShow = !isShow;
			Sleep(100);
		}

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			--yy;
		}

		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			++yy;
		}

		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			--xx;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			++xx;
		}

		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		//GetWindowRect(FindWindow(0, "Command Prompt"), &TargetRect);
		//MoveWindow(hWnd, TargetRect.left, TargetRect.top, TargetRect.right - TargetRect.left, TargetRect.bottom - TargetRect.top, true);

		MoveWindow(hWnd, xx, yy, width+15, height+15, true);
		RenderIt(retDXDEVICE(), isShow);
	}

	return 0;
}
