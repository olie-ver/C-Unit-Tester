#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "testpp::testpp" for configuration "Release"
set_property(TARGET testpp::testpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(testpp::testpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libtestpp.a"
  )

list(APPEND _cmake_import_check_targets testpp::testpp )
list(APPEND _cmake_import_check_files_for_testpp::testpp "${_IMPORT_PREFIX}/lib/libtestpp.a" )

# Import target "testpp::testpp_main" for configuration "Release"
set_property(TARGET testpp::testpp_main APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(testpp::testpp_main PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libtestpp_main.a"
  )

list(APPEND _cmake_import_check_targets testpp::testpp_main )
list(APPEND _cmake_import_check_files_for_testpp::testpp_main "${_IMPORT_PREFIX}/lib/libtestpp_main.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
