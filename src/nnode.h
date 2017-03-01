#ifndef nnode_h
#define nnode_h

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>


struct Connection
{
    double weight;
    double deltaWeight;
};
typedef std::vector<Connection> Connections;


class NNode;
typedef std::vector<NNode> Layer;

class NNode
{
public:
    NNode(unsigned numOutputs, unsigned myIndex);

    inline void setOutputVal(double val) { m_outputVal = val; }
    inline double getOutputVal(void) const { return m_outputVal; }

    void feedForward(const Layer& prevLayer);
    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const Layer& nextLayer);
    void updateInputWeights(Layer& prevLayer);

private:
   
    double transferFunction(double x) {  return tanh(x); }
    double transferFunctionDerivative(double x) { return (1.0 - x * x); }
    double randomWeight() { return rand() / double(RAND_MAX); }
 

private:    
    unsigned m_myIndex;
    double m_outputVal;
    double m_gradient; 

private:    
    
    Connections m_outputWeights;
};

#endif