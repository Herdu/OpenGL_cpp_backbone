LIBS=-lGL -lglfw -lGLEW
FILES=main.cpp

main_file: $(FILES)
	g++ -o main_file $(FILES)  $(LIBS)
