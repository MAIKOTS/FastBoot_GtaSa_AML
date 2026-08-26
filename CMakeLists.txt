# mínimo CMake
cmake_minimum_required(VERSION 3.14)
project(FastBoot_GtaSa_AML LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# URLs / tags
set(AML_CORE_REPO "https://github.com/RusJJ/AndroidModLoader.git")
set(SAUTILS_REPO  "https://github.com/AndroidModLoader/SAUtils.git")
set(GIT_TAG       "main") # ou uma tag/commit específico

# Fonte do seu projeto
set(PROJ_SOURCES
  src/main.cpp
  src/socialclub.cpp
  src/startmode.cpp
)

# --- Fetch AndroidModLoader (core) ---
FetchContent_Declare(aml_core GIT_REPOSITORY ${AML_CORE_REPO} GIT_TAG ${GIT_TAG})
FetchContent_Populate(aml_core) # obtido em aml_core_SOURCE_DIR

# inicializar submodules dentro do repo populado (ARMPatch, AML_PrecompiledLibs)
execute_process(
  COMMAND git submodule update --init --recursive
  WORKING_DIRECTORY ${aml_core_SOURCE_DIR}
  RESULT_VARIABLE _aml_submod_rc
  OUTPUT_QUIET ERROR_QUIET
)
if(NOT _aml_submod_rc EQUAL 0)
  message(WARNING "Falha ao inicializar submodules de AndroidModLoader (rc=${_aml_submod_rc}). Rode 'git submodule update --init --recursive' no diretório ${aml_core_SOURCE_DIR}.")
endif()

# adicionar arquivos do core se existirem
if(EXISTS "${aml_core_SOURCE_DIR}/mod/config.cpp")
  list(APPEND PROJ_SOURCES "${aml_core_SOURCE_DIR}/mod/config.cpp")
endif()
if(EXISTS "${aml_core_SOURCE_DIR}/mod/logger.cpp")
  list(APPEND PROJ_SOURCES "${aml_core_SOURCE_DIR}/mod/logger.cpp")
endif()

# inclui headers do core
if(EXISTS "${aml_core_SOURCE_DIR}/include")
  set(AML_CORE_INCLUDE "${aml_core_SOURCE_DIR}/include")
endif()

# --- Fetch SAUtils (opcional/recomendado) ---
FetchContent_Declare(sautils GIT_REPOSITORY ${SAUTILS_REPO} GIT_TAG ${GIT_TAG})
FetchContent_Populate(sautils)
if(EXISTS "${sautils_SOURCE_DIR}/include")
  set(SAUTILS_INCLUDE "${sautils_SOURCE_DIR}/include")
elseif(EXISTS "${sautils_SOURCE_DIR}")
  set(SAUTILS_INCLUDE "${sautils_SOURCE_DIR}")
endif()

# cria target
add_library(${PROJECT_NAME} SHARED ${PROJ_SOURCES})

# adiciona includes detectados
if(AML_CORE_INCLUDE)
  target_include_directories(${PROJECT_NAME} PRIVATE "${AML_CORE_INCLUDE}")
endif()
if(SAUTILS_INCLUDE)
  target_include_directories(${PROJECT_NAME} PRIVATE "${SAUTILS_INCLUDE}")
endif()

# compatibilidade link flags
if(COMMAND target_link_options)
  target_link_options(${PROJECT_NAME} PRIVATE "-s")
else()
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s")
endif()
