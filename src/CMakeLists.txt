add_executable(gluonsh main.c)

target_include_directories(gluonsh PUBLIC 
                            ${PROJECT_BINARY_DIR})