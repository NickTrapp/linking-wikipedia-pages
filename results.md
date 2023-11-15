# Results

Our leading question was to create a search tool that finds the distance between two Wikipedia nodes and an algorithm that ranks the pages based on importance. We answered these questions by writing three algorithms that accomplish these goals:

1. `BFS` Traversal: Implemented a BFS traversal to find the shortest path between two nodes.
2. `IDDFS` Algorithm: Implemented an IDDFS algorithm that also finds the shortest path between two nodes.
3. `PageRank` Algorithm: Implemented a PageRank algorithm that finds the "significance" of each node and returns the node with the highest importance.

However, we were unable to implement a function that directly compares the performance (runtime and space complexity) between the BFS traversal and IDDFS algorithm. As a group, we had issues making the files on some of our computers, which limited our productivity. To resolve this, those of us who were having these issues had to run our code on other members' machines. Despite these challenges, we managed to overcome them through good collaboration and communication.

## Graph Representation

For our graph representation of the data, we used a Node struct with the following fields:

- `title`: Represents the name of the Wikipedia page (string).
- `edges`: Represents the IDs of the pages that the current page contains links to (vector of integers).
- `significance`: Represents the significance of each node, calculated using the PageRank algorithm (double).

We used a map with integers as keys and node pointers as values to represent our graph. The integer keys correspond to the IDs of the pages that the corresponding node value represents.

## BFSpath Function

The `BFSpath` function takes in two integers, `start` and `end`, which correspond to the IDs of two nodes in our dataset. It performs the BFS algorithm to find the shortest path between the nodes. During the execution of the BFS algorithm, it populates a map from integer to integer to keep track of which nodes are pointing to each other. The map's key represents the node being pointed to, and the value represents the node from which the edge is originating.

Once the end node is found, the function loops back through this map until it reaches the start node and populates a vector containing the IDs of all the nodes in the shortest path from start to end. We tested this function using both the full dataset and a shorter modified version of it. We manually performed the algorithm on our dataset and ensured that the function returned the same ordered vector as our test cases. We also tested various edge cases, such as when the start and end nodes have the same value, to verify the expected behavior (an empty vector). The running time for this function is optimal - O(N + E) - where N is the number of nodes in the graph and E is the number of edges.

## IDDFS Function

The `IDDFS` function takes in three integers - `start`, `end`, and `max_depth` - and finds the shortest distance between the starting and ending nodes using an iterative deepening depth-first search. It returns the value of this distance as an integer. The start and end values represent the IDs of the nodes we are looking for a path between, and the max_depth value is the maximum distance from the start node that we check.

In the function, for each distance from 1 up to max_depth, we call a helper function called `DLS` (Depth-Limited Search) that checks if the end node is within that distance from the starting node. If it is, we return that distance. If we go through all the distances up to max_depth and still don't find the end node, we return -1.

We tested this function by performing the algorithm manually on our dataset and verifying that the function produced the same result. We also ensured that the function returns one less than the size of the `BFSpath` vector when called on the same two nodes and that their distance is less than or equal to max_depth. The running time for this function is also O(N + E) - where N is the number of nodes in the graph and E is the number of edges - because it iterates over each node in a given number of levels.

## FindMostSignificantNode Function

The `FindMostSignificantNode` function runs through each node in our graph and returns the key (ID of the node) with the highest significance. It iterates through the entire graph, and each time the current node's significance is greater than the current maximum significance, it updates the maximum significance key and value.

The runtime for this function is O(N), where N is the number of vertices, because it loops through each node in the graph. We created a test case for the sample data only due to the large number of nodes in the full dataset (over 4 million) and the arbitrary significance values. The test case for this function on the sample data passed (the node with ID = 20 had the most links and connections, and thus the highest significance), indicating that the function worked properly.

## PopulatePageRank Function

The `PopulatePageRank` function takes a `damping factor` (ranging from 0 to 100) and an `iteration` parameter. The damping factor determines the likelihood of the function skipping to a random node in the graph. The iteration parameter indicates how many times the function will iterate through the nodes.

Each time a node is visited, the corresponding value in the significance map is incremented by 1. After going through all the iterations, each node will be assigned a `significance value`. This value is calculated by taking the node's corresponding value in the significance map and dividing it by the number of iterations. A low significance value (close to 0) indicates that a node is not significant, while higher values indicate higher significance.

The running time of this function is O(N), where N is the number of iterations. We wrote test cases comparing the significance of highly important nodes (many links and edges) with non-important nodes (no links), and the test cases passed. We also checked the correctness of PopulatePageRank by implementing the function within the `FindMostSignificantNode` test cases. The node with the most connections and links (ID = 20) was the node returned by FindMostSignificantNode, confirming that the PopulatePageRank function was correct.
