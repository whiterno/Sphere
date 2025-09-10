SRCS := src/3dvector.cpp src/sphere.cpp src/main.cpp
HEADERS := include/main.h

TARGET:
	g++ -std=c++17 ${SRCS} -o a.out -I include -I /opt/homebrew/Cellar/sfml/3.0.0_1/include -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system
