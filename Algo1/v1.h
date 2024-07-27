#pragma once
#include <Windows.h>

#include <string>
#include <stdexcept>
#include <iostream>


#ifdef _AUTOSG_EXPORTS_ALG
#define AUTOSG_DECLSP_ALG   __declspec(dllexport) 
#else
#define AUTOSG_DECLSP_ALG   __declspec(dllimport)
#endif

AUTOSG_DECLSP_ALG void call_Elad_test_Algo1();