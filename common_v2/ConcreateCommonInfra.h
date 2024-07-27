#pragma once
#ifdef _AUTOSG_EXPORTS
#define AUTOSG_DECLSP   __declspec(dllexport) 
#else
#define AUTOSG_DECLSP   __declspec(dllimport)
#endif

AUTOSG_DECLSP void call_common_method_same_name();

