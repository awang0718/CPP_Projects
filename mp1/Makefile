mp1:  main.o mp1.o PNG.o HSLAPixel.o lodepng.o
	clang++ main.o mp1.o PNG.o HSLAPixel.o lodepng.o -o mp1

main.o: main.cpp mp1.h cs225/PNG.h cs225/HSLAPixel.h
	clang++ -c main.cpp

mp1.o: mp1.cpp mp1.h cs225/PNG.h cs225/HSLAPixel.h
	clang++ -c mp1.cpp

PNG.o: cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	clang++ -c cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	clang++ -c cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	clang++ -c cs225/lodepng/lodepng.cpp

test : unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o
	$(LD) unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o $(LDFLAGS) -o test

unit_tests.o : tests/unit_tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) tests/unit_tests.cpp

clean :
	rm mp1 *.o
