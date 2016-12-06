#include "nnetwork.h"
#include "nnode.h"

#include <cstdlib>
#include <cassert>
#include <cmath>

#include <vector>
#include <iostream>
#include <string>
  
	    //F IXME compile error
            /*NNetwork::NNetwork(int iscount, int oscount, int midcount, int layers) 
            {
                srand(time(0));
                //std::cout << "Creating Network with " << m_midlayers_cnt << " layers" << std::endl;
                //std::cout << "With " << m_ns_in_midlayer_cnt<< " neurons in each layer" << std::endl;
                m_naive_outputs.resize(m_ns_in_outputlayer_cnt);
            
                create_mid_layers();
                create_output_layer();
                create_input_layer();
            }
	    */

            void NNetwork::play_with_weights() {
                int h = 1+rand()%(m_midlayers_cnt*m_ns_in_midlayer_cnt);
                for (int i=0; i<h; i++) {
                    int r_clm = 1+rand()%(m_midlayers_cnt-1);
                    int r_row = rand()%m_ns_in_midlayer_cnt;
                    (*m_mid_layers[r_clm])[r_row]->randomize_some_input_weights();
                }
            }
            
            
            void NNetwork::load_inputs(const std::vector<float>& v) {
                //assert(!m_is_input_loaded);   
                assert(m_input_layer);
                assert(m_input_layer->size() == v.size());
                
                //assert(v.size() == m_ns_in_midlayer_cnt);
                
                for( int j=0; j<v.size(); j++) 
                    (*m_input_layer)[j]->load_input(v[j]);  

                m_is_input_loaded = true;
                assert(m_input_layer);
            }
            
            
            const std::vector<float>& NNetwork::get_output() {
                assert(m_is_input_loaded);
                assert(m_output_layer);
                assert(m_output_layer->size()>0);
                //std::cout << "Getting output...\n";
                //std::cout << " Getting result starting from output node" << m_output_node->get_id() << "(" <<m_output_node << ")" << std::endl;
                for( int j=0; j<m_output_layer->size(); j++) 
                    m_naive_outputs[j]=(*m_output_layer)[j]->get_result(); 
                
                return m_naive_outputs;
            }
            
            const std::vector<float>& NNetwork::calculate_result_for_given_inputs(const std::vector<float>& v) {
                // std::cout << "Loading inputs... "<< std::endl;
                 //if (!m_is_input_loaded) 
		 load_inputs(v);
                 //std::cout << "Getting output..." << std::endl;
                 //return 1.0;
                 return get_output();
            }
            
            void NNetwork::print_vector(std::string label, const std::vector<float> &v)
            {
                    std::cout << label << " ";
                    for (unsigned i = 0; i < v.size(); ++i)
                    std::cout << v[i] << " ";
                    std::cout << std::endl;
            }


            void NNetwork::print_graphviz_sytle_network_state() 
            {
                std::cout << "digraph g{\n";
                std::cout << "rankdir=LR;\n";
                std::cout << "node [style=\"filled\",color=blue,shape=square,fontsize=1];";
                for(size_t i=0; i< m_input_layer->size(); i++) std::cout << " INPUT" << i;
                std::cout<< ";" << std::endl;
                
                std::cout << "node [style=\"filled\",color=red,shape=square,fontsize=1];";
                for(size_t i=0; i< m_output_layer->size(); i++) std::cout << " OUTPUT" << i;
                std::cout<< ";" << std::endl;
                
                std::cout << "node [shape=circle,fontsize=10,color=black,style=\"\"];\n";
                std::cout << "size=\"20\"\n";
               
                for(size_t i=0; i< m_input_layer->size(); i++) {
                   std::cout << "  INPUT" <<i << "-> node" << (*m_input_layer)[i]->get_id() << " [  label =\"" <<  (*m_input_layer)[i]->get_last_result() << "\"  ]; " << std::endl;          
                }
               
                size_t size1 = m_mid_layers.size();
                for (size_t i = 0; i< size1; ++i) {
                    size_t size2 = (*m_mid_layers[i]).size();
                    for (size_t j = 0; j < size2; ++j) {
                        (*m_mid_layers[i])[j]->dbg();
                    }
                }
                
                for(size_t i=0; i< m_ns_in_outputlayer_cnt; i++) {
                    (*m_output_layer)[i]->dbg();
                    std::cout << " node" << (*m_output_layer)[i]->get_id() << " -> OUTPUT" <<i <<"  [  label =\"" << (*m_output_layer)[i]->get_last_result() << "\"  ]; " << std::endl;                    
                }
                
                
                std::cout << "}" << std::endl;
            }
   
                        
            void NNetwork::create_input_layer() {
                m_input_layer = new std::vector<NNode*>;
                // create input layers
                for( int j=0; j<m_ns_in_inputlayer_cnt; j++) {
                    NNode* i = new NNode(1,true);    
                    m_input_layer->push_back(i);            
                }

                // connect first midlayer to input layer 
                for( int j=0; j<m_ns_in_midlayer_cnt; j++)
                    (*m_mid_layers[0])[j]->load_inputs(m_input_layer);            

            }
            
            void NNetwork::create_output_layer() {
                m_output_layer = new std::vector<NNode*>;
                for( int j=0; j<m_ns_in_outputlayer_cnt; j++) {
                    NNode* i = new NNode(m_ns_in_midlayer_cnt);    
                    m_output_layer->push_back(i);            
                }
                assert(m_output_layer->size()>0);

               //connect output layer to mid layers
                for( int i=0; i<m_ns_in_outputlayer_cnt; i++)
                      (*m_output_layer)[i]->load_inputs(m_mid_layers[m_midlayers_cnt-1]);
            }
            
        
            void NNetwork::create_mid_layers() {
                bool ft = true;
                for(  int i=0; i<m_midlayers_cnt; i++) {             
                    //std::cout << " MidLayer" << i << " : ";
                    NLayer* c_layer = new std::vector<NNode*> ;
                    for(  int j=0; j<m_ns_in_midlayer_cnt; j++) {
                        NNode* n = new NNode(ft?m_ns_in_inputlayer_cnt:m_ns_in_midlayer_cnt);
                        //std::cout << " N" << j << "(" << n << ")";
                        c_layer->push_back(n);
                    }
                    m_mid_layers.push_back(c_layer);
                    //std::cout << " :::" << c_layer << " . layerscount=" << m_mid_layers.size()<< std::endl;
                ft = false;
                }
                
                for(  int i=1; i<m_midlayers_cnt; i++) 
                    for(  int j=0; j<m_ns_in_midlayer_cnt; j++)
                            (*m_mid_layers[i])[j]->load_inputs(m_mid_layers[i-1]);           

            }
            
