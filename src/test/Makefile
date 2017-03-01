NAME= ../../bin/test
SRC := $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,../../objs/test/%.o,$(SRC))
CXXFLAGS= -Wfatal-errors -Wall -W -Wextra -Wunused -g3 -I./
LDFLAGS=	
CXX=g++
RM=rm -rf
#######

../../objs/test/%.o:	%.cpp
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) ../../libs/libtestnn.a $(CPPFLAGS) $(CXXFLAGS) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)
		$(RM) $(NAME)

.PHONY:		clean all
