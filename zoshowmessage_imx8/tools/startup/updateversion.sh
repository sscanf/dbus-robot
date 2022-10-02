#!/bin/bash

BASEDIR=$(dirname $0)
REPO_SITE=$1
BUILD_MODE=$2
MODULE_NAME=$3
MAJOR=$4
CORELENGTH=0

if [ "$BUILD_MODE" == "" ]; then
    BUILD_MODE="release"
fi

#Construct the full paths of the versioncotrol.h and repoinfo.h files:
PROJECTDIR=$(echo ${BASEDIR}/../../)
VERSIONFILE=$(echo $PROJECTDIR/versioncontrol.h)
REPOFILE=$(echo $PROJECTDIR/repoinfo.h)

#Check if the versioncontrol file exists. If it doesn't exist, create a default one:
if ! [ -f ${VERSIONFILE} ]; then
    echo "Version control file does not exist. Creating..."
    touch ${VERSIONFILE}
    echo >> ${VERSIONFILE}
    echo "#define BUILD_DATE "\""XXXX-XX-XX"\""" >> ${VERSIONFILE}
    echo "#define BUILD_TIME "\""XX:XX:XX"\""" >> ${VERSIONFILE}
    echo "#define BUILD_HOST "\""hostname"\""" >> ${VERSIONFILE}
    echo "#define BUILD_GCCV "\""X.X.X"\""" >> ${VERSIONFILE}
    echo >> ${VERSIONFILE}
    echo "#define VERSION "\""XX.YYYYMMDDHHMM"\""" >> ${VERSIONFILE}
    echo "#define MAJOR "\""XX"\""" >> ${VERSIONFILE}
    echo "#define MINOR "\""YYYYMMDDHHMM"\""" >> ${VERSIONFILE}
    echo >> ${VERSIONFILE}
    echo "Finished creating version control file."
fi

#Check if the repoinfo file exists. If it doesn't exist, create a default one:
if ! [ -f ${REPOFILE} ]; then
    echo "Repo info file does not exist. Creating..."
    touch ${REPOFILE}
    echo >> ${REPOFILE}
    echo "#define REPOSITORY_BRANCH "\""branch"\""" >> ${REPOFILE}
    echo "#define REPOSITORY_STATUS "\""status"\""" >> ${REPOFILE}
    echo "#define REPOSITORY_HASH "\""xxxxxxxxxxxx"\""" >> ${REPOFILE}
    echo >> ${REPOFILE}
    echo "Finished creating repo info file."
fi

#Calculate date, time and host name:
TODAY="\""$(date +%Y-%m-%d)"\""
NOW="\""$(date +%H:%M:%S)"\""
HOST="\""$(hostname)"\""

#Get the gcc version that is being used to compile:
GCC="\""$(${GCC_LOCATION} --version | perl -pe '($_)=/([0-9]+([.][0-9]+)+)/' )"\""

echo "==========Build data=========="
echo ${TODAY}
echo ${NOW}
echo ${HOST}
echo ${GCC}
echo "=============================="

#Stamp the new build data into the versioncontrol.h file:
sed -i '/BUILD_DATE/c\#define BUILD_DATE '${TODAY} ${VERSIONFILE}
sed -i '/BUILD_TIME/c\#define BUILD_TIME '${NOW} ${VERSIONFILE}
sed -i '/BUILD_HOST/c\#define BUILD_HOST '${HOST} ${VERSIONFILE}
sed -i '/BUILD_GCCV/c\#define BUILD_GCCV '${GCC} ${VERSIONFILE}

#Change working directory to the project's one:
cd "${PROJECTDIR}"

#If the Build mode is "debug", read the git data directly using the "git" command
#Version string: in this case, unconditionally update the version string
if [ "$BUILD_MODE" == "debug" ]; then
    echo "Building in Debug mode..."

    #Read the current git data:
    GITHASHLONG=$(git describe --always --dirty --abbrev=0)
    GITHASH="\""$(git describe --always --abbrev=0)"\""
    GITBRANCH="\""$(git branch | sed -n -e 's/^\* \(.*\)/\1/p')"\""
    GITSTATUS="\""$(echo $GITHASHLONG | cut -d'-' -f 2)"\""

    if [ ${#GITSTATUS} -gt 7 ]; then
        GITSTATUS="\"""clean""\""
    fi

    #If we are in a "detached HEAD" state, the original branch we come from must be queried:
    if [[ $GITBRANCH == *"HEAD"* ]]; then
       GITHASHCLEAN=$(git describe --always --abbrev=0)
       GITBRANCH="\""$(git branch --contains ${GITHASHCLEAN} | sed -n 2p | sed -e 's/^ *//g' -e 's/ *$//g')"\""
    fi

    #Stamp the version in the "major.minor" version into the versioncontrol file:
    MINOR=$(date +%Y%m%d)$(date +%H%M)
    echo "=======Version: ${MAJOR}.${MINOR}======"
    sed -i '/#define VERSION/c\#define VERSION '"\""${MAJOR}.${MINOR}"\"" ${VERSIONFILE}
    sed -i '/#define MAJOR/c\#define MAJOR '"\""${MAJOR}"\"" ${VERSIONFILE}
    sed -i '/#define MINOR/c\#define MINOR '"\""${MINOR}"\"" ${VERSIONFILE}
fi

#If the Build mode is "release", check the repository URL for the hash of the current HEAD commit
#Version string: in this case, do NOT update the version string
if [ "$BUILD_MODE" == "release" ]; then
    echo "Building in Release mode..."

    #Read current git repository data:
    GITHASH="\""$(git ls-remote ${REPO_SITE} | awk '/HEAD/ {print $1}')"\""
    GITBRANCH="\""master"\""
    GITSTATUS="\""clean"\""
fi

echo "==========Repository data=========="
echo ${GITHASH}
echo ${GITSTATUS}
echo ${GITBRANCH}
echo "==================================="

#Stamp the git repository data into the repoinfo.h file:
sed -i '/REPOSITORY_HASH/c\#define REPOSITORY_HASH '${GITHASH} ${REPOFILE}
sed -i '/REPOSITORY_STATUS/c\#define REPOSITORY_STATUS '${GITSTATUS} ${REPOFILE}
sed -i '/REPOSITORY_BRANCH/c\#define REPOSITORY_BRANCH '"${GITBRANCH}" ${REPOFILE}


