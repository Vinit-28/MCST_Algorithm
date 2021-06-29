
// This File Contains the Utilities i.e. Build Graph Method and its Components //

#include<iostream>
#include<vector>

#define INFINITY INT32_MAX

using namespace std;

// Class Graph to Make a Graph Structure //
class Graph{

	public:
		int vertices, edges;
		vector<vector<int>> adjacency_matrix;
};


// Function to Build a Graph //
Graph Build_Graph(){

	Graph MyGraph;
	int i,j,starting_point,ending_point,path_cost;

	cout<<"Enter Nuber of Vertices :- ";
	cin>>MyGraph.vertices;

	cout<<"Enter Number of Edges :- ";
	cin>>MyGraph.edges;

	for(i=0; i<MyGraph.vertices; i++){
		
        MyGraph.adjacency_matrix.push_back(vector<int>(MyGraph.vertices));
        for(int j=0; j<MyGraph.vertices; j++){

            if( i==j )
                MyGraph.adjacency_matrix[i][j] = 0;
            else
                MyGraph.adjacency_matrix[i][j] = INFINITY;
        }
	}

	for(int i=0;i<MyGraph.edges;i++){

		cout<<"\nEnter the Starting Point of Edge "<<i+1<<" :- ";
		cin>>starting_point;
		cout<<"Enter the Ending Point of Edge "<<i+1<<" :- ";
		cin>>ending_point;
        cout<<"Enter Path Cost :- ";
        cin>>path_cost;

        MyGraph.adjacency_matrix[starting_point][ending_point] = path_cost;
        MyGraph.adjacency_matrix[ending_point][starting_point] = path_cost;
	}

	cout<<"\nGraph has Build Successfully!!!\n";
	return MyGraph;
}
// END of this Funtion //
