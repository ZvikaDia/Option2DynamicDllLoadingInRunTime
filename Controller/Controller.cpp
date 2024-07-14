// Controller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <yaml-cpp/yaml.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include "D:\Projects\Option2DynamicDllLoadingInRunTime\CommonInterfaces\DemoComminInterfaces.h"
#include "D:\Projects\Option2DynamicDllLoadingInRunTime\ComSupport\comsupport.h"

int main()
{
    std::cout << "Starting!\n";

    _putenv("demo_configuration_file=D:/Projects/Option2DynamicDllLoadingInRunTime/Controller/demo_config_permutation_1.yaml");

    ISayHello* theSayHello = (ISayHello * )CreateObjectFromYaml("Algo1", "v1");

    theSayHello->Hello();

    theSayHello->Release();

    theSayHello = (ISayHello*)CreateObjectFromYaml("Algo1", "v2");

    theSayHello->Hello();

    theSayHello->Release();

    _putenv("demo_configuration_file=D:/Projects/Option2DynamicDllLoadingInRunTime/Controller/demo_config_permutation_2.yaml");

    ISayHello* theSayHello2 = (ISayHello*)CreateObjectFromYaml("Algo2", "v1");

    theSayHello2->Hello();

    theSayHello2->Release();


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
