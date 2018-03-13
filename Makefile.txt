#Peggy Li
#CISC 3140-ET6: Web Applications
#Homework 3
#March 6, 2018

#Uses -o to specify output
#First line of each section specifies dependencies (only runs if those specific files are changed)
#Second line specifies action
GoHome: main.o Makefile Game.o CardSet.o Player.o 
	g++ main.o Game.o CardSet.o Player.o -o GoHome.exe

#Uses -c to remove .cpp ending
main.o: main.cpp Makefile Game.o
	g++ -c main.cpp
	
#Uses -c to remove .cpp ending	
Game.o: Game.cpp Game.h Makefile CardSet.o Player.o
	g++ -c Game.cpp

#Uses -c to remove .cpp ending
CardSet.o: Cardset.cpp CardSet.h Makefile
	g++ -c CardSet.cpp

#Uses -c to remove .cpp ending
Player.o: Player.cpp Player.h Makefile
	g++ -c Player.cpp

#Removes all .o files and GoHome.exe
clean:
	rm *.o GoHome.exe