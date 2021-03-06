cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD  90)
set(CMAKE_C_STANDARD_REQUIRED True)

# set the project name
project(RT)

add_definitions(-DPLATFORM_MACOS)

#  find src -type f -name '*.c' | sort | column -c 100
set(${PROJECT_NAME}_SOURCE
        src/cam/cam_init.c                      src/err/msg_err.c                       src/scn/get/scn_get_obj_by_name.c
        src/err/msg_ok.c
        src/err/msg_warn.c                      src/scn/scn_id.c
        src/err/rt_err.c                        src/scn/scn_init.c
        src/err/rt_warn.c                       src/scn/scn_name.c
        src/gpu/gpu_buffer_load.c               src/srv/srv_deinit.c
        src/gpu/gpu_init.c                      src/srv/srv_ext.c
        src/gpu/gpu_kernel_run.c                src/srv/srv_ext_data.c
        src/gui/gui_init.c                      src/srv/srv_init.c
        src/main.c                              src/srv/srv_loop.c
        src/mat/mat_init.c                      src/srv/srv_parse.c
        src/obj/obj_container_init.c            src/srv/srv_utils.c
        src/obj/obj_copy_init.c                 src/tfm/tfm_init.c
        src/obj/obj_grp_init.c                  src/tfm/tfm_move.c
        src/obj/obj_init.c                      src/txr/txr_init.c
        src/rt.c                                src/vlk/vlk_init.c
        src/scn/add/scn_add_obj.c
        src/scn/get/scn_get_obj_by_id.c
)

add_executable(${PROJECT_NAME}  ${${PROJECT_NAME}_SOURCES} lib/ft/src/file/ft_read_files.c lib/ft/src/file/ft_read_files.h)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/src       ${PROJECT_SOURCE_DIR}/src/err
        ${PROJECT_SOURCE_DIR}/src/gui   ${PROJECT_SOURCE_DIR}/src/srv
        ${PROJECT_SOURCE_DIR}/src/cmd   ${PROJECT_SOURCE_DIR}/src/gpu
        ${PROJECT_SOURCE_DIR}/src/mtl   ${PROJECT_SOURCE_DIR}/src/scn
        ${PROJECT_SOURCE_DIR}/src/vlk   ${PROJECT_SOURCE_DIR}/src/txr
        ${PROJECT_SOURCE_DIR}/src/mat   ${PROJECT_SOURCE_DIR}/src/cam
        ${PROJECT_SOURCE_DIR}/src/obj   ${PROJECT_SOURCE_DIR}/src/tfm
        ${PROJECT_SOURCE_DIR}/src/shp   ${PROJECT_SOURCE_DIR}/src/txr
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/ft/inc		)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/num/include		)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/ft/libft.a)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/num/libnum.a)

set (GTK_BUNDLE_DIR ${PROJECT_SOURCE_DIR}/gtk_bundle_42)
set (GTK_INCLUDE_DIR ${GTK_BUNDLE_DIR}/include)
set (GTK_LIB_DIR ${GTK_BUNDLE_DIR}/lib)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${GTK_INCLUDE_DIR}
        ${GTK_INCLUDE_DIR}/gtk-3.0
        ${GTK_INCLUDE_DIR}/glib-2.0
        ${GTK_INCLUDE_DIR}/harfbuzz
        ${GTK_INCLUDE_DIR}/cairo
        )

target_link_directories(${PROJECT_NAME} PUBLIC ${GTK_LIB_DIR} )
target_link_libraries(${PROJECT_NAME} "gtk-3.0" "gdk-3.0" "glib-2.0" "gobject-2.0" "gio-2.0")

target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/build/mtl)
target_link_libraries(${PROJECT_NAME} "mtl")

add_custom_command(TARGET RT
        POST_BUILD
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/../rt_school21_linking.sh" RT
        COMMENT "Linking RT..."
        VERBATIM
        )
        
