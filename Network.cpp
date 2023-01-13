#include "Network.h"

Network::Network(std::vector<int> networkStructure, bool randomize, float (*activation)(float x)) {
    this->networkStructure = networkStructure;
    this->activation = activation;
     
    if (randomize) {
        randomizeWeights();
        randomizeBiases();
    }
}

void Network::randomizeBiases() {
    biases.resize(networkStructure.size() - 1);
    for (int i = 0; i < biases.size(); i++) {
        biases[i].resize(networkStructure[i + 1]);
        for (int j = 0; j < biases[i].size(); j++) {
            biases[i][j] = reLu(rand() / (float)RAND_MAX);
        }
    }
}
void Network::printBiases() {
    for (int i = 0; i < biases.size(); i++) {
        cout << "[";
        for (int j = 0; j < biases[i].size() - 1; j++) {
            cout << biases[i][j] << ", ";
        }
        cout << biases[i][biases[i].size() - 1] << "]" << endl;
    }
    cout << endl;
}
void Network::randomizeWeights() {
    weights.resize(networkStructure.size() - 1);
    for (int i = 0; i < weights.size(); i++) {
        weights[i].resize(networkStructure[i + 1]);
        for (int j = 0; j < weights[i].size(); j++) {
            weights[i][j].resize(networkStructure[i]);
            for (int k = 0; k < weights[i][j].size(); k++) {
                weights[i][j][k] = reLu(rand() / (float)RAND_MAX);
            }
        }
    }
}
void Network::printWeights() {
    for (int i = 0; i < weights.size(); i++) {
        for (int j = 0; j < weights[i].size(); j++) {
            for (int k = 0; k < weights[i][j].size(); k++) {
                cout << weights[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}
std::vector<float> Network::nextLayer(std::vector<float> curr, int layer) {
    std::vector<float> output2;

    output2.resize(networkStructure[layer + 1]);
    for (int i = 0; i < output2.size(); i++) {
        float sum = biases[layer][i];
        for (int j = 0; j < curr.size(); j++) {
            sum += weights[layer][i][j] * curr[j];
        }
        output2[i] = sum;
    }
    return output2;
}
void Network::runNetwork() {
    std::vector<float> layer = input;
    for (int i = 0; i < networkStructure.size() - 1; i++) {
        layer = nextLayer(layer, i);
    }
    output = layer;
}

void Network::saveNetwork(std::string fileName) {
    std::ofstream file(fileName);
    file << "Layout: \n";
    for (int i = 0; i < networkStructure.size(); i++) {
        file << networkStructure[i] << " ";
    }
    file << "\n\n";

    file << "Biases: \n";
    for (int i = 0; i < biases.size(); i++) {
        for (int j = 0; j < biases[i].size(); j++) {
            file << biases[i][j] << " ";
        }
        file << "\n";
    }
    file << "\n";

    file << "Weights: \n";
    for (int i = 0; i < weights.size(); i++) {
        for (int j = 0; j < weights[i].size(); j++) {
            for (int k = 0; k < weights[i][j].size(); k++) {
                file << weights[i][j][k] << " ";
            }
            file << "\n";
        }
        file << "\n";
    }
}

float Network::reLu(float x) { return x > 0 ? x : 0; }
float Network::sigmoid(float x) { return 1 / (1 + exp(-x)); }

Network Network::operator|(const Network& net) {
    // weights
    Network babyNetwork(networkStructure);
    babyNetwork.weights.resize(networkStructure.size() - 1);
    for (int i = 0; i < weights.size(); i++) {
        babyNetwork.weights[i].resize(networkStructure[i + 1]);
        for (int j = 0; j < weights[i].size(); j++) {
            babyNetwork.weights[i][j].resize(networkStructure[i]);
            for (int k = 0; k < weights[i][j].size(); k++) {
                babyNetwork.weights[i][j][k] =
                    rand() % 2 == 0 ? weights[i][j][k] : net.weights[i][j][k];
                if (rand() % 50 == 0) {
                    babyNetwork.weights[i][j][k] = rand() / (float)RAND_MAX;
                }
            }
        }
    }

    // biases
    babyNetwork.biases.resize(networkStructure.size() - 1);
    for (int i = 0; i < biases.size(); i++) {
        babyNetwork.biases[i].resize(networkStructure[i + 1]);
        for (int j = 0; j < biases[i].size(); j++) {
            babyNetwork.biases[i][j] =
                rand() % 2 == 0 ? biases[i][j] : net.biases[i][j];
            if (rand() % 50 == 0) {
                babyNetwork.biases[i][j] = reLu(rand() / (float)RAND_MAX);
            }
        }
    }

    return babyNetwork;
}

void Network::operator=(const Network& net) {
    weights.clear();
    biases.clear();

    this->networkStructure = net.networkStructure;
    this->weights = net.weights;
    this->biases = net.biases;
}
