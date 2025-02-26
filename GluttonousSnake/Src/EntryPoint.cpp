#include <iostream>

#include <Windows.h>
#include "Core/Tool.h"
#include "Application.h"

int main() {
    Application::Init();

    Application::GetInstance().Start();
    Application::GetInstance().Run();
    
    Application::Terminate();
    return 0;
}