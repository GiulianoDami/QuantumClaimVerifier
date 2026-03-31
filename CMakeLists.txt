cmake_minimum_required(VERSION 3.14)
project(QuantumClaimVerifier LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework)
find_package(Eigen3 REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ClaimValidator.cpp
    src/StatisticalAnalyzer.cpp
    src/ReplicationTester.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES}
    Eigen3::Eigen
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    BOOST_TEST_DYN_LINK
)

enable_testing()
add_test(NAME QuantumClaimVerifierTests COMMAND ${PROJECT_NAME} --run_test=*)