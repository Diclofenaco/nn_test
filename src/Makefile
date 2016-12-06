#CC=/depot/gcc-5.2.0/bin/g++ 
CC=g++ 
CFLAGS=-c -Wfatal-errors
#-std=c++14 
default:
	$(CC) $(CFLAGS) nnetwork.cpp nnode.cpp
	mv *.o ../objs
	ar rcs ../libs/libtrivial_nn.a ../objs/nnetwork.o ../objs/nnode.o 
	