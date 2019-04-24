#include "Utility.h"

int Utility::randomIntNumber(int min, int max) {
	srand(time(NULL));
	int randomInt = rand() % max + min;
	//std::cout << "Random INT generated: " << randomInt << std::endl;

	return rand() % max + min;
}

double Utility::randomDoubleNumber(double min, double max) {
	double f = (double)rand() / RAND_MAX;
	double randomDouble = min + f * (max - min);
	//std::cout << "Random DOUBLE generated: " << randomDouble << std::endl;

	return randomDouble;
}

float Utility::randomFloatNumber(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float randomFloat = min + (random * diff);
	//std::cout << "Random FLOAT generated: " << randomFloat << std::endl;

	return randomFloat;
}