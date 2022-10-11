#pragma once
#include "pch.h"

// 
#ifndef __MSVC__
#define __debugbreak() getchar()
#endif

#define ASSERT(x) if(!(x)) {__debugbreak();}

#ifdef DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

// Loop until there are no errors left.
void GLClearError();

// Request the current error state
bool GLLogCall(const char* function, const char* file, int line);