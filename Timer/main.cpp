#include "stdafx.h"

// ----------------------------------------------------------------------------------
// 전역상수
namespace constant {
    static const TCHAR Title[] = _T("Hello");
    static const UINT Width = 800U;
    static const UINT Height = 600U;
    static const bool Fullscreen = false;
}
// ----------------------------------------------------------------------------------



HWND initWin(HINSTANCE hInstance, int nCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, char[], int nCmdShow)
try {
    HWND hWnd = initWin(hInstance, nCmdShow);

    MSG message = {};
    while ( ::GetMessage(&message, nullptr, 0, 0) ) {
        ::TranslateMessage(&message);
        ::DispatchMessage(&message);
    }
    //while ( message.message != WM_QUIT ) {
    //    if ( ::PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) ) {
    //        ::TranslateMessage(&message);
    //        ::DispatchMessage(&message);
    //    } else {
    //        
    //    }
    //}
    
    return EXIT_SUCCESS;
} catch ( ErrorReporter& e ) {
    e.Report();
    ExitProcess(EXIT_FAILURE);
} catch ( std::exception& e ) {
    std::string text ( "프로그램 실행중 표준예외가 발생하였습니다 ( " );
	text.append ( typeid(e).name() );
	text.append ( " )\n ■ " );
	text.append ( e.what() );
    ErrorReporter ( text.c_str() ).Report();
    ExitProcess(EXIT_FAILURE);
} catch ( ... ) {
    ErrorReporter ( "프로그램 실행중 미처리예외가 발생하였습니다." ).Report();
    ExitProcess(EXIT_FAILURE);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static std::wstring text;
    static uclock_t begin = -1;
    static uclock_t end;

    switch ( msg ) {
    case WM_KEYDOWN:
        text += _T('●');
        goto APPEND_TEXT;
    case WM_KEYUP:
        text += _T('○');
        APPEND_TEXT:
        text += static_cast<wchar_t>(wParam);
        text += _T(" (");

        end = uclock();
        if ( -1 == begin ) begin = end;
        text += std::to_wstring(static_cast<long double>(end - begin));

        text += _T(")\n");
        InvalidateRect(hWnd, nullptr, TRUE);
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rt = { 10, 10, 10, 10 };
            DrawText(hdc, text.c_str(), text.length(), &rt, DT_NOCLIP);
		    EndPaint(hWnd, &ps);
        }
        return 0;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

// hWnd 초기화 편의함수
HWND initWin(HINSTANCE hInstance, int nCmdShow) {
    WNDCLASSEX window = {};
    window.cbSize = sizeof( WNDCLASSEX );
    window.style = CS_HREDRAW | CS_VREDRAW;
    window.lpfnWndProc = ::WndProc;
    window.hInstance = hInstance;
    window.hIcon = ::LoadIcon( hInstance, IDI_APPLICATION );
    window.hIconSm = ::LoadIcon( hInstance, IDI_APPLICATION );
    window.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
    window.lpszClassName = constant::Title;
    FALSE_THROW ( ::RegisterClassEx(&window) );

    HWND hWnd = ::CreateWindow( constant::Title, constant::Title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, constant::Width, constant::Height, nullptr, nullptr, hInstance, nullptr);
    FALSE_THROW_MSG ( hWnd, "::CreateWindow - failed" );

    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

    return hWnd;
}
