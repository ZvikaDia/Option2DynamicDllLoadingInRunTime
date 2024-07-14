// ComSupport.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include <Windows.h>
#include <yaml-cpp/yaml.h>
#include <string>
#include <stdexcept>
#include <iostream>

// TODO: This is an example of a library function
void fnComSupport()
{
}


IUnknown* CreateObjectFromYaml(const std::string& cls_to_create, const std::string& interface_name) {
    // Load YAML file

    char* demo_configuration_file = nullptr;
    size_t sz = 0;
    _dupenv_s(&demo_configuration_file, &sz, "demo_configuration_file");
    
    printf("EnvVarName = %s\n", demo_configuration_file);
    

    YAML::Node config = YAML::LoadFile(demo_configuration_file);

    // Find DLL path for the given object ID
    std::string dllPath;
    std::string class_name;
    try {
        dllPath = config[cls_to_create]["dllPath"].as<std::string>();
    }
    catch (const YAML::Exception& e) {
        throw std::runtime_error("Failed to find DLL path for object ID: " + cls_to_create);
    }

    // Load the DLL
    HMODULE hModule = LoadLibraryA(dllPath.c_str());
    if (!hModule) {
        throw std::runtime_error("Failed to load DLL: " + dllPath);
    }

    // Get the function address for object creation
    typedef HRESULT(*CreateObjectFunc)(std::string riid, void** ppv);
    CreateObjectFunc createObject = (CreateObjectFunc)GetProcAddress(hModule, "CreateObject");
    if (!createObject) {
        FreeLibrary(hModule);
        throw std::runtime_error("Failed to get CreateObject function from DLL");
    }

    // Create the object
    IUnknown* pUnknown = nullptr;
    HRESULT hr = createObject(interface_name, (void**)&pUnknown);
    if (FAILED(hr)) {
        FreeLibrary(hModule);
        throw std::runtime_error("Failed to create object");
    }

    return pUnknown;
}
