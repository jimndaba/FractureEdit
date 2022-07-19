#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <istream>
#include <sstream>
#include <ostream>
#include <functional>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <random>
#include <chrono>
#include <iomanip>
#include <thread>
#include <future>
#include <mutex>          // std::mutex, std::lock_guard
#include <execution>
#include <typeinfo> 
#include <stack>
#include <queue>
#include <list>
#include <type_traits>
#include <typeindex>
#include <filesystem>
#include <Windows.h>


#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"


#include "glad/glad.h"

#define GLM_FORCE_NO_CTOR_INIT 
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp> 
#include "glm/gtx/compatibility.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "optick/optick.h"

#include "json/json.hpp"
using namespace nlohmann;

#include "core/UUID.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"