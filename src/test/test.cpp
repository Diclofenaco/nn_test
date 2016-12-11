#include "../nnetwork.h"
#include "../train_set_io.h"

#include <vector>

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

void showVectorVals(std::string label, Vals v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";

    std::cout << std::endl;
}


void test_learning() {
    TrainingData trainData("src/test/data/out_xor.txt");
    // TrainingData trainData("src/test/data/out_and.txt");
    // TrainingData trainData("src/test/data/out_or.txt");
    // TrainingData trainData("src/test/data/out_no.txt");
    std::vector<unsigned> topology;
    trainData.getTopology(topology);

    //NNetwork myNet(topology[0],topology[2],topology[0],topology[1]);

    NNetwork myNet(topology);

    std::vector<float> inputVals, targetVals;
    int trainingPass = 0;

    while (!trainData.isEof()) 
    {
        if (trainData.getNextInputs(inputVals) != topology[0])
            break;

        ++trainingPass;
        std::cout << std::endl << "Pass " << trainingPass << std::endl;

        showVectorVals("Inputs:", inputVals);

        trainData.getTargetOutputs(targetVals);
        showVectorVals("Outputs:", myNet.calculate(inputVals,targetVals));
        showVectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());
        std::cout << "Net current error: " << myNet.getError() << std::endl;
        std::cout << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;
        if (trainingPass > myNet.learning_iteration_limit() && myNet.getRecentAverageError() < 0.01)
        {
            std::cout << std::endl << "average error acceptable -> break" << std::endl;
            break;
        }
    }
    
    
        std::cout << std::endl << "Done" << std::endl;

        /*
    
        std::cout << "TEST" << std::endl;
        std::cout << std::endl;

        unsigned dblarr_test[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} };

        for (unsigned i = 0; i < 4; ++i)
        {
            inputVals.clear();
            inputVals.push_back(dblarr_test[i][0]);
            inputVals.push_back(dblarr_test[i][1]);
  
            showVectorVals("Inputs:", inputVals);
            showVectorVals("Outputs:",myNet.calculate(inputVals));

            std::cout << std::endl;
        }

        std::cout << "/TEST" << std::endl;
        */
}


void test_learning2()
{
  
    std::vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(3);
    topology.push_back(1);
    
    NNetwork myNet(topology);

    std::vector<float> inputVals, targetVals;
    inputVals.resize(2);
    targetVals.resize(1);
    int trainingPass = 0;

    int i = 1;
    while ( i != 10 ) 
    {

      //int k = 0;
      //trainingPass = 0;
     
      while ( true ) {
          ++trainingPass;
          inputVals[0] = i/100;
          inputVals[1] = i/100;
          targetVals[0] = inputVals[0]+inputVals[1];

          std::cout << std::endl << "Pass " << trainingPass << std::endl;
          showVectorVals("Inputs:", inputVals);
          showVectorVals("Outputs:", myNet.calculate(inputVals,targetVals));
          showVectorVals("Targets:", targetVals);
          std::cout << "Net current error: " << myNet.getError() << std::endl;
          std::cout << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;
          assert(0);    
   
          if (trainingPass > myNet.learning_iteration_limit() && myNet.getRecentAverageError() < 0.01)
          {
              std::cout << std::endl << "average error acceptable -> break" << std::endl;
              //assert(0);
              ++i;
              break;
              
          }
       }
    
     ++i;
    }
}


int main() 
{
  //test_learning();
  
  test_learning2();     
  return 0;   
}