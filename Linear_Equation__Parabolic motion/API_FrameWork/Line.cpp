#include "stdafx.h"
#include "Line.h"

Line::~Line() noexcept
{
};

void Line::Initialize()
{

}

int Line::Update()
{
    return OBJ_NOEVENT;
}

void Line::Late_Update()
{

}

void Line::Render(HDC _DC)
{
    MoveToEx(_DC, _segment.v0.x, _segment.v0.y, nullptr);
    LineTo(_DC, _segment.v1.x, _segment.v1.y);
}

void Line::Release()
{

}

float Line::y()
{
    return atan((_segment.v1.y - _segment.v0.y) / (_segment.v1.x - _segment.v1.x));
}
