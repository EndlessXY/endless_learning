cmake_minimum_required(VERSION 3.8)
project(test_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(test_interfaces REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(include/test_service)

add_executable(add_two_ints_server src/service_adder_server.cpp)
ament_target_dependencies(add_two_ints_server
        rclcpp
        test_interfaces)

add_executable(add_two_ints_client src/service_adder_client.cpp)
ament_target_dependencies(add_two_ints_client
        rclcpp
        test_interfaces)

install(TARGETS
        add_two_ints_server
        add_two_ints_client
        DESTINATION lib/${PROJECT_NAME})

ament_package()
