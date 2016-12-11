NAME= ../libs/libtestnn.a
SRC := $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,../objs/%.o,$(SRC))
CXXFLAGS= -Wfatal-errors -Wall -W -Wextra -Wunused -g3 -I./
LDFLAGS=	
CXX=g++
RM=rm -rf
#######

../objs/%.o:	%.cpp
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(NAME):	$(OBJ)
		ar rcs $(NAME) $(OBJ) 

all:		$(NAME)

clean:
		$(RM) $(OBJ)
		$(RM) $(NAME)

.PHONY:		clean all