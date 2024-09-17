#include "hider.h"
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

float countP(float a, float b, float c)
{
    return -b / (2 * a);
}
float countQ(float a, float b, float c)
{
    float delta = countDelta(a, b, c);
    return -delta / (4 * a);
}
float countDelta(float a, float b, float c)
{
    return b * b - 4 * a * c;
}

float countX1(float a, float b, float delta)
{
    return (-b + sqrt(delta)) / (2 * a);
}

float countX2(float a, float b, float delta)
{
    return (-b - sqrt(delta)) / (2 * a);
}

string standardForm(float a, float b, float c)
{
    ostringstream result;
    result << "f(x) = " << a << "*x^2 + " << b << "*x + " << c;
    return result.str();
}

string vertexForm(float a, float b, float c)
{
    ostringstream result;
    result << "f(x) = " << a << "*(x - (" << countQ(a, b, c) << "))^2 + " << countP(a, b, c);
    return result.str();
}

string factoredForm(float a, float b, float c)
{
    ostringstream result;

    float delta = countDelta(a, b, c);

    if (delta > 0)
    {
        float x1 = countX1(a, b, delta);
        float x2 = countX2(a, b, delta);

        result << "f(x) = " << a << "*(x - " << x1 << ")*(x - " << x2 << ")";
    }
    else if (delta == 0)
    {
        float x1 = countX1(a, b, delta);
        result << "f(x) = " << a << "*(x - " << x1 << ")^2";
    }
    else
    {
        result << "brak";
    }

    return result.str();
}
