#ifndef __ALGORITHM_REGISTRAR_H_
#define __ALGORITHM_REGISTRAR_H_

#include "io_utils.h"
#include "AlgorithmRegistration.h"

using namespace std;

class AlgorithmRegistrar {
	list<string> algorithmNames;
	list<function<unique_ptr<AbstractAlgorithm>()>> algorithmFactories;
	//list<function<unique_ptr<_204032031_BaseAlgorithm>()>> algorithmFactories;
	void registerAlgorithm(function<unique_ptr<AbstractAlgorithm>()> algorithmFactory, const string& name)
	{
		algorithmFactories.push_back(algorithmFactory);
		algorithmNames.push_back(name);
	}/*
	void registerAlgorithm(function<unique_ptr<_204032031_BaseAlgorithm>()> algorithmFactory, const string& name)
	{
		algorithmFactories.push_back(algorithmFactory);
		algorithmNames.push_back(name);
	}*/
public:
	friend struct AlgorithmRegistration;
	list<unique_ptr<AbstractAlgorithm>> getAlgorithms()const;
	//list<unique_ptr<_204032031_BaseAlgorithm>> getAlgorithms()const;
	const list<std::string>& getAlgorithmNames()const;
	size_t size()const;
	void printAlgorithmsNames();

	static AlgorithmRegistrar& getInstance()
	{
		static AlgorithmRegistrar instance;
		return instance;
	}

};

#endif