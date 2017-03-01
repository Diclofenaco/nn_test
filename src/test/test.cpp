#include "../nnetwork.h"
#include "../train_set_io.h"

#include <algorithm>
#include <vector>
#include <cstdlib>
#include <bitset>

/*
void test_infrastructure()
{
  
    int inputs = 3;
    int outputs = 1;
    int mids = 3;
    int midlayers = 3;
 

    std::vector<float> i;
    i.push_back(1.0);
    i.push_back(0.0);
    i.push_back(0.0);
    NNetwork net(inputs,outputs,mids,midlayers);
      net.calculate_result_for_given_inputs(i);
      net.print_graphviz_sytle_network_state();

}
*/

void showVectorVals(std::string label, std::vector<int> v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";

    std::cout << std::endl;
}

void showVectorVals(std::string label, Vals v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";

    std::cout << std::endl;
}

void print_stat(NNetwork& n, std::vector<float> i, std::vector<float> o,std::vector<float> t) {
              //std::cout << std::endl << "Pass " << trainingPass << std::endl;
              showVectorVals("Inputs:", i);
              showVectorVals("Outputs:", o);
              showVectorVals("Targets:", t);
              std::cout << "Net current error: " << n.getError() << std::endl;
              std::cout << "Net recent average error: " << n.getRecentAverageError() << std::endl;
              std::cout << "------\n\n";
}

/*
void prepare_study_case()
{
  
  
  
  

} */


//FIXME
std::vector<int> convert(int x) {
  std::vector<int> ret;
  while(x) {
    if (x&1)
      ret.push_back(1);
    else
      ret.push_back(0);
    x>>=1;  
  }
  std::reverse(ret.begin(),ret.end());
  return ret;
}

std::vector< int > get_bits( unsigned long x ) {
    std::string chars( std::bitset< 3 >( x )
        .to_string( char(0), char(1) ) );
    return std::vector< int >( chars.begin(), chars.end() );
}

void learn_simple_and(NNetwork& n)
{
  

    std::vector<float> inputVals, targetVals;
    inputVals.resize(3);
    targetVals.resize(1);
    int trainingPass = 0;
    float acceptable_error = 0.001;

    int i = 1;
    while ( i != n.learning_generation_limit() ) 
    {
          int a = rand()%2;
          int b = rand()%2;
          int c = rand()%2;
          
          inputVals[0] = (float)a;
          inputVals[1] = (float)b;
          inputVals[2] = (float)c; 
          
          targetVals[0] = (bool)inputVals[0] && (bool)inputVals[1] && (bool)inputVals[2];

          while ( true ) {
              ++trainingPass;
              n.learn(inputVals,targetVals);
             // print_stat();
      
              if (trainingPass > n.learning_iteration_limit() && n.getRecentAverageError() < acceptable_error)
              {
                  //std::cout << std::endl << "average error acceptable -> break" << std::endl;
                  trainingPass=0;
                  break;
              }
          }
     ++i;
    }
}


void learn_to_sum(NNetwork& n)
{
  

    std::vector<float> inputVals, targetVals;
    inputVals.resize(3);
    targetVals.resize(3);
    int trainingPass = 0;
    float acceptable_error = 0.0001;

    
    int i = 0;
    while ( i != n.learning_generation_limit() ) 
    {
          //int a = rand()%2;
          //int b = rand()%2;
          //int c = rand()%2;
          
          int c = rand()%5;
          //int c = i;
          int res = c + 1;
          
          //std::cout  << c << " " << res << std::endl;
          std::vector<int> c_bool = get_bits(c);
          std::vector<int> res_bool = get_bits(res);
          //showVectorVals("is",c_bool);
          //showVectorVals("res",res_bool);
          
          //assert(0);
          
          inputVals[0] = c_bool[c_bool.size()-3];
          inputVals[1] = c_bool[c_bool.size()-2];
          inputVals[2] = c_bool[c_bool.size()-1]; 
          
          targetVals[0] = res_bool[c_bool.size()-3];
          targetVals[1] = res_bool[c_bool.size()-2];
          targetVals[2] = res_bool[c_bool.size()-1];

          while ( true ) {
              ++trainingPass;
              n.learn(inputVals,targetVals);
              //print_stat(n,inputVals,n.learn(inputVals,targetVals),targetVals);
              //assert(0);
              if (trainingPass > n.learning_iteration_limit() && n.getRecentAverageError() < acceptable_error)
              {
                  //std::cout << std::endl << "average error acceptable -> break" << std::endl;
                  trainingPass=0;
                  break;
              }
          }
     ++i;
    }
}


void execute(NNetwork& n) 
{
  
        //*
        std::vector<float>  inputVals;
        std::cout << "TEST" << std::endl;
        std::cout << std::endl;

        unsigned dblarr_test[8][3] = { {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1}, {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}  };

        for (unsigned i = 0; i < 8; ++i)
        {
            inputVals.clear();
            inputVals.push_back(dblarr_test[i][0]);
            inputVals.push_back(dblarr_test[i][1]);
            inputVals.push_back(dblarr_test[i][2]);
            
  
            showVectorVals("Inputs:", inputVals);
            showVectorVals("Outputs:",n.calculate(inputVals));

            std::cout << std::endl;
        }

        std::cout << "/TEST" << std::endl;
        /**/ 
  
}

int main() 
{

    srand(time(0));
    std::vector<unsigned> topology;
    topology.push_back(3);
    topology.push_back(15);
    topology.push_back(3);
    
    NNetwork myNet(topology);

  
    std::cout << "\n\n Studying, do not disturb! " << std::endl;
    learn_to_sum(myNet);   
  
  
    
    std::cout << " Bereq xzarem... " << std::endl;
    execute(myNet);

return 0;   
}