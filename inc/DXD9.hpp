#ifndef DXD9_HPP
#define DXD9_HPP

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

IDirect3DDevice9Ex* retDXDEVICE();
int D3DIniti(HWND hWnd);
int Draw_Text(char* String, int x, int y, int r, int g, int b, int a);

#endif
