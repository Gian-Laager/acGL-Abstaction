#include <acGL_Abstraction.h>

int main()
{
//    glAbs::MainWindowSettings::getInstance()->runMainLoopInParallel = true;
    glAbs_Init();
    glAbs::hello_GL();
    return 0;
}
