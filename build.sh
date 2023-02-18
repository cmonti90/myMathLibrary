#!/bin/sh

buildToDir="build/lib"

SCRIPT_DIR="$( dirname -- "${BASH_SOURCE[0]}" )"

curDir=${PWD}
oldDir=${OLDPWD}

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
SCRIPT_DIR="$( dirname "$SOURCE" )"

if [ -d "${SCRIPT_DIR}/${buildToDir}" ]
then
    echo "Removing current build..."
    rm -rf "${SCRIPT_DIR}/${buildToDir}"
    echo "Done!"
fi

mkdir -p "${SCRIPT_DIR}/${buildToDir}"

echo "Configuring build..."
cmake -S "${SCRIPT_DIR}" -B "${SCRIPT_DIR}/${buildToDir}"

if [ ${?} -ne 0 ]
then
  echo "Configuration failed"
  echo "Exiting"
  
  cd ${curDir}
  export OLDPWD=${oldDir}

  exit 1
fi

echo "Building library..."
cmake --build "${SCRIPT_DIR}/${buildToDir}"
if [ ${?} -ne 0 ]
then
  echo "Build failed"
  echo "Exiting"

  cd ${curDir}
  export OLDPWD=${oldDir}

  exit 1
fi

echo "Build complete!"

echo "Installing library..."
cmake --install "${SCRIPT_DIR}/${buildToDir}" --prefix "${SCRIPT_DIR}/${buildToDir}/install"

cd ${curDir}
export OLDPWD=${oldDir}

exit 0