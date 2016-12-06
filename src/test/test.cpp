#include "../nnetwork.h"

#include <vector>
int main() 
{
    
    int inputs = 3;
    int outputs = 3;
    int mids = 3;
    int midlayers = 3;
 
    //11x
    //std::vector<float> i = {1.1 , 0.5 , 3.2};
    std::vector<float> i;
    i.push_back(1.1);
    i.push_back(0.1);
    i.push_back(2.1);
    
    
    NNetwork net(inputs,outputs,mids,midlayers);
      net.calculate_result_for_given_inputs(i);
      net.print_graphviz_sytle_network_state();
    
    
 return 0;   
}