#pragma once
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class Network {
private:
	std::vector<float> input;
	std::vector<float> output;
	float reLu(float x);
	float sigmoid(float x);
	float (*activation)(float x);

public:
	std::vector<std::vector<std::vector<float>>> weights;
	std::vector<std::vector<float>> biases;
	std::vector<int> networkStructure;

	std::vector<float> nextLayer(std::vector<float> curr, int layer);
	Network(std::vector<int> networkStructure, bool randomize = false, float (*activation)(float x) = [](float x) { return 1 / (1 + exp(-x)); });
	void randomizeBiases();
	void printBiases();
	void randomizeWeights();
	void printWeights();
	void setInput(std::vector<float> input) { this->input = input; }
	std::vector<float> getOutput() { return output; }
	void runNetwork();
	void saveNetwork(std::string fileName);
	std::vector<int> getNetworkStructure() { return networkStructure; }
	Network operator|(const Network& net);
	void operator=(const Network& net);
};
