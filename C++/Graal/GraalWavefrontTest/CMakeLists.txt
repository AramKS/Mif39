cmake_minimum_required(VERSION 2.8)

project ( GraalWavefrontTest CXX )
file ( GLOB_RECURSE SRC *.?pp )
add_executable(GraalWavefrontTest ${SRC})
target_link_libraries(GraalWavefrontTest Qt5::Core)
target_link_libraries(GraalWavefrontTest Qt5::Gui)
target_link_libraries(GraalWavefrontTest Utility)
target_link_libraries(GraalWavefrontTest AssetInterfaces)
target_link_libraries(GraalWavefrontTest AssetGenerics)
target_link_libraries(GraalWavefrontTest Assets)
target_link_libraries(GraalWavefrontTest Wavefront)
target_link_libraries(GraalWavefrontTest QImageLoader)
