#ifndef train_set_io_h
#define train_set_io_h

#include <vector>
#include <string>
#include <fstream>

class TrainingData
{
public:
    TrainingData(const std::string filename);
    bool isEof(void) { return m_trainingDataFile.eof(); }
    void getTopology(std::vector<unsigned> &topology);

    // Returns the number of input values read from the file:
    unsigned getNextInputs(std::vector<float> &inputVals);
    unsigned getTargetOutputs(std::vector<float> &targetOutputVals);

private:
    std::ifstream m_trainingDataFile;
};

#endif