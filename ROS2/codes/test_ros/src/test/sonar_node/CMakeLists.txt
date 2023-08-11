cmake_minimum_required(VERSION 3.5)
project(sonar_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(OpenCV REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS}
        ${CUDA_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include
        )
message(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_LIBRARIES})

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

include_directories(include/sonar_pub)
file(GLOB_RECURSE SRC_DIR ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(sonar_pub
        src/sonar_pub.cpp
        )

target_link_libraries(sonar_pub
        ${OpenCV_LIBRARIES})

ament_target_dependencies(sonar_pub
        rclcpp
        std_msgs
        sensor_msgs
        cv_bridge
        image_transport
        rclcpp_components
        OpenCV
        )

install(TARGETS
        sonar_pub
        DESTINATION lib/${PROJECT_NAME})

ament_package()
