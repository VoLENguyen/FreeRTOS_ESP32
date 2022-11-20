# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v4.4.2/components/bootloader/subproject"
  "E:/CE_Document/HDH_RTOS/NEW_MPU/build/bootloader"
  "E:/CE_Document/HDH_RTOS/NEW_MPU/build/bootloader-prefix"
  "E:/CE_Document/HDH_RTOS/NEW_MPU/build/bootloader-prefix/tmp"
  "E:/CE_Document/HDH_RTOS/NEW_MPU/build/bootloader-prefix/src/bootloader-stamp"
  "E:/CE_Document/HDH_RTOS/NEW_MPU/build/bootloader-prefix/src"
  "E:/CE_Document/HDH_RTOS/NEW_MPU/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/CE_Document/HDH_RTOS/NEW_MPU/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
