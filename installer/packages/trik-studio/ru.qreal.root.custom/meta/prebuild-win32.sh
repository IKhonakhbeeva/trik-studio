#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/plugins/editors

#cp    $BIN_DIR/plugins/editors/customMetamodel.dll                                $PWD/../data/plugins/editors/
#cp    $BIN_DIR/robots-custom-kit.dll                                              $PWD/../data/
cp    $BIN_DIR/plugins/tools/kitPlugins/robots-custom-interpreter.dll             $PWD/../data/plugins/tools/kitPlugins/
