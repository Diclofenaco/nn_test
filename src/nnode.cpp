#include "nnode.h"
int NNode::m_unique_id = 0;


#include <cstdlib>
#include <cassert>
#include <cmath>

#include <vector>
#include <iostream>
#include <string>


            
            NNode::NNode(int inputs_cnt, bool isi):m_is_input_node(isi) { 
                if (! m_is_input_node ) {
                    m_input_weights.resize(inputs_cnt);
                    
                    gen_random_weights();
                }
                m_id = m_unique_id;
                ++m_unique_id;
            }
            
            
            void NNode::dbg() {
             
                assert( m_input_weights.size() == m_input_nodes->size() );
                size_t size = m_input_weights.size();
                for (size_t i = 0; i < size; ++i) {
                    //std::cout << (*m_input_nodes)[i]->get_id() << " -> " <<  m_id  << " [  label =\"" << m_input_weights[i] << "\" ]; " << std::endl;
                    std::cout << " node" << (*m_input_nodes)[i]->get_id() << " -> node" <<  m_id  << " [  label =\"" << (*m_input_nodes)[i]->get_last_result() << " , w="<< m_input_weights[i] << "\" ]; " << std::endl;                    
                }

            }
            
            void NNode::load_input(float v) {
                assert(m_is_input_node); 
                m_input_value = v;
                m_input_weight = 1.0;
                m_is_input_loaded = true;
                
            }
            
            void NNode::load_inputs(std::vector<NNode*>* i) {
                //std::cout << m_input_weights.size() << "!=" << i->size() << std::endl;
                assert( m_input_weights.size() == i->size() );
                //m_input_weights.resize(i->size());
                assert(i);
                assert(!m_is_input_node);
                //assert(!m_is_input_loaded);
                m_input_nodes = i;
                m_is_input_loaded = true;
            }
            
            float NNode::get_result() {
                assert(m_is_input_loaded);
                //std::cout << " results from Node" << m_id << "(" << this << ")" << std::endl;
                //return activation_function();
                m_last_res = m_is_input_node?activation_function2():activation_function();
                return m_last_res;    
            }

            void NNode::randomize_some_input_weights() {
                assert(m_is_input_loaded);
                assert(!m_is_input_node);
                float epsilon = 0.3;
                unsigned int ws_to_permuate = rand()% m_input_weights.size();
                std::vector<int> rand_indexes(ws_to_permuate);    
                for(  int i=0; i!=rand_indexes.size(); i++) rand_indexes[i] = rand()% m_input_weights.size() ; 
                for(  int i=0; i!=rand_indexes.size(); i++) m_input_weights[rand_indexes[i]] = gen_rand_float_in_0_1_range(); 
                //for(  int i=0; i!=rand_indexes.size(); i++) 
                        //std::cout << " change for node" << m_id << " weigth n:" << rand_indexes[i] << std::endl;
               //std::cout << std::endl;
                //for(  int i=0; i!=rand_indexes.size(); i++) rand_indexes[i] = rand()% m_input_weights.size() ; 
            }
            
            int NNode::get_uid() { return m_unique_id; }
            
            int NNode::get_id() { return m_id; }
            
            float NNode::get_last_result() {return m_last_res;}
            
    
            float NNode::activation_function2() {
                return m_input_value*m_input_weight;    
            }
            
            float NNode::activation_function() {
                float r;// do something on sigma
                r = tanh(calcualte_sigma());
                return r;
            }
            
            float NNode::calcualte_sigma() {
                //std::cout << "Calc sigma" << std::endl;
                assert(m_input_nodes);
                assert(m_input_nodes->size() > 0);
                //std::cout << m_input_weights.size() << "!=" << m_input_nodes->size() << std::endl;
                assert( m_input_weights.size() == m_input_nodes->size() );
                float res = 0.0;
                for( unsigned int i=0; i!=m_input_weights.size(); ++i) {
                    //std::cout << "Calc sigma" << std::endl;
                    assert((*m_input_nodes)[i]);
                    res = res + m_input_weights[i]*( (*m_input_nodes)[i] ->get_result() ); 
                }
                 return res;  
            }
            
            void NNode::gen_random_weights() {
                for( unsigned int i=0; i!=m_input_weights.size(); ++i) 
                    m_input_weights[i] = gen_rand_float_in_0_1_range();
            }
            
             float NNode::gen_rand_float_in_0_1_range() {
                return   static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            }
            


