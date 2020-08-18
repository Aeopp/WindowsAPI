// WindowsAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "WindowsAPI.h"
#include "Bullet.h"
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include "monster.h"
#include "player.h"

namespace global 
{
    player<draw_rect> _tank{};
    MoveableObject<draw_rect> _monster;

    std::vector<MoveableObject<draw_rect>>monsters;
    std::vector<Bullet<draw_circle>> bullets;

    void Fire(const float, const float, const float, const float, const float,const float);

    static void Logic()
    {
        if(hWnd)
        {
            global::_tank.Update();

            for (auto& bullet : bullets)
            {
                bullet.Update(hWnd);
            }
            for (auto& monster : monsters)
            {
				monster.MoveByDir();
            }
        }
        for (auto iter = std::begin(bullets); iter != std::end(bullets);)
        {
            if (iter->IsDie())
            {
                iter = bullets.erase(iter);
            }
            else 
            {
                for (auto monster_iter = std::begin(monsters); 
                monster_iter != std::end(monsters); )
                {
                    RECT intersect_rect{};
                    RECT dst_rect = iter->get_rect();
                    RECT src_rect = monster_iter->get_rect();

                    bool is_intersect = IntersectRect(&intersect_rect, &dst_rect, &src_rect);

                    if (is_intersect)
                    {
                        monster_iter->set_die(true);
                        monster_iter = monsters.erase(monster_iter);
                    }
                    else
                    {
                        ++monster_iter;
                    }
                };
                ++iter; 
            }
        }
    };
    static std::pair<float, float> get_player_to_mouse_dir(const float x, const float y, const float length)
    {
        POINT _mouse_pt;
        GetCursorPos(&_mouse_pt);
        _mouse_pt.x -= x;
        _mouse_pt.y -= y;
        float dir_length = std::sqrt(std::pow(_mouse_pt.x, 2) + std::pow(_mouse_pt.y, 2));

        float dir_x = _mouse_pt.x / dir_length;
        float dir_y = _mouse_pt.y / dir_length;

        return { dir_x,dir_y };
    };

    static void fire_from_player_to_mouse(const float x, const float y, const float length,const float 
    speed)
    {
        POINT _mouse_pt;
        GetCursorPos(&_mouse_pt);
        _mouse_pt.x -= x;
        _mouse_pt.y -= y;
        float dir_length = std::sqrt(std::pow(_mouse_pt.x, 2) + std::pow(_mouse_pt.y, 2));

        float dir_x = _mouse_pt.x / dir_length;
        float dir_y = _mouse_pt.y / dir_length;
       global::Fire(x, y, length, dir_x, dir_y,speed);
    }
    static void Fire(
        const float x,
        const float y,
        const float length,
        const float dir_x,
        const float dir_y,
        const float speed)
    {
        bullets.emplace_back(x, y, length, dir_x, dir_y,speed);
    };
}

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, global::szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSAPI, global::szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSAPI));

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    // 기본 메시지 루프입니다:
    while (WM_QUIT!=msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            GetMessage(&msg, NULL, 0, 0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            global::Logic();

            InvalidateRect(global::hWnd, nullptr, false);
            UpdateWindow(global::hWnd);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSAPI);
    wcex.lpszClassName  = global::szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    global::hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   global::hWnd = CreateWindowW(global::szWindowClass, global::szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!global::hWnd)
   {
      return FALSE;
   }

   ShowWindow(global::hWnd, nCmdShow);
   UpdateWindow(global::hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(global::hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case 'A':
            global::_tank.add_barrel_angle(math::degree_to_radian(-5.f));
            break;
        case 'D':
			global::_tank.add_barrel_angle(math::degree_to_radian(+5.f));
            break;
        case 'W':
            global::_tank.move_from_barrel_dir(true);
            break;
        case 'S':
			global::_tank.move_from_barrel_dir(false);
            break;
        case VK_SPACE:
            global::_tank.fire_from_barrel();
            break;
        case VK_TAB:
            auto monster_spawn{ [] (const float spawn_x,const float spwan_y)
                {
                    const auto[x,y] =  global::get_player_to_mouse_dir
                                   (global::_tank.get_center().first,
                                    global::_tank.get_center().second,
                                    25.0f);
                   
					global::monsters.emplace_back(spawn_x, spwan_y, 25.f, x, y);
                } };

            monster_spawn(1, 1);
            break;
        default:
            break;
        }
        break;
    case WM_PAINT: {
        /** 더블버퍼링 시작처리입니다. **/
        static HDC hdc, MemDC, tmpDC;
        static HBITMAP BackBit, oldBackBit;
        static RECT bufferRT;
        PAINTSTRUCT ps;

        hdc = BeginPaint(hWnd, &ps);
        
		// TODO: 여기에 그리기 코드를 추가합니다.
        
        GetClientRect(hWnd, &bufferRT);
        MemDC = CreateCompatibleDC(hdc);
        BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
        oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
        PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
        tmpDC = hdc;
        hdc = MemDC;
        MemDC = tmpDC;

        // 총알의 경계선을 지정합니다.
        // 경계선 사이즈 만큼 클라이언트 좌표에서 줄여서 사각형을 그립니다.
        
        using dummy = char;

        Bullet<dummy>::Draw_bullet_fence(hdc);
      
        global::_tank.Draw(hdc);
     
        for (auto& monster : global::monsters)
        {
            monster.Draw(hdc);
        }
        for (auto& bullet : global::bullets)
        {
			bullet.Draw(hdc);
        }

        RECT rt{ 0,0,250,250 };
        std::wstringstream ss;

        ss << L"총알 개수 : " << global::bullets._size() << "\n\n";
        ss << L"몬스터 숫자 : " << global::monsters._size() << "\n\n";

        DrawText(hdc, ss.str().c_str(), -1, &rt, DT_CENTER | DT_WORDBREAK);
        
        /** 더블버퍼링 끝처리 입니다. **/
        tmpDC = hdc;
        hdc = MemDC;
        MemDC = tmpDC;
        GetClientRect(hWnd, &bufferRT);
        BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
        SelectObject(MemDC, oldBackBit);
        DeleteObject(BackBit);
        DeleteDC(MemDC);
        EndPaint(hWnd, &ps);
        break;
    }        
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
