cmake_minimum_required(VERSION 2.6)
project(SystemBoard)

# include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/../Platform_Public")
include_directories("${PROJECT_SOURCE_DIR}/../Platform_EleBox")
set(INC_MDB_DIR ${INC_MDB_DIR} /usr/local/include/modbus)
include_directories(${INC_MDB_DIR}) # 用${}引用变量

# add_subdirectory("${PROJECT_SOURCE_DIR}/ElectricityBox")
# add_subdirectory("${PROJECT_SOURCE_DIR}/Modbus")


# aux_source_directory(./EletricityBox/ SRC_EleBox)
# aux_source_directory(./Modbus/ SRC_Modbus)

SET(SRC_LIST Modbus/BaseModbus.cpp
        Modbus/ModbusMaster.cpp
        ElectricityBox/EleBoxHAL.cpp
        ElectricityBox/EleBoxSimulation.cpp
        ElectricityBox/EleBoxV2.cpp
        ElectricityBox/EleBoxV4.cpp
        ElectricityBox/EleBoxFactory.cpp
        
        )

SET(INCLUDE_LIST Modbus/BaseModbus.h
        Modbus/ModbusMaster.h
        ElectricityBox/BaseEleBox.h
        ElectricityBox/EleBoxHAL.h
        ElectricityBox/EleBoxSimulation.h
        ElectricityBox/EleBoxV2.h
        ElectricityBox/EleBoxV4.h
        ElectricityBox/EleBoxFactory.h
        
        )

add_library(Box SHARED ${SRC_LIST} ${INCLUDE_LIST})

SET(INCLUDE ${PROJECT_SOURCE_DIR}/ElectricityBox ${PROJECT_SOURCE_DIR}/Modbus)

target_include_directories(Box PUBLIC INCLUDE)

set(LINK_MDB_DIR ${LINK_MDB_DIR} /usr/local/lib)
link_directories(${LINK_MDB_DIR})

target_link_libraries(Box modbus)
add_definitions(-fPIC)

