
// This is the implementation of the Algorithm to fin the MCST for a graph ( Undirected Graph Only* ) //

#include<queue> // Importing Queue to implement BFS //
#include "Utils.cpp" // Importing Utils i.e. Class and Method to Build a Graph //




// Function to find the index of the shortest vertex from the given vertex list //
int get_shortest_distance_vertex(vector<int> &adj_list,int except){

    int min_edge = INFINITY, index;
    for(int i=0;i<adj_list.size();i++){

        if( i != except && min_edge > adj_list[i] ){
            min_edge = adj_list[i];
            index = i;
        }
    }
    return index;
}
// END of this Function //



// Function to find the index of the minimum weighted edge from the edge list //
int get_minimum_weighted_edge(vector<pair<pair<int,int>, int>> &candidates){

    int index=-1,min_weight=INFINITY;

    for(int i=0;i<candidates.size();i++){

        if( candidates[i].second < min_weight ){

            min_weight = candidates[i].second;
            index = i;
        }
    }
    return index;
}
// END of this Function //



// Function to find the remaining edges left after the First-Half //
vector<pair<pair<int,int>, int>> get_remaining_edges(Graph &MyGraph){

    // vector<pair<pair< starting_point_of_edge, ending_point_of_edge> , path_cost>> //
    vector<pair<pair<int,int>, int>> remaining_edges;

    for(int i=0;i<MyGraph.vertices;i++){

        for(int j=0;j<MyGraph.vertices;j++){

            if( MyGraph.adjacency_matrix[i][j] != 0 && MyGraph.adjacency_matrix[i][j] != INFINITY ){
                
                remaining_edges.push_back( { {i , j}, MyGraph.adjacency_matrix[i][j] } );
                MyGraph.adjacency_matrix[i][j] = INFINITY;
                MyGraph.adjacency_matrix[j][i] = INFINITY;
            }
        }
    }

    return remaining_edges;
}
// END of this Function //



// Function to remove an vertex from the list //
void remove_node(vector<int> &lst, int key){

    for(int i=0;i<lst.size();i++){
        if(key==lst[i]){
            lst.erase(lst.begin()+i);
            break;
        }
    }
}
// END of this Function //



// Function to find whether the given edge will make a loop in the graph or not ( In this we are using BFS with little modification )//
bool will_it_create_a_loop(pair<int,int> &connection, vector<vector<int>> adj_list, int total_vertices){

    vector<bool> is_in_the_queue(total_vertices,false);
    queue<int> nodes;

    is_in_the_queue[connection.first] = is_in_the_queue[connection.second] = true;

    nodes.push(connection.first);
    nodes.push(connection.second);

    while(nodes.empty()==false){

        int curr_node = nodes.front();
        nodes.pop();

        for(auto n: adj_list[curr_node]){
            
            if(is_in_the_queue[n])
                return true;
            
            is_in_the_queue[n] = true;
            remove_node(adj_list[n],curr_node);
            nodes.push(n);
        }
    }

    return false;
}
// END of this Function //



// Function to apply Algorithm to find the Minimum Cost Spanning Tree of the given graph //
pair<int, vector<vector<int>>> Find_MCST(Graph &MyGraph){

    vector<int> is_edge_created(MyGraph.vertices,0);
    vector<vector<int>> adj_list(MyGraph.vertices);
    int total_edges=0,total_cost=0,i;



    // This is the Starting of the First-Half of the Algorithm ( Finding Minimum Weighted Edges for Every Vertex ) //
    for(int i=0;i<MyGraph.vertices;i++){

        if( is_edge_created[i] == 0 ){
            
            // Finding the closed vertex for the current vertex //
            int shortest_distance_vertex = get_shortest_distance_vertex(MyGraph.adjacency_matrix[i],i);

            if( MyGraph.adjacency_matrix[i][shortest_distance_vertex] == INFINITY ){
                cout<<"\nThere Should be no Isolated Vertex\n";
                exit(0);
            }

            // Adding the Edge between the current vertex and the new closed vertex in the graph //
            total_edges += 1;
            total_cost += MyGraph.adjacency_matrix[i][shortest_distance_vertex];
            adj_list[i].push_back(shortest_distance_vertex);
            adj_list[shortest_distance_vertex].push_back(i);
            MyGraph.adjacency_matrix[i][shortest_distance_vertex] = INFINITY;
            MyGraph.adjacency_matrix[shortest_distance_vertex][i] = INFINITY;
            is_edge_created[i] = 1;
            is_edge_created[shortest_distance_vertex] = 1;
        }
    }
    // END of First Half (Now the grpah has been converted into some trees)//




    // This is the Starting of the Second-Half of the Algorithm ( Finding Minimum Wighted Vertex that will not create a loop ) //
    if( total_edges < (MyGraph.vertices-1) ){
        
        // Getting Remaining Edges that were left after First Half //
        auto remaining_edges = get_remaining_edges(MyGraph);

        // Looping/Finding Valid Required Edges //
        while(total_edges < (MyGraph.vertices-1) ){

            // This will contain information about those edges that will not gonna create a loop in the graph //
            vector<pair<pair<int,int>, int>> candidates;

            for(int i=0;i<remaining_edges.size();i++){

                // if the edge is an valid edge ( i.e. it will not create a loop ) then it will be considered as a candidate to be the next counted edge for MCST //
                if( ! will_it_create_a_loop(remaining_edges[i].first,adj_list,MyGraph.vertices) ){
                    
                    candidates.push_back(remaining_edges[i]);
                }
            }

            // Getting Minimum Wieghted edge amnog all the Candidates //
            int min_edge_index = get_minimum_weighted_edge(candidates);
            
            if(min_edge_index == -1){

                cout<<"\nInvalid Graph\n";
                exit(0);
            }

            // Adding the new Minimum Wieghted Valid Edge in the graph //
            adj_list[candidates[min_edge_index].first.first].push_back(candidates[min_edge_index].first.second);
            adj_list[candidates[min_edge_index].first.second].push_back(candidates[min_edge_index].first.first);
            total_edges += 1;
            total_cost += candidates[min_edge_index].second;
            candidates.erase(candidates.begin()+min_edge_index);

            remaining_edges = candidates;
        }
    }

    return {total_cost, adj_list};
}
// END of this Function //



// Main Function //
int main(){

    auto MyGraph = Build_Graph();
    auto answer = Find_MCST(MyGraph);
    cout<<"\nTotal Minimum Cost :- "<<answer.first<<endl;

    for(int i=0;i<MyGraph.vertices;i++){

        cout<<"Vertex "<<i<<" is Connected with :- ";
        for(int j=0;j<answer.second[i].size();j++)
            cout<<answer.second[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
// END of this Function //