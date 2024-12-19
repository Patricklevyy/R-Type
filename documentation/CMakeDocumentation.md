# R-Type Project CMake Build System

## Overview
This CMake script is designed to configure and build the R-Type project, a game project structured with a client-server architecture. It supports dependency management using Vcpkg, organizes source files, and sets up executable targets for both client and server components. The script is highly modular and incorporates automatic dependency installation and management.

## Prerequisites
Before using this CMake script, ensure the following tools and libraries are installed:
- **CMake** (version 3.21 or later)
- **Git**
- **Vcpkg** (automatically handled by the script if not set up)
- **C++17 compiler**

## Features
1. **Dependency Management:**
   - Uses [Vcpkg](https://github.com/microsoft/vcpkg) for package management.
   - Automatically clones and sets up Vcpkg if not already available.
   - Activates Vcpkg's manifest mode if `vcpkg.json` is present in the project directory.

2. **Dependencies:**
   - `fmt` (formatted output library)
   - `libconfig` (configuration file library)
   - `SFML` (Simple and Fast Multimedia Library) for graphical and audio components

3. **Source Organization:**
   - Client-specific code is located in `rtype_game/client/`.
   - Server-specific code is located in `rtype_game/server/`.
   - Shared code between client and server resides in `rtype_game/shared/`.
   - Additional functionality is implemented in the `ecs/` directory.

4. **Build Outputs:**
   - Generates two executables:
     - `r-type_client` for the client application
     - `r-type_server` for the server application
   - All runtime files are placed in the CMake binary directory.

## Usage Instructions

### 1. Clone the Repository
Clone the R-Type project repository into your working directory:
```bash
git clone <repository-url>
cd <repository-folder>
```

### 2. Configure the Project
Run CMake to configure the project. Ensure you specify the desired build directory:
```bash
cmake -S . -B build
```

### 3. Build the Project
Compile the project using the generated build files:
```bash
cmake --build build
```

### 4. Run the Executables
Run the client and server executables:
```bash
./build/r-type_client
./build/r-type_server
```

## Key Script Sections

### Minimum Requirements
```cmake
cmake_minimum_required(VERSION 3.21)
project(RType LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)
```
This ensures the project uses C++17, with warnings enabled for better code quality.

### Vcpkg Integration
```cmake
if(NOT DEFINED ENV{VCPKG_ROOT})
    message(STATUS "Vcpkg not found in environment. Cloning and setting up vcpkg...")
    execute_process(COMMAND git clone https://github.com/microsoft/vcpkg.git ${CMAKE_BINARY_DIR}/vcpkg)
    execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg)
    set(ENV{VCPKG_ROOT} "${CMAKE_BINARY_DIR}/vcpkg")
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
```
This block ensures Vcpkg is set up and integrated with the CMake build system.

### Dependency Management
```cmake
find_package(fmt CONFIG REQUIRED)
find_package(libconfig CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
```
This block finds required packages using CMake's `find_package` command.

### Source File Management
```cmake
file(GLOB_RECURSE CLIENT_SRC
    "${CMAKE_SOURCE_DIR}/rtype_game/client/*.cpp"
    "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp"
    "${CMAKE_SOURCE_DIR}/ecs/*.cpp"
)

file(GLOB_RECURSE SERVER_SRC
    "${CMAKE_SOURCE_DIR}/rtype_game/server/*.cpp"
    "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp"
    "${CMAKE_SOURCE_DIR}/ecs/*.cpp"
)
```
This block organizes source files for both the client and server executables.

### Target Creation
```cmake
add_executable(r-type_client ${CLIENT_SRC})
add_executable(r-type_server ${SERVER_SRC})

resolve_dependency(r-type_client fmt::fmt)
resolve_dependency(r-type_server fmt::fmt)
resolve_dependency(r-type_client libconfig::config++)
resolve_dependency(r-type_server libconfig::config++)

target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)
target_link_libraries(r-type_server PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)
```
This block creates and links the client and server targets with their dependencies.

## Additional Notes
- **Installation:** The script installs the binaries in the `bin` directory within the build folder.
- **Customization:**
  - Modify `add_compile_options` to include custom compiler flags.
  - Extend the `find_package` section to include additional dependencies.

## Troubleshooting
- Ensure that Vcpkg is properly cloned and bootstrapped if issues arise during dependency resolution.
- Verify the correctness of the `vcpkg.json` file for specifying dependency versions.
- Use `cmake --trace` for detailed debugging information during the configuration process.

