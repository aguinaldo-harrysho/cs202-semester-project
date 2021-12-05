#include<vector>
#include<iostream>

#include"sampleEcho.h"

std::vector<float> Echo::process(std::vector<float> data){

  float delay; // = specified delay echo

  for(int i = 0; i < data.size(); i++){
    
    data[i] = data[i] + delay;//delay*data;

  }
  data;
  return data;
}    
  
 


