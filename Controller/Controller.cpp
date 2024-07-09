// Controller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <yaml-cpp/yaml.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include "D:\Projects\Option2DynamicDllLoadingInRunTime\CommonInterfaces\DemoComminInterfaces.h"
IUnknown* CreateObjectFromYaml(const std::string& cls_to_create , const std::string& interface_name ) {
    // Load YAML file
    YAML::Node config = YAML::LoadFile("config.yaml");

    // Find DLL path for the given object ID
    std::string dllPath;
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
    typedef HRESULT(*CreateObjectFunc)(REFIID riid, void** ppv);
    CreateObjectFunc createObject = (CreateObjectFunc)GetProcAddress(hModule, "CreateObject");
    if (!createObject) {
        FreeLibrary(hModule);
        throw std::runtime_error("Failed to get CreateObject function from DLL");
    }

    // Create the object
    IUnknown* pUnknown = nullptr;
    HRESULT hr = createObject(__uuidof(IUnknown), (void**)&pUnknown);
    if (FAILED(hr)) {
        FreeLibrary(hModule);
        throw std::runtime_error("Failed to create object");
    }

    return pUnknown;
}

int main()
{
    std::cout << "Hello World!\n";

    ISayHello* theSayHello = (ISayHello * )CreateObjectFromYaml("Algo1_v1", "ISayHello");

    theSayHello->Hello();

     theSayHello->Release();




}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
