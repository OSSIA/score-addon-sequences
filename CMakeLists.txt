project(score_addon_sequence LANGUAGES CXX)

# General initialization
score_common_setup()

# Source files
set(HDRS
    sequence/Executor.hpp
    sequence/Inspector.hpp
    sequence/LocalTree.hpp
    sequence/Metadata.hpp
    sequence/Presenter.hpp
    sequence/Process.hpp
    sequence/View.hpp
    sequence/Layer.hpp
    sequence/CommandFactory.hpp

    score_addon_sequence.hpp
)
set(SRCS
    sequence/Executor.cpp
    sequence/Inspector.cpp
    sequence/LocalTree.cpp
    sequence/Presenter.cpp
    sequence/Process.cpp
    sequence/View.cpp

    score_addon_sequence.cpp
)


# Creation of the library
add_library(${PROJECT_NAME} ${SRCS} ${HDRS})

# Code generation
score_generate_command_list_file(${PROJECT_NAME} "${HDRS}")

# Link
target_link_libraries(${PROJECT_NAME} PUBLIC score_plugin_engine)

# Target-specific options
setup_score_plugin(${PROJECT_NAME})
