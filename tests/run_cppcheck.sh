#!/bin/sh

# Expects to be run from the directory it is located in
cd "$(dirname "$(realpath "$0")")";

# Run cppcheck
cppcheck -ibuild -itest -ilibs -Ifw/MVMFirmwareCpp/MVMFirmwareCore --language=c++ --enable=all --xml --xml-version=2 . 2> report/cppcheck-result.xml

# Run cppcheck-htmlreport and dump the results in report directory
./libs/cppcheck/htmlreport/cppcheck-htmlreport --source-encoding="iso8859-1" --report-dir=report --file=report/cppcheck-result.xml --title=MVM --source-dir=.
