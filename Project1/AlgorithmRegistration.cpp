
#include "AlgorithmRegistrar.h"
#include "AlgorithmRegistration.h"

AlgorithmRegistration::AlgorithmRegistration(std::function<unique_ptr<AbstractAlgorithm>()> algorithmFactory, string name) {
	AlgorithmRegistrar::getInstance().registerAlgorithm(algorithmFactory, name);
}