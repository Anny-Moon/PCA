#!/bin/bash

# Run: $ source init_session.sh

PROJECT_DIR=$PWD
INC_DIR=$PWD/PCA_lib/include
BUILD_DIR=$PWD/PCA_lib/build
DATA_DIR=$PWD/data

#################
# Include paths #
#################
if [ -z "$CPLUS_INCLUDE_PATH" ]
then
    CPLUS_INCLUDE_PATH=${INC_DIR};
else
    CPLUS_INCLUDE_PATH+=:${INC_DIR};
fi
export CPLUS_INCLUDE_PATH

#########################
# Build time link paths #
#########################
if [ -z "$LIBRARY_PATH" ]
then
    LIBRARY_PATH=${BUILD_DIR};
else
    LIBRARY_PATH+=:${BUILD_DIR};
fi
export LIBRARY_PATH

#########################
# Paths to data#
#########################
if [ -z "$DATA_PATH" ]
then
    DATA_PATH=${DATA_DIR};
else
    DATA_PATH+=:${DATA_DIR};
fi
export DATA_PATH


printf "Initialization session completed.\n"
printf "You had to call 'source init_session.sh'\n"
printf "If you did not do this, then call init_session again in correct way.\n"


