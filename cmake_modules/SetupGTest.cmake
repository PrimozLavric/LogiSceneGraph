
macro(setup_gtest SEARCH_PATHS)

	find_package(GTest QUIET)

	if (NOT ${GTEST_FOUND})
		foreach (DIR "${SEARCH_PATHS}")
			if (EXISTS "${DIR}/include" AND EXISTS "${DIR}/lib")
				find_library(GTEST_LIB_DIR gtest PATHS "${DIR}/lib")
				find_library(GTEST_MAIN_LIB_DIR gtest_main PATHS "${DIR}/lib")

				if (EXISTS ${GTEST_LIB_DIR} AND EXISTS ${GTEST_MAIN_LIB_DIR})
					set(GTEST_INCLUDE_DIRS "${DIR}/include")
					set(GTEST_BOTH_LIBRARIES "${GTEST_LIB_DIR} ${GTEST_MAIN_LIB_DIR}")
					set(GTEST_LIBRARIES "${GTEST_LIB_DIR}")
					set(GTEST_MAIN_LIBRARIES "${GTEST_MAIN_LIB_DIR}")
					set(${GTEST_FOUND} TRUE)
				endif()
			endif()
		endforeach(DIR)

	endif()

endmacro()