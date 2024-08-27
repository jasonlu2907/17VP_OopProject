// GDIPLUSTEST.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "GDIPLUSTEST.h"
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <iostream>
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                     // current instance
WCHAR szTitle[MAX_LOADSTRING];       // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: Place code here.
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;

  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  // Initialize global strings
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_GDIPLUSTEST, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDIPLUSTEST));

  MSG msg;

  // Main message loop:
  while (GetMessage(&msg, nullptr, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  // Ket thuc GDI+
  GdiplusShutdown(gdiplusToken);

  return (int)msg.wParam;
}

//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {

  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDIPLUSTEST));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GDIPLUSTEST);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//   In this function, we save the instance handle in a global variable and
//   create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  // Store instance handle in our global variable
  hInst = hInstance;

  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd)
  {
    return FALSE;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_COMMAND: {
  
    int wmId = LOWORD(wParam);
    // Parse the menu selections:
    switch (wmId)
    {
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  }
  break;
  case WM_PAINT: {
  
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    vector<PointF> ar1 = {PointF(25, 25), PointF(20, 20)};
    rectangle R(ar1);
    R.MyPaint(hdc);

    ellipse e(PointF(0, 200), 60, 60);
    e.MyPaint(hdc);

    star(hdc);

    vector<PointF> ar2 = {PointF(10, 30), PointF(30, 10), PointF(30, 30), PointF(50, 10), PointF(50, 30), PointF(70, 10), PointF(70, 30), PointF(90, 10),
                          PointF(90, 30), PointF(110, 10)};
    polyLine po(ar2);
    po.MyPaint(hdc);

    vector<PointF> ar3 = {PointF(850, 75), PointF(958, 137), PointF(958, 262), PointF(850, 325), PointF(742, 262), PointF(742, 137)};
    polygon p(ar3);
    p.MyPaint(hdc);

    ifstream inPut("inPut.svg");
    ofstream outPut("outPut.svg");
    rapidxml::xml_document<> doc;

    // Read file into vector<char>
    // Test the buffer
    vector<char> buffer((istreambuf_iterator<char>(inPut)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    cout << &buffer[0] << endl;
    doc.parse<0>(&buffer[0]);

    rapidxml::xml_node<> *pNode = doc.first_node();
    // polyline / line / circle...
    outPut << "<" << pNode->name() << " ";
    for (rapidxml::xml_attribute<> *i = pNode->first_attribute(); i; i = i->next_attribute())
    {
      // stroke / width / height...
      outPut << i->name() << "=\"" << i->value() << "\" ";
    }
    outPut << ">" << endl;
    if (pNode != nullptr)
    {
      rapidxml::xml_node<> *child = pNode->first_node();
      while (child != nullptr)
      {
        outPut << "\t<" << child->name() << " ";
        for (rapidxml::xml_attribute<> *i = child->first_attribute(); i; i = i->next_attribute())
        {
          outPut << i->name() << "=\"" << i->value() << "\" ";
        }
        outPut << "/>\n";
        child = child->next_sibling();
      }
    }
    outPut << "</" << pNode->name() << ">";

    EndPaint(hWnd, &ps);
  }
  break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Message handler for about box.
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
