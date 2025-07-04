default:
	g++ -std=c++17 src/main.cpp src/Texture.cpp src/Scene.cpp src/Camera.cpp src/Object3D.cpp src/Light.cpp src/Vector3D.cpp src/Face3D.cpp src/Ray.cpp src/Color.cpp src/Hitpoint.cpp src/BinaryDisect.cpp src/BinaryArray.cpp src/MixedArray.cpp -o bin/main

run:
	make
	./bin/main.exe

log:
	make 
	.\bin\main.exe > log.txt
