#project name
PROJECT(eclat)

#source directory
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

# set output binary path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#add executable file
ADD_EXECUTABLE(eclat ${DIR_SRCS})
