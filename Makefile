# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependencies among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ a.out ]

########## Variables ##########

CXX = g++-11					# compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

SOURCES = $(wildcard *.cc)			# source files (*.cc)
OBJECTS = ${SOURCES:.cc=.o}			# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
<<<<<<< HEAD
EXEC = raiinet					# executable name

########## Targets ##########

.PHONY : clean					# not file names
=======
EXEC = raiinet					    # executable name

########## Targets ##########

.PHONY : clean					    # not file names
>>>>>>> 977598fc33ad39b4d8da8400a276babd22585475

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@ -lX11		# additional object files before $^

<<<<<<< HEAD
${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile
=======
${OBJECTS} : ${MAKEFILE_NAME}	    # OPTIONAL : changes to this file => recompile
>>>>>>> 977598fc33ad39b4d8da8400a276babd22585475

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
<<<<<<< HEAD
	
=======
>>>>>>> 977598fc33ad39b4d8da8400a276babd22585475
