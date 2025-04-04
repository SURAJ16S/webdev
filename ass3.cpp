/*
Assignement No : 3 

Problem Statement : There are flight paths between cities. If there is a flight between 
city A and city B then 
there is an edge between the cities.
The cost of the edge can be the time that flight takes to reach city B from A or the 
amount of fuel used for the 
journey. The node can be 
represented by airport name or name of the city. Use adjacency list representation of the 
graph and adjacency 
matrix representation of the graph.
Justify the storage representation used
*/
//using the advancency matrix
#include<iostream>
using namespace std;
//class creation
class AMS{
    public:
        int numofcities;              
        string cities[100];
        int adj[100][100];

        //accept function
         void accept(){
            cout<<"Enter total Number of Cities to accept : ";
            cin>>numofcities;
            
        //accept city namee
            for(int i =0;i<numofcities;i++){
                cout<<"Enter "<<i<< " Cities :";
                cin>>cities[i];
            } 
            
            //accept fuel
            for(int j=0;j<numofcities;j++){
                for(int k=0;k<numofcities;k++){
                    //set fuel 0 for the self loop
                    if(cities[j] == cities[k]){
                        adj[j][k] = 0;
                    }

                    //else accept the fuel
                    else{
                        cout<<"Enter Fuel require for " <<cities[j]<< " to " << cities[k]<<" : ";
                        cin>>adj[j][k];
                    }
                }
            }
         }

         void display(){
            for(int i =0;i<numofcities;i++){
                for(int j=0;j<numofcities;j++){
                    if(cities[i] == cities[j]){
                        
                    }
                    else{
                        cout<<cities[i]<<" to "<<cities[j]<<" : " <<adj[i][j]<<endl;
                    }
                }
            }
              
         }

}flight;     //creation of 'flight' object

 int main(){
    flight.accept();
    flight.display();
    return 0;
 }

 /*
                    a b c d
                  a 0 6 2 1
                  b 6 0 5 3
                  c 2 5 0 9
                  d 1 3 9 0

                  to enter 
                  12,13,14
                  23,24
                  34

                  to skip - 11,22,33,44

                  row = limit -1
                  column = row + (j++)      //means j will be 1,2,3,4... 

                  for(int i =0;i<limit;i++){
                    for(int j =i++;j<limit;j++){
                        if(cities[i] == cities[j]){
                            //---
                        }
                   
                    }
                  }
                */