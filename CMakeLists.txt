find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Sql)
target_link_libraries(MAVERICK PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Sql)
