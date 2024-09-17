#ifndef HIDER_H_INCLUDED
#define HIDER_H_INCLUDED
#include <string>

using namespace std;

float countP(float a, float b, float c);
float countQ(float a, float b, float c);
float countDelta(float a, float b, float c);
float countX1(float a, float b, float delta);
float countX2(float a, float b, float delta);
string standardForm(float a, float b, float c);
string vertexForm(float a, float b, float c);
string factoredForm(float a, float b, float c);

#endif // HIDER_H_INCLUDED
