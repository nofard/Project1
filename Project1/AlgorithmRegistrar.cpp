#include "AlgorithmRegistrar.h"


list<unique_ptr<AbstractAlgorithm>> AlgorithmRegistrar::getAlgorithms()const 
{
	list<unique_ptr<AbstractAlgorithm>> algorithms;
	for (auto algorithmFactoryFunc : algorithmFactories) 
	{
		algorithms.push_back(algorithmFactoryFunc());
	}
	return algorithms;
}

/*
list<unique_ptr<_204032031_BaseAlgorithm>> AlgorithmRegistrar::getAlgorithms()const
{
	list<unique_ptr<_204032031_BaseAlgorithm>> algorithms;
	for (auto algorithmFactoryFunc : algorithmFactories)
	{
		algorithms.push_back(algorithmFactoryFunc());
	}
	return algorithms;
}
*/
const list<std::string>& AlgorithmRegistrar::getAlgorithmNames()const
{
	return algorithmNames;
}

size_t AlgorithmRegistrar::size()const
{
	return algorithmFactories.size();
}

void AlgorithmRegistrar::printAlgorithmsNames()
{
	int i = 0;
	auto pName = algorithmNames.begin();
	while (pName != algorithmNames.end())
	{
		cout << "(" << i++ << ") " << *pName << endl;
		pName++;
	}
}
