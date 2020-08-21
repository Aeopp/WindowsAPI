#pragma once
#include "Obj.h"
class Line :
    public CObj 
{
public :
    segment _segment{};

    using super = CObj;

    virtual ~Line()noexcept;
    // CObj을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC _DC) override;
    virtual void Release() override;
public:
    void set_segment(segment _segment) { this->_segment = _segment; }
    float y();
};

