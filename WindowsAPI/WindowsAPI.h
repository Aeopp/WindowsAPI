#pragma once

#include "resource.h"
#include "pch.h"
#include "framework.h"

#define MAX_LOADSTRING 100

// 전역 변수:
namespace global
{
	static HINSTANCE hInst;                                // 현재 인스턴스입니다.
	static WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	static WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	static HWND hWnd;
}


