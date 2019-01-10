
##############################################
#
# Add the given subdirectories and update
# PATH_FROM_BASE variable.
#
# Parameters:
# - SUBDIRECTORIES  List of subdirectories that
#                   will be added.
#
##############################################
macro(add_subdirectories SUBDIRECTORIES)
  
  foreach(SUBDIR ${SUBDIRECTORIES})
    add_subdirectory(${SUBDIR})
  endforeach()
  
endmacro(add_subdirectories)