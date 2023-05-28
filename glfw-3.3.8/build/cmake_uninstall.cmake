
if (NOT EXISTS "D:/.INGENIERIA EN COMPUTACION/OpenGL_Basics/glfw-3.3.8/build/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"D:/.INGENIERIA EN COMPUTACION/OpenGL_Basics/glfw-3.3.8/build/install_manifest.txt\"")
endif()

file(READ "D:/.INGENIERIA EN COMPUTACION/OpenGL_Basics/glfw-3.3.8/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("D:/.INGENIERIA EN COMPUTACION/OpenGL_Basics/cmake-3.26.4-windows-x86_64/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("D:/.INGENIERIA EN COMPUTACION/OpenGL_Basics/cmake-3.26.4-windows-x86_64/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

