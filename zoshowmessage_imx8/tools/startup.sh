#!/bin/bash

echo "Executing startup scripts..."

BASEDIR=$(dirname $0)
QMAKE_CXX=$1
MODULE_NAME=$2
BUILD_MODE=$3
MAJOR_VERSION=$4
STARTUPDIR=${BASEDIR}/startup

REPO_SITE="ssh://git@zlbitbucket.zitro.local:7999/zone/"$MODULE_NAME."git"

#Export any required variables:
export GCC_LOCATION=${QMAKE_CXX}

#Make the symlinks with the git hooks:
PRECOMMIT="../.git/hooks/pre-commit"
if [[ ! -L ${PRECOMMIT} ]]; then
    ln -s ../../tools/pre-commit.sh ../.git/hooks/pre-commit
fi

#Run all startup scripts in the startup directory:
for script in ${STARTUPDIR}/*.sh; do 
    $script $REPO_SITE $BUILD_MODE $MODULE_NAME $MAJOR_VERSION
done

echo "Finished executing startup scripts..."

