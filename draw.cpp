#include <windows.h>
#include <sstream>
#include <iomanip>

float countY(float a, float b, float c, float x)
{
    return a * x * x + b * x + c;
}

void DrawQuadraticGraph(HDC hdc, float a, float b, float c, RECT graphRect)
{
    float startX = -46.0f;
    float endX = 46.0f;
    float stepX = 0.1f;
    int scale = 10;

    int offsetX = graphRect.left + (graphRect.right - graphRect.left) / 2;
    int offsetY = graphRect.bottom - (graphRect.bottom - graphRect.top) / 2;

    // adding and changing pen
    HPEN hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    SelectObject(hdc, hRedPen);

    // drawing the graph
    MoveToEx(hdc, offsetX + startX * scale, offsetY - countY(a, b, c, startX) * scale, NULL);
    for (float x = startX + stepX; x <= endX; x += stepX)
    {
        LineTo(hdc, offsetX + x * scale, offsetY - countY(a, b, c, x) * scale);
    }

    HPEN hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hBlackPen);

    // drawing y-axis
    MoveToEx(hdc, offsetX, graphRect.top, NULL);
    LineTo(hdc, offsetX, graphRect.bottom);

    // drawing x-axis
    MoveToEx(hdc, graphRect.left, offsetY, NULL);
    LineTo(hdc, graphRect.right, offsetY);

    // x-axis ticks
    for (float x = -40.0f; x <= 40.0f; x += 1.0f)
    {
        MoveToEx(hdc, offsetX + x * scale, offsetY - 5, NULL);
        LineTo(hdc, offsetX + x * scale, offsetY + 5);
    }

    // y-axis ticks
    for (float y = -40.0f; y <= 40.0f; y += 1.0f)
    {
        MoveToEx(hdc, offsetX - 5, offsetY - y * scale, NULL);
        LineTo(hdc, offsetX + 5, offsetY - y * scale);
    }

    DeleteObject(hRedPen);
    DeleteObject(hBlackPen);
}
