FLAGS = -Iinclude -Llib -std=c++11 -Ofast
LIBRARIES = -lgmp

sqtri:
	g++ $(FLAGS) $(LIBRARIES) sqtri.cpp -o sqtri
