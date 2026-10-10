add_library(bot_lib STATIC bot.cpp)
target_include_directories(bot_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(bot_lib PUBLIC dpp::dpp)

add_executable(bot main.cpp)
target_link_libraries(bot PRIVATE bot_lib)