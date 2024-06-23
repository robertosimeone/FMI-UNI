#include <iostream>
#include <vector>

using namespace std;

struct Neuron {
  double value;
  double weight;
};

class NeuralNetwork {
private:
  vector<vector<Neuron>> layers;
  double learningRate;

public:
  NeuralNetwork(int inputSize, int hiddenSize, int outputSize, double learningRate) {
    layers.resize(3);

    for (int i = 0; i < 3; i++) {
      layers[i].resize(i + 1);

      for (int j = 0; j < layers[i].size(); j++) {
        if (i == 0) {
          layers[i][j].weight = 1;
        } else if (i == 1) {
          layers[i][j].value = 0;
        } else {
          layers[i][j].weight = 1;
        }
      }
    }

    this->learningRate = learningRate;
  }

  double sigmoid(double x) {
    return 1 / (1 + exp(-x));
  }

  double feedforward(vector<double> inputs) {
    vector<double> outputs;

    for (int i = 0; i < layers.size(); i++) {
      vector<double> newInputs;

      for (int j = 0; j < layers[i].size(); j++) {
        double weightedSum = 0;

        for (int k = 0; k < inputs.size(); k++) {
          weightedSum += layers[i - 1][k].value * layers[i][j].weight;
        }

        newInputs.push_back(sigmoid(weightedSum));
      }

      inputs = newInputs;
    }

    return outputs[0];
  }

  void backpropagation(vector<double> inputs, double expectedOutput) {
    vector<double> errors;

    errors.push_back(expectedOutput - feedforward(inputs));

    for (int i = layers.size() - 2; i >= 0; i--) {
      vector<double> deltas;

      for (int j = 0; j < layers[i].size(); j++) {
        double delta = 0;

        for (int k = 0; k < layers[i + 1].size(); k++) {
          delta += errors[i + 1] * layers[i + 1][k].weight;
        }

        deltas.push_back(delta * sigmoid(layers[i][j].value) * (1 - sigmoid(layers[i][j].value)));
      }

      errors = deltas;
    }

    for (int i = layers.size() - 2; i >= 0; i--) {
      for (int j = 0; j < layers[i].size(); j++) {
        double change = errors[i + 1] * layers[i][j].value;

        layers[i - 1][j].value += learningRate * change;
      }
    }
  }
};

int main() {
  NeuralNetwork neuralNetwork(2, 1, 1, 0.1);

  vector<double> inputs = {0, 0};
  double expectedOutput = 0;

  neuralNetwork.backpropagation(inputs, expectedOutput);
  double prediction = neuralNetwork.feedforward(inputs);

  cout << "Input: " << inputs[0] << ", " << inputs[1] << endl;
  cout << "Prediction: " << prediction << endl;

  return 0;
}

