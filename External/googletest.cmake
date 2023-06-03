CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.13.0
    VERSION v1.13.0
    OPTIONS
        "INSTALL_GTEST OFF"
)

set_target_properties(gtest_main PROPERTIES FOLDER External/googletest)
set_target_properties(gtest PROPERTIES FOLDER External/googletest)
set_target_properties(gmock PROPERTIES FOLDER External/googletest)
set_target_properties(gmock_main PROPERTIES FOLDER External/googletest)
