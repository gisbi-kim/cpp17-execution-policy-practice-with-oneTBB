# 최소 CMake 버전 설정
cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 설정
project(MyApp)

# C++20 표준 사용 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 컴파일러 최적화 옵션 설정
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# 실행 파일 생성
add_executable(main main.cpp)

# PARALLEL 매크로 정의
target_compile_definitions(main PRIVATE PARALLEL)

# TBB 라이브러리 링크
find_package(TBB REQUIRED)
target_link_libraries(main TBB::tbb)
