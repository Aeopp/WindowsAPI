#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <list>
#include <memory>
#include <map>
#include <sstream>

#include "math.h"

#pragma warning ( disable : 4244)

using type_hash_type = decltype(std::declval<std::type_info>().hash_code());


