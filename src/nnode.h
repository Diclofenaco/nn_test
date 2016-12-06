#ifndef nnode_h
#define nnode_h

#include <cstdlib>
#include <cassert>
#include <cmath>

#include <vector>
#include <iostream>
#include <string>


class NNode
{
    public:
            
            NNode(int inputs_cnt, bool isi = false);
            void dbg();            
            void load_input(float v);
            void load_inputs(std::vector<NNode*>* i);
            float get_result();
            void randomize_some_input_weights();
           
            int get_id();      
            float get_last_result();
            
    private:
    
            float activation_function2();
            float activation_function();
            float calcualte_sigma();
            void gen_random_weights();
            float gen_rand_float_in_0_1_range();
 
  private:
            int m_id;
            
            float m_input_value;
            float m_input_weight;
            
            std::vector<NNode*>* m_input_nodes;
            std::vector<float> m_input_weights;
            bool m_is_input_loaded;
            bool m_is_input_node;
            
            float m_last_res;
            
    public:
	    static int get_uid();
	    
    private:        
            static int m_unique_id;
};



#endif