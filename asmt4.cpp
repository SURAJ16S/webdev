/*
assignment 4 : you are a job seeker , preparing for interview in different location , you have a list of cities 
where interview are scheduled and 
you want to find the 
shortest path to visit all the interview location starting from your corrent location , the objejctive is to 
minimize the total travel distance  
and time while insuaring
you reach each interview location on time . use appropriate data structure and algorithm to implement it .
*/
#include <iostream>
#include <string>
using namespace std;

class IMS{
public:
    int totalCities, totalEdges;
    string cities[10];
    int distance[10][10];
    void accept();
    void primsAlgorithm();
    void display();
};
//object creation
IMS interviewer;

void IMS::accept() {
    //accept total cities 
    cout << "Enter Total Cities: ";
    cin >> totalCities;
//accecpt the actual city names 
    for (int i = 0; i < totalCities; i++) {
        cout << "Enter City Name: ";
        cin >> cities[i];
    }

    // Initialize the distance matrix to a large value (infinity)
    for (int i = 0; i < totalCities; i++) {
        for (int j = 0; j < totalCities; j++) {
            distance[i][j] = (i == j) ? 0 : 999; // 0 for same city, large value for others
        }
    }
//accept the total edges to store
    cout << "Enter Total Edges: ";
    cin >> totalEdges;
//accept the city names and distance between them
    for (int i = 0; i < totalEdges; i++) {
        string city1, city2;
        int weight;
        cout << "Enter Edge " << i + 1 << " (City1, City2, Weight): ";
        cin >> city1 >> city2 >> weight;

        // Find indexes for the cities
        int index1 = -1, index2 = -1;
        for (int j = 0; j < totalCities; j++) {
            if (cities[j] == city1) index1 = j;
            if (cities[j] == city2) index2 = j;
        }

        // Update the distance matrix - but check before whether it is availble or not 
        //in the city list
        if (index1 != -1 && index2 != -1){
            distance[index1][index2] = weight;
            distance[index2][index1] = weight; 
        } else {
            cout << "Invalid cities entered. Please try again." << endl;
            i--; // Re-enter this edge
        }
    }
}

void IMS::primsAlgorithm() {
    bool visited[10] = {false};     // start as nothing is visited
    int parent[10]; // To store the parent of each city in the MST
    int weight[10];  //min weight
    int min, u;       //u = source index
int mstvalue = 0;
    // Initialize weights to a high value
    for (int i = 0; i < totalCities; i++) {
        weight[i] = 999;
        parent[i] = -1;
    }
//first city is the starting point so weight is 0 assign 999
    weight[0] = 0; // Start from the first city

    for (int count = 0; count < totalCities - 1; count++) {
        min = 999;

        // Find the minimum weight unvisited city
        for (int v = 0; v < totalCities; v++) {
            if (!visited[v] && weight[v] < min) {
                min = weight[v];
                u = v;
            }
        }

        visited[u] = true; // Mark the city as visited

        // Update the weights of adjacent cities
        for (int v = 0; v < totalCities; v++) {
            if (!visited[v] && distance[u][v] && distance[u][v]  < weight[v]) {
                parent[v] = u;
                weight[v] = distance[u][v];
            }
        }
    }

    // Display the Minimum Spanning Tree
    cout << "\nEdge \tWeight\n";
    for (int i = 1; i < totalCities; i++) {
        cout << cities[parent[i]] << " -> " << cities[i] << " \t" << distance[i][parent[i]] << " \n";
        mstvalue = mstvalue + distance[i][parent[i]];

    }
    cout << "Total Distance of MST is : " << mstvalue << endl;
}
// display in square matrix form
void IMS::display() {
    cout << "\nAdjacency Matrix (Distances between Cities):\n";
    for (int i = 0; i < totalCities; i++) {
        for (int j = 0; j < totalCities; j++) {
            cout << distance[i][j] << "\t";
        }
        cout<<endl;
    }
}

/* PRINTING IN TABULAR FORM
void display()
    {
        cout << "\nAdjacency Matrix (Fuel between Cities):\n";
        cout << "\t";       //cross space
        for (int j = 0; j < numofcities; j++)
        {
            cout << cities[j] << "\t";
        }
        cout << endl;
        for (int i = 0; i < numofcities; i++)
        {
            cout << cities[i] << "\t";
            for (int j = 0; j < numofcities; j++)
            {
                if (cities[i] == cities[j])
                {
                    cout << "0\t";
                }
                else
                {
                    cout << adj[i][j] << "\t";
                }
            }
            cout << endl;
        }

*/

int main(){
    interviewer.accept();
    interviewer.display();
    interviewer.primsAlgorithm();
    return 0;
}
