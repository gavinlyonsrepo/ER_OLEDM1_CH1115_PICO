# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.18)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(ch1115 C CXX ASM)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# turn on all compiler warnings
add_compile_options(-Wall -Wextra )

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
  examples/ER_OLEDM1_CH1115_HELLO/main.cpp
  #examples/ER_OLEDM1_CH1115_BITMAP/main.cpp
  #examples/ER_OLEDM1_CH1115_FPS_FUNCTIONS/main.cpp
  #examples/ER_OLEDM1_CH1115_TEXT_GRAPHICS/main.cpp
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

add_library(pico_ch1115 INTERFACE)

target_sources(pico_ch1115 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/ch1115/ER_OLEDM1_CH1115.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ch1115/ER_OLEDM1_CH1115_graphics.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ch1115/ER_OLEDM1_CH1115_Print.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/ch1115/ER_OLEDM1_CH1115_font.cpp
)

target_include_directories(pico_ch1115 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_spi pico_ch1115 )


# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

