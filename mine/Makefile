
release:
	gcc -fopenmp -O3 -Wall -Wextra -Wno-unused-parameter -I/usr/include/GL/ -I/usr/include/SDL2 -o bin main.c -lm -lGLEW -lSDL2 -lGL

release-singlethreaded:
	gcc -DTERRAIN_THREAD=0 -fopenmp -O3 -Wall -Wextra -Wno-unused-parameter -I/usr/include/GL/ -I/usr/include/SDL2 -o bin main.c -lm -lGLEW -lSDL2 -lGL

debug:
	gcc -fopenmp -O3 -g -Wall -Wextra -Wno-unused-parameter -I/usr/include/GL/ -I/usr/include/SDL2 -o bin main.c -lm -lGLEW -lSDL2 -lGL

debug-singlethreaded:
	gcc -DTERRAIN_THREAD=0 -fopenmp -O3 -g -Wall -Wextra -Wno-unused-parameter -I/usr/include/GL/ -I/usr/include/SDL2 -o bin main.c -lm -lGLEW -lSDL2 -lGL

clean:
	rm -f bin
