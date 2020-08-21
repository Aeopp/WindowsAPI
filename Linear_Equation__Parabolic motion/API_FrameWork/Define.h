#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 800
#define WINCY 600

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1
#define g 20.8f

#define PI 3.1415f

#endif // !__DEFINE_H__
