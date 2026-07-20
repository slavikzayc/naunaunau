cmake_minimum_required(VERSION 3.14)  # FetchContent_MakeAvailable появился с 3.14
project(MyJsonProject LANGUAGES CXX)

# --- Подтягиваем nlohmann/json ---
include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY  https://github.com/nlohmann/json.git
  GIT_TAG         v3.11.3   # можешь сменить на latest или конкретную версию
  GIT_SHALLOW     TRUE      # скачиваем только нужный коммит (быстрее)
)

FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 23)

# --- Твой исполняемый файл / библиотека ---
add_executable(my_app
  main.cpp
  Components/Entity.h
  Components/Components.h
  Systems/MovementSystem.h
  Systems/MovementSystem.cpp
  World/World.h
  World/World.cpp
  WorldSerializer/WorldSerializer.h
  WorldSerializer/WorldSerializer.cpp
  # сюда добавишь свои .cpp/.h файлы
 "Components/Components.h" "World/World.h" "World/World.cpp" "Systems/MovementSystem.h" "Systems/MovementSystem.cpp" "WorldSerializer/WorldSerializer.h" "WorldSerializer/WorldSerializer.cpp")

# Линкуем header-only библиотеку
target_link_libraries(my_app PRIVATE nlohmann_json::nlohmann_json)

# --- Единые настройки стандарта C++ ---
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # отключаем расширения компилятора (чистый стандарт)

# --- Специфичные для MSVC (Visual Studio) настройки ---
if(MSVC)
  # Включаем подробные предупреждения, строгий режим соответствия стандарту,
  # правильный макрос __cplusplus и принудительно UTF-8 для исходников.
  target_compile_options(my_app PRIVATE
    /W4                  # уровень предупреждений 4
    /permissive-         # строгое следование стандарту (не пропускает некоторые вольности MSVC)
    /Zc:__cplusplus      # чтобы __cplusplus показывал реальную версию стандарта
    /utf-8               # исходники в UTF-8 (и исходный, и исполняемый наборы символов)
  )

  # По желанию: можно управлять рантайм-библиотекой (статическая/динамическая)
  # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") # статическая
endif()