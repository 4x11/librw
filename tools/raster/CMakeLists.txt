add_executable(raster WIN32
    main.cpp
)

target_link_libraries(raster
    PRIVATE
        librw::skeleton
        librw::librw
)

add_custom_command(
    TARGET raster POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "$<TARGET_FILE_DIR:raster>/files"
    COMMAND "${CMAKE_COMMAND}" -E copy_directory  "${CMAKE_CURRENT_SOURCE_DIR}/files" "$<TARGET_FILE_DIR:raster>/files"
)

librw_platform_target(raster)
