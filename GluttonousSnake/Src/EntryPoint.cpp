#include <iostream>

#include <Windows.h>
#include "Core/Tool.h"
#include "Application.h"

#include <vector>
#include <algorithm>
int main() {
    Application::Init();

    Application::GetInstance().Start();
    Application::GetInstance().Run();
    
    Application::Terminate();
    return 0;
}