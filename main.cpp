#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include "hider.h"
#include "hider2.h"

using namespace std;


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[ ] = _T("Pudzian's quadratic functions");

// edit fields
HWND hEditA, hEditB, hEditC;
// label fields
HWND hLabelA, hLabelB, hLabelC;
// count button
HWND hButton;

// changeable labels
HWND hLabelW, hLabelP, hLabelQ, hLabelDelta, hLabelX1, hLabelX2, hLabelStandardForm, hLabelVertexForm, hLabelFactoredForm;

// photo
HBITMAP hbitmap;
HWND g_hObrazek;

float a, b, c;

char szBuffer[256]; // string buffer needed for getting values from inputs

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);


    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;


    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
               0,
               szClassName,
               _T("Pudzian's quadratic function counter"),
               WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
               CW_USEDEFAULT,
               CW_USEDEFAULT,
               1500,
               500,
               HWND_DESKTOP,
               NULL,
               hThisInstance,
               NULL
           );



    hEditA = CreateWindowEx(
                 0,
                 _T("EDIT"),
                 _T(""),
                 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                 50,
                 50,
                 100,
                 20,
                 hwnd,
                 NULL,
                 hThisInstance,
                 NULL
             );

    hEditB = CreateWindowEx(
                 0,
                 _T("EDIT"),
                 _T(""),
                 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                 50,
                 100,
                 100,
                 20,
                 hwnd,
                 NULL,
                 hThisInstance,
                 NULL
             );

    hEditC = CreateWindowEx(
                 0,
                 _T("EDIT"),
                 _T(""),
                 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                 50,
                 150,
                 100,
                 20,
                 hwnd,
                 NULL,
                 hThisInstance,
                 NULL
             );

    hLabelA = CreateWindowEx(
                  0,
                  _T("STATIC"),
                  _T("A:"),
                  WS_CHILD | WS_VISIBLE,
                  10,
                  50,
                  30,
                  20,
                  hwnd,
                  NULL,
                  hThisInstance,
                  NULL
              );

    hLabelB = CreateWindowEx(
                  0,
                  _T("STATIC"),
                  _T("B:"),
                  WS_CHILD | WS_VISIBLE,
                  10,
                  100,
                  30,
                  20,
                  hwnd,
                  NULL,
                  hThisInstance,
                  NULL
              );

    hLabelC = CreateWindowEx(
                  0,
                  _T("STATIC"),
                  _T("C:"),
                  WS_CHILD | WS_VISIBLE,
                  10,
                  150,
                  30,
                  20,
                  hwnd,
                  NULL,
                  hThisInstance,
                  NULL
              );

    hButton = CreateWindowEx(
                  0,
                  _T("BUTTON"),
                  _T("Policz"),
                  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                  50,
                  200,
                  100,
                  30,
                  hwnd,
                  (HMENU)1,
                  hThisInstance,
                  NULL
              );


    hLabelW = CreateWindowEx(
                  0,
                  _T("STATIC"),
                  _T("W=(x, y)"),
                  WS_CHILD | WS_VISIBLE,
                  200,
                  50,
                  200,
                  20,
                  hwnd,
                  NULL,
                  hThisInstance,
                  NULL
              );

    hLabelP = CreateWindowEx(
                  0,
                  _T("STATIC"),
                  _T("P="),
                  WS_CHILD | WS_VISIBLE,
                  200,
                  80,
                  200,
                  20,
                  hwnd,
                  NULL,
                  hThisInstance,
                  NULL
              );

    hLabelQ = CreateWindowEx(
                  0,
                  _T("STATIC"),
                  _T("Q="),
                  WS_CHILD | WS_VISIBLE,
                  200,
                  110,
                  200,
                  20,
                  hwnd,
                  NULL,
                  hThisInstance,
                  NULL
              );

    hLabelDelta = CreateWindowEx(
                      0,
                      _T("STATIC"),
                      _T("Delta="),
                      WS_CHILD | WS_VISIBLE,
                      200,
                      140,
                      200,
                      20,
                      hwnd,
                      NULL,
                      hThisInstance,
                      NULL
                  );

    hLabelX1 = CreateWindowEx(
                   0,
                   _T("STATIC"),
                   _T("x1="),
                   WS_CHILD | WS_VISIBLE,
                   200,
                   170,
                   200,
                   20,
                   hwnd,
                   NULL,
                   hThisInstance,
                   NULL
               );

    hLabelX2 = CreateWindowEx(
                   0,
                   _T("STATIC"),
                   _T("x2="),
                   WS_CHILD | WS_VISIBLE,
                   200,
                   200,
                   200,
                   20,
                   hwnd,
                   NULL,
                   hThisInstance,
                   NULL
               );

    hLabelStandardForm = CreateWindowEx(
                             0,
                             _T("STATIC"),
                             _T("Postac ogolna:"),
                             WS_CHILD | WS_VISIBLE,
                             200,
                             230,
                             350,
                             20,
                             hwnd,
                             NULL,
                             hThisInstance,
                             NULL
                         );
    hLabelVertexForm = CreateWindowEx(
                           0,
                           _T("STATIC"),
                           _T("Postac kanoniczna:"),
                           WS_CHILD | WS_VISIBLE,
                           200,
                           260,
                           350,
                           20,
                           hwnd,
                           NULL,
                           hThisInstance,
                           NULL
                       );

    hLabelFactoredForm = CreateWindowEx(
                             0,
                             _T("STATIC"),
                             _T("Postac iloczynowa:"),
                             WS_CHILD | WS_VISIBLE,
                             200,
                             290,
                             350,
                             40,
                             hwnd,
                             NULL,
                             hThisInstance,
                             NULL
                         );


    ShowWindow (hwnd, nCmdShow);


    while (GetMessage (&messages, NULL, 0, 0))
    {

        TranslateMessage(&messages);

        DispatchMessage(&messages);
    }


    return messages.wParam;
}



LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // menu creation
        HMENU hMenu = CreateMenu();
        HMENU hSubMenu = CreateMenu();

        AppendMenuW(hSubMenu, MF_STRING, 2, L"Wyczysc");
        AppendMenuW(hSubMenu, MF_STRING, 3, L"Wyjdz");
        AppendMenuW(hSubMenu, MF_STRING, 4, L"O mnie");

        AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Menu");

        SetMenu(hwnd, hMenu);

        // adding image
        g_hObrazek = CreateWindowEx(0, _T("Static"), NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, 0, 250, 200, 200, hwnd, NULL, NULL, NULL);
        hbitmap = (HBITMAP)LoadImage(NULL, "pudzian2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(g_hObrazek, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbitmap);
        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == 1)  // button click event
        {
            // Gets text
            GetWindowTextA(hEditA, szBuffer, sizeof(szBuffer));
            a = atof(szBuffer);

            GetWindowTextA(hEditB, szBuffer, sizeof(szBuffer));
            b = atof(szBuffer);

            GetWindowTextA(hEditC, szBuffer, sizeof(szBuffer));
            c = atof(szBuffer);

            // message warning box
            if (a > 30 || b > 30 || c > 30 || a < -30 || b < -30 || c < -30)
            {
                MessageBox(hwnd, _T("Podane wartoœci s¹ wyoskie i mog¹ niepoprawnie wyœwietlaæ siê na wykresie"), _T("Info"), MB_OK | MB_ICONINFORMATION);
            }


            float p = countP(a, b, c);
            float q = countQ(a, b, c);
            float delta = countDelta(a, b, c);

            // updating the labels
            TCHAR szResult[50];
            _stprintf(szResult, _T("W=(%f, %f)"), p, q);
            SetWindowText(hLabelW, szResult);

            _stprintf(szResult, _T("P=%f"), p);
            SetWindowText(hLabelP, szResult);

            _stprintf(szResult, _T("Q=%f"), q);
            SetWindowText(hLabelQ, szResult);

            _stprintf(szResult, _T("Delta=%f"), delta);
            SetWindowText(hLabelDelta, szResult);

            // quadratic functino checknig
            if (delta > 0)
            {
                float x1 = countX1(a, b, delta);
                float x2 = countX2(a, b, delta);

                _stprintf(szResult, _T("x1=%f"), x1);
                SetWindowText(hLabelX1, szResult);
                _stprintf(szResult, _T("x2=%f"), x2);
                SetWindowText(hLabelX2, szResult);
            }
            else if (delta == 0)
            {
                float x1 = countX1(a, b, delta);
                _stprintf(szResult, _T("x1=%f"), x1);
                SetWindowText(hLabelX1, szResult);
                _stprintf(szResult, _T("x2=brak"));
                SetWindowText(hLabelX2, szResult);
            }
            else
            {
                _stprintf(szResult, _T("x1=brak"));
                SetWindowText(hLabelX1, szResult);
                _stprintf(szResult, _T("x2=brak"));
                SetWindowText(hLabelX2, szResult);
            }

            TCHAR szResult2[256];
            _stprintf(szResult2, _T("Postac ogolna: %s"), standardForm(a, b, c).c_str()); // for strings
            SetWindowText(hLabelStandardForm, szResult2);

            _stprintf(szResult2, _T("Postac kanoniczna: %s"), vertexForm(a, b, c).c_str());
            SetWindowText(hLabelVertexForm, szResult2);

            _stprintf(szResult2, _T("Postac iloczynowa: %s"), factoredForm(a, b, c).c_str());
            SetWindowText(hLabelFactoredForm, szResult2);

            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
        }
        else if (LOWORD(wParam) == 2)
        {
            a = 0;
            b = 0;
            c = 0;
            SetWindowText(hEditA, _T(""));
            SetWindowText(hEditB, _T(""));
            SetWindowText(hEditC, _T(""));
        }
        else if (LOWORD(wParam) == 3)
        {
            PostQuitMessage(0); // exits app
        }
        else if (LOWORD(wParam) == 4)
        {
            MessageBox(hwnd, _T("Projekt zrobiony przez S³awka D¹browskiego"), _T("Info"), MB_OK | MB_ICONINFORMATION);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        // width of ui for drawings, so the graph doesnt interfere with ui
        int uiWidth = 560;


        RECT graphRect = { uiWidth, 0, clientRect.right, clientRect.bottom };

        // clearing graph
        FillRect(hdc, &graphRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

        DrawQuadraticGraph(hdc, a, b, c, graphRect);

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
