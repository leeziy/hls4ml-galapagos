<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="com.autoesl.autopilot.project" name="CNN_prj" top="CNN">
  <files>
    <file name="firmware/CNN.cpp" sc="0" tb="false" cflags="-std=c++0x" blackbox="false"/>
    <file name="../../CNN_test.cpp" sc="0" tb="1" cflags=" -std=c++0x -Wno-unknown-pragmas"/>
    <file name="../../tb_data" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
    <file name="../../firmware/weights" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
  </files>
  <solutions>
    <solution name="solution1" status="active"/>
  </solutions>
  <includePaths/>
  <libraryPaths/>
  <Simulation>
    <SimFlow name="csim" setup="true" clean="true" csimMode="0" lastCsimMode="0"/>
  </Simulation>
</project>