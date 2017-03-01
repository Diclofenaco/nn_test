#ifndef nnetwork_h
#define nnetwork_h

#include "nnode.h"
#include <vector>

typedef std::vector<float> Vals;
typedef std::vector<NNode> Layer;

class NNetwork
{
public:
    NNetwork(const std::vector<unsigned>& topology);
    //NNetwork(int is, int os, int hs, int ls); 
    
    Vals learn(const Vals& i, const Vals& t);
    Vals calculate(const Vals& i);
   
public: 
    double getError() const { return m_error; }
    double getRecentAverageError() const { return m_recentAvgError; }
    int learning_iteration_limit() { return k_recentAvgSmoothingFactor; } 
    int learning_generation_limit() { return m_generation_limit; } 
    

private:
    void propogate(const Vals& inputVals);
    void back_prop(const Vals& targetVals);

private:
    void calc_output_error(const Vals& targetVals);
    void calc_output_gradients(const Vals& targetVals);
    void calc_hidden_gradients();
    void calc_gradients(const Vals& targetVals);
    void update_weights();
    
    
private:
    std::vector<Layer> m_layers; 

    double m_error;
    double m_recentAvgError;
    static double k_recentAvgSmoothingFactor;
    static int m_generation_limit;
};

#endif