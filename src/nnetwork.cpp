#include "nnetwork.h"

double NNetwork::k_recentAvgSmoothingFactor = 100000.0; // Number of training samples to average over
int NNetwork::m_generation_limit = 8000;

NNetwork::NNetwork(const std::vector<unsigned>& topology)
    :   m_error(0.0),
        m_recentAvgError(0.0)
{
    assert( !topology.empty() ); // no empty topology

    for (unsigned i = 0; i < topology.size(); ++i)
    {
        unsigned num_neuron = topology[i];
        assert( num_neuron > 0 ); // no empty layer
        m_layers.push_back(Layer());
        Layer& new_layer = m_layers.back();
        bool is_last_layer = (i == (topology.size() - 1));
        unsigned numOutputs = ((is_last_layer) ? (0) : (topology[i + 1]));
        
        for (unsigned j = 0; j < (num_neuron + 1); ++j) // add a bias neuron
            new_layer.push_back( NNode(numOutputs, j) );

        NNode& bias_neuron = new_layer.back();
        bias_neuron.setOutputVal(1.0);
    }
}


void NNetwork::propogate(const Vals& inputVals)
{
    assert( inputVals.size() == (m_layers[0].size() - 1) ); // exclude bias neuron
    for (unsigned i = 0; i < inputVals.size(); ++i)
        m_layers[0][i].setOutputVal(inputVals[i]);

    for (unsigned i = 1; i < m_layers.size(); ++i) // exclude input layer
    {
        Layer& prevLayer = m_layers[i - 1];
        Layer& currLayer = m_layers[i];

        unsigned num_neuron = (currLayer.size() - 1); // exclude bias neuron
        for (unsigned n = 0; n < num_neuron; ++n)
            currLayer[n].feedForward(prevLayer);
    }
}


void NNetwork::calc_output_error(const Vals& targetVals) {
  
    //assert(0);
    Layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
    }
    m_error /= (outputLayer.size() - 1); // get average error squared
    m_error = sqrt(m_error); // RMS
    m_recentAvgError =
            (m_recentAvgError * k_recentAvgSmoothingFactor + m_error)
            / (k_recentAvgSmoothingFactor + 1.0);
  
}

void NNetwork::calc_output_gradients(const Vals& targetVals) {
    Layer& outputLayer = m_layers.back();
   
     for (unsigned n = 0; n < (outputLayer.size() - 1); ++n)
        outputLayer[n].calcOutputGradients(targetVals[n]);
}


void NNetwork::calc_hidden_gradients() {
 
    for (unsigned i = (m_layers.size() - 2); i > 0; --i)
    {
        Layer &hiddenLayer = m_layers[i];
        Layer &nextLayer = m_layers[i + 1];

        for (unsigned n = 0; n < hiddenLayer.size(); ++n)
            hiddenLayer[n].calcHiddenGradients(nextLayer);
    }

}


void NNetwork::calc_gradients(const Vals& targetVals) {
      calc_output_gradients(targetVals);
      calc_hidden_gradients();
}


void NNetwork::update_weights()
{
    for (unsigned i = (m_layers.size() - 1); i > 0; --i)
    {
        Layer &currLayer = m_layers[i];
        Layer &prevLayer = m_layers[i - 1];

        for (unsigned n = 0; n < (currLayer.size() - 1); ++n) // exclude bias
            currLayer[n].updateInputWeights(prevLayer);
    }
  
}

void NNetwork::back_prop(const Vals& targetVals)
{
    calc_output_error(targetVals);
    calc_gradients(targetVals);
    update_weights();
}



Vals NNetwork::learn(const Vals& i, const Vals& t) 
{
   
    propogate(i);
    
    Vals resultVals;
    //resultVals.clear();
    const Layer& outputLayer = m_layers.back();
    unsigned total_neuron = (outputLayer.size() - 1);
    for (unsigned n = 0; n < total_neuron; ++n)
        resultVals.push_back(outputLayer[n].getOutputVal());

   back_prop(t);
   
return resultVals;
}



Vals NNetwork::calculate(const Vals& i)
{
   
    propogate(i);
    
    Vals resultVals;
    //resultVals.clear();
    const Layer& outputLayer = m_layers.back();
    unsigned total_neuron = (outputLayer.size() - 1);
    for (unsigned n = 0; n < total_neuron; ++n)
        resultVals.push_back(outputLayer[n].getOutputVal());
   
return resultVals;
}

