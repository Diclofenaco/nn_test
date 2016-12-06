#ifndef network_h
#define network_h

#include "nnode.h"

#include <cstdlib>
#include <cassert>
#include <cmath>

#include <vector>
#include <iostream>
#include <string>

typedef std::vector<NNode*> NLayer;

class NNetwork
{
    public:  
            NNetwork(int iscount, int oscount, int midcount, int layers ): m_all_n_cnt(0),m_midlayers_cnt(layers),m_ns_in_inputlayer_cnt(iscount),m_ns_in_outputlayer_cnt(oscount),m_ns_in_midlayer_cnt(midcount),m_is_input_loaded(false) {
	       srand(time(0));
                //std::cout << "Creating Network with " << m_midlayers_cnt << " layers" << std::endl;
                //std::cout << "With " << m_ns_in_midlayer_cnt<< " neurons in each layer" << std::endl;
                m_naive_outputs.resize(m_ns_in_outputlayer_cnt);
            
                create_mid_layers();
                create_output_layer();
                create_input_layer(); 
	    }

                       
            const std::vector<float>& calculate_result_for_given_inputs(const std::vector<float>& v) ;
           
            void print_vector(std::string label, const std::vector<float> &v);

            void print_graphviz_sytle_network_state() ;
           
    private:
            void load_inputs(const std::vector<float>& v);
            const std::vector<float>& get_output() ;

            void play_with_weights();
            void create_input_layer();
            void create_output_layer();
            void create_mid_layers();
            

    
    private:
        int m_all_n_cnt;
        int m_midlayers_cnt;
        int m_ns_in_inputlayer_cnt;
        int m_ns_in_midlayer_cnt;    
        int m_ns_in_outputlayer_cnt;
        bool m_is_input_loaded;
    
    private:
        
        //NNode* m_output_node;
        
        NLayer* m_output_layer;
        NLayer* m_input_layer;
        std::vector<NLayer*> m_mid_layers;
        
        //std::vector<float> m_naive_inputs;
        std::vector<float> m_naive_outputs;
        
        //For debug
        //std::multimap<NNode*,NNode*> m_dbg_inodes2onodes;
        //std::multimap<NNode*,NNode*> m_dbg_inodes2onodes;
    
};

#endif
