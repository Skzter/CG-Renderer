default:
	g++ src/main.cpp src/Texture.cpp src/Scene.cpp src/Camera.cpp src/Object3D.cpp src/Light.cpp src/Vector3D.cpp src/Face3D.cpp src/Light.cpp src/Ray.cpp src/Color.cpp src/Hitpoint.cpp src/BinaryDisect.cpp -o bin/main

run:
	./bin/main.exe
