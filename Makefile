LIBS=-lGL -lglfw -lGLEW

FILES = main.cpp cube/cube.cpp cube/model.cpp player/player.cpp element/ground.cpp loader/objLoader.cpp loader/obj_parser.cpp loader/string_extra.cpp loader/list.cpp element/drawable.cpp imgLoader/lodepng.cpp element/skybox.cpp element/track.cpp  element/cart.cpp cube/torus.cpp cube/detailed_cube.cpp cube/sphere.cpp element/light.cpp


main_file: $(FILES)
	g++ -o main_file $(FILES)  $(LIBS)
