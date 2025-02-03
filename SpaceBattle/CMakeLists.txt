# CMakeList.txt: проект CMake для SpaceBattle; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

add_library(SpaceBattle STATIC
  "Move.cpp" "Move.h" 
  "IMovable.h"
  "Vector2d.cpp" "Vector2d.h" 
  "Angle.cpp" "Angle.h"
  "IRotatable.h"
  "Rotate.cpp" "Rotate.h"
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SpaceBattle PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
