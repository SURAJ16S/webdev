//assignment 3 using the adjacency list 
#include<iostream>
using namespace std;

class fms{
    public:

    int numofcity;  
    int fuel;

    string city;

    fms *next;

    void accept();
    void insertEdge();
    void display();

}*head[10];       

void fms::accept(){      //accept no of cities to accept and cities name and store in the head array pointer
    cout<<"Enter Number Of Cities to Enter : ";
    cin>>numofcity;
    for(int i =0;i<numofcity;i++){
        head[i] = new fms;     //memory allocation
        //city name accept
        cout<<"Enter "<< i <<" Cities Name : ";
        cin >> head[i]->city;
        head[i]->next = NULL;       //setting next to NULL , creating individual array pointer 
    }
}

void fms::insertEdge(){
    //declare variable
    int totaledges;
    string sourcecity, destcity;

    //accept total edges
    cout<<"Enter Total Edges : ";
    cin>>totaledges;

    //accept source and destination city and fuel
    for(int i = 0; i < totaledges; i++){
        cout<<"Enter Source and Destination City : ";
        cin>>sourcecity>>destcity;

        cout<<"Enter Fuel : ";
        cin>>fuel; //direct store in the variable 

        //compare the source city with the head array
        for(int j = 0; j < numofcity; j++){
            if(head[j]->city == sourcecity){
            
                fms *temp = head[j];
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = new fms;
                temp->next->city = destcity;
                temp->next->fuel = fuel;
                temp->next->next = NULL;
                break;
            }
            // reverse the process for destination city
            // if(head[j]->city == destcity){
            
            //     fms *temp = head[j];
            //     while(temp->next != NULL){
            //         temp = temp->next;
            //     }
            //     temp->next = new fms;
            //     temp->next->city = sourcecity;
            //     temp->next->fuel = fuel;
            //     temp->next->next = NULL;
            //     break;
            // }
        }
    }
}

void fms::display() {
    //apply for loop for all cities
    for (int i = 0; i < numofcity; i++) { 
        cout << head[i]->city << " -> ";  //print the source city and arrow

        fms *temp = head[i]->next;        //store the next pointer in temp variable
        
        while (temp!= NULL) { //while temp is not null
            cout << temp->city << " (Fuel: " << temp->fuel << ") ";    //print the destination city and fuel store in temp variable
            temp = temp->next;       // update temp to next pointer
        }
        
        cout << "\n";
    }
}

fms flight;

int main(){
    flight.accept();
    flight.insertEdge();
    flight.display();
    return 0;
}
