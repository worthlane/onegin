# Did DED tell you about better compiler flags?
# Maybe you should use them
#
# Also: You can compile each file separately to avoid re-compiling the
# whole program after each change
#
# Simple example:
# CC := g++
# CFLAGS := <DED FLAGS>
#
# main.o: main.cpp
# 	$(CC) $(CFLAGS) -c main.cpp -o main.o
# getoutinfo.o: getoutinfo.cpp
# 	$(CC) $(CFLAGS) -c getoutinfo.cpp -o getoutinfo.o
# sorter.o: sorter.cpp
# 	$(CC) $(CFLAGS) -c sorter.cpp -o sorter.o
#
# all: main.o getoutinfo.o sorter.o
# 	$(CC) $(CFLAGS) main.o getoutinfo.o sorter.o -o onegin
#
# This example can be made much shorter with some of the more advanced syntax
# Documentation on GNU Make can be found here:
# 	https://www.gnu.org/software/make/manual/make.html
# 
# You can also take a look at my own Makefile, use documentation to understand:
# 	https://github.com/MeerkatBoss/ray_trace/blob/master/Makefile
#
# Please, avoid blindly copying what you see.
all:
	g++ main.cpp getoutinfo.cpp sorter.cpp
