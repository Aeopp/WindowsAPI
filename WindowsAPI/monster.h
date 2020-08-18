#pragma once
#include "DrawObject.h"

template<typename DrawType>
class MoveableObject :
    public DrawObject<DrawType>
{
public:
     using super = DrawObject<DrawType>;

      MoveableObject(const float init_x, const float init_y, const float init_length,
      const float move_dir_x, const float move_dir_y);
private:
    float move_dir_x{};
    float move_dir_y{};
    bool bDie{ false}; 
public:
    void MoveByDir()&;
    virtual void Update();

    inline bool is_die()const&
    {
        return bDie;
    };
    inline void set_die(const bool die)
    {
        bDie = die;
    };
};

template<typename DrawType>
MoveableObject<DrawType>::MoveableObject
(const float init_x, 
   const float init_y, 
    const float init_length, 
    const float init_move_dir_x, 
    const float init_move_dir_y)
    :
    super(init_x,init_y,init_length)
    , move_dir_x{ init_move_dir_x }, move_dir_y{ init_move_dir_y }
{};

template<typename DrawType>
void MoveableObject<DrawType>::MoveByDir()&
{
    super::move(move_dir_x, move_dir_y);
};

template<typename DrawType>
 void MoveableObject<DrawType>::Update()
{
     MoveByDir();
};



