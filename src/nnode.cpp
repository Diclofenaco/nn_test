#include "nnode.h"


NNode::NNode(unsigned numOutputs, unsigned myIndex)
    : m_myIndex(myIndex)
{
    for (unsigned i = 0; i < numOutputs; ++i)
    {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }
}

void NNode::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;
    for (unsigned n = 0; n < prevLayer.size(); ++n)
        sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;

    m_outputVal = NNode::transferFunction(sum);
}


void NNode::calcOutputGradients(double targetVal)
{
    double delta = targetVal - m_outputVal;
    m_gradient = delta * NNode::transferFunctionDerivative(m_outputVal);
}



void NNode::calcHiddenGradients(const Layer &nextLayer)
{
    double sum = 0.0;
    unsigned num_NNode = (nextLayer.size() - 1); 

    for (unsigned n = 0; n < num_NNode; ++n)
      sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;


    m_gradient = sum * NNode::transferFunctionDerivative(m_outputVal);
}


void NNode::updateInputWeights(Layer &prevLayer)
{
    double eta = 0.15;    
    double alpha = 0.5; 

    for (unsigned n = 0; n < prevLayer.size(); ++n)
    {
        NNode &NNode = prevLayer[n];
        double oldDeltaWeight = NNode.m_outputWeights[m_myIndex].deltaWeight;
        double newDeltaWeight = eta * NNode.getOutputVal()* m_gradient + alpha* oldDeltaWeight ;
        NNode.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        NNode.m_outputWeights[m_myIndex].weight += newDeltaWeight;
    }
}


