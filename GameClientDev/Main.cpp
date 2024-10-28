#include <iostream>

#include "Entities/Camera2D.h"
#include "math/Math.h"

int main()
{
	Camera2D camera(800, 600);
	auto Matrix = camera.GetProjectMatrix();
	std::cout << "hello world!" << *Matrix.data() << std::endl;
}
