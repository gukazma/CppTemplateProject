project(myproject)


add_executable(${PROJECT_NAME} main.cpp)

add_test(NAME test1_1
                        COMMAND myproject 2 2)

set_property (TEST test1_1
    PROPERTY PASS_REGULAR_EXPRESSION "3")