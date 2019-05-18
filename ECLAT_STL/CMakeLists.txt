#project name
PROJECT(ECLAT_STL)

#source directory
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

# set output binary path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#add executable file
ADD_EXECUTABLE(ECLAT_STL ${DIR_SRCS})
