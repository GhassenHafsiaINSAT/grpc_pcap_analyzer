#include <bits/stdc++.h>
#include "Actia.pb.h"


// Function to simulate server-side logic for GetFeature RPC
feature GetFeature(const point& request) {
    feature response;
    response.set_id(request.id() + 100);  // Simulated logic: id + 100
    response.set_nom("Feature " + request.nom());  // Simulated logic: prepend "Feature "
    return response;
};

int main(){

    point point_request; 
    point_request.set_id(123); 
    point_request.set_nom("hello"); 


    feature feature_response;
    feature_response = GetFeature(point_request); 

    std::cout<<"We have a message recieved"<<std::endl;
    std::cout<<"Its ID is" << feature_response.id()<< std::endl; 
    std::cout<<"Its name is "<< feature_response.nom()<<std::endl; 
    
    return 0; 
}