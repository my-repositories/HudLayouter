#include <hud.hpp>
#include <strsafe.h>

int RenderIt(IDirect3DDevice9Ex* dx_Device, bool isShow)
{
	dx_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	dx_Device->BeginScene();
	if (isShow)
	{
		CHAR text[13] = {};
		SYSTEMTIME time;
		GetLocalTime(&time);
		sprintf_s(text, "%02u:%02u:%02u", time.wHour, time.wMinute, time.wSecond);
		Draw_Text(text, 0, 0, 255, 255, 255, 255);
	}

	dx_Device->EndScene();

	dx_Device->PresentEx(NULL, NULL, NULL, NULL, NULL);

	return 0;
}

void GetMonitorSizes(int& width, int& height)
{
	HMONITOR hMonitor = MonitorFromWindow(GetActiveWindow(), MONITOR_DEFAULTTOPRIMARY);
	MONITORINFOEX monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFOEX);
	if (GetMonitorInfo(hMonitor, &monitorInfo) == TRUE)
	{
		width = monitorInfo.rcWork.right;
		height = monitorInfo.rcWork.bottom;
	}
	else
	{
		width = 2560;
		height = 1440;
	}
}