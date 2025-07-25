#!/bin/sh

buildToDir="build"

SCRIPT_DIR="$( dirname -- "${0}" )"

SOURCE="${0}"
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

if [ -d "${SCRIPT_DIR}/install" ]
then
    echo "Removing current install..."
    rm -rf "${SCRIPT_DIR}/install"
    echo "Done!"
fi

mkdir -p "${SCRIPT_DIR}/${buildToDir}"
mkdir -p "${SCRIPT_DIR}/install"

echo "Configuring build..."
cmake -S "${SCRIPT_DIR}" -B "${SCRIPT_DIR}/${buildToDir}" -DCMAKE_BUILD_TYPE=Release

if [ ${?} -ne 0 ]
then
  echo "Configuration failed"
  echo "Exiting"

  return 1
fi

echo "Building library..."
cmake --build "${SCRIPT_DIR}/${buildToDir}" --config Release
if [ ${?} -ne 0 ]
then
  echo "Build failed"
  echo "Exiting"

  return 1
fi

echo "Build complete!"

echo "Installing library..."
cmake --install "${SCRIPT_DIR}/${buildToDir}" --prefix "${SCRIPT_DIR}/install"

cd ${SCRIPT_DIR}/${buildToDir}/Testing/
ctest -C Release -V

return 0