#ifndef ACGL_ABSTRACTION_PCH_H
#define ACGL_ABSTRACTION_PCH_H

#define GLEW_STATIC

////open gl error handling
#define glCall(x) GLErrorHandling::clearError();\
    x;\
    assert(GLErrorHandling::logCall(#x, __FILE__, __LINE__))

namespace glAbs::GLErrorHandling
{
    void clearError();

    bool logCall(const char* function, const char* file, int line);
}

////including dependencies
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
//glm
#include "glm.hpp"
#include "gtx/string_cast.hpp"
#include "gtc/type_ptr.hpp"

////including standard library
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <array>
#include <future>

#endif //ACGL_ABSTRACTION_PCH_H
