#pragma once

#include "resource.h"
#include "pch.h"
#include "framework.h"

#define MAX_LOADSTRING 100

// ���� ����:
namespace global
{
	static HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
	static WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	static WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	static HWND hWnd;
}


