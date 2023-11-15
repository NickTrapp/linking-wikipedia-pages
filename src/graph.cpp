#include "graph.h"
#include <queue>

/**
 * The function performs a breadth-first search on a graph to find the shortest path between two nodes.
 *
 * @param start The start parameter is the index of the starting node in the graph.
 * @param end The "end" parameter in the above code refers to the index of the node in the graph that
 * you want to find a path to.
 *
 * @return a vector of integers, which represents the path from the start node to the end node in a
 * graph. If the start or end node is out of bounds or if there is no path from the start to the end
 * node, an empty vector is returned.
 */
std::vector<int> Graph::BFSpath(int start, int end)
{
    // basic checks for size out of bounds errors
    if ((start < 0 || start >= (int)map.size()) || (end < 0 || end >= (int)map.size()))
    {
        return std::vector<int>();
    }

    std::queue<int> q;
    std::set<int> visited;
    q.push(start);
    visited.insert(start);
    // path keeps track of which nodes point to which
    // key is node being pointed to and value is node that the edge is coming from
    std::map<int, int> path;
    bool found = false;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        if (v == end)
        {
            found = true;
            break;
        }
        for (size_t i = 0; i < map[v]->edges.size(); ++i)
        {
            int num = map[v]->edges.at(i);
            if (visited.find(num) == visited.end())
            {
                visited.insert(num);
                q.push(num);
                path[num] = v;
            }
        }
    }

    std::vector<int> vect;
    // if end is not found, return empty vector
    if (!found)
    {
        return vect;
    }
    // go backwards through path to get return vector
    // this will be backwards, so we must reverse
    while (end != start)
    {
        vect.push_back(end);
        end = path[end];
    }

    vect.push_back(start);

    std::reverse(vect.begin(), vect.end());

    return vect;
}

/**
 * The IDDFS function performs an iterative deepening depth-first search on a graph to find the
 * shortest path between two nodes within a specified maximum depth.
 *
 * @param start The start parameter is the index of the starting node in the graph.
 * @param end The "end" parameter in the IDDFS function represents the target node or vertex in the
 * graph that we want to reach from the starting node.
 * @param max_depth The parameter "max_depth" represents the maximum depth or level of the search that
 * will be performed in the IDDFS (Iterative Deepening Depth-First Search) algorithm. It determines how
 * deep the algorithm will explore the graph before giving up and returning -1 if the target node is
 * not found.
 *
 * @return an integer value. If a valid path is found within the specified maximum depth, the function
 * returns the depth level at which the path was found. If no valid path is found within the maximum
 * depth, the function returns -1.
 */
int Graph::IDDFS(int start, int end, int max_depth)
{
    // basic checks for size out of bounds errors
    if ((start < 0 || start >= (int)map.size()) || (end < 0 || end >= (int)map.size()))
    {
        return -1;
    }
    // run depth level search for each depth until max_depth
    for (int i = 0; i <= max_depth; ++i)
    {
        if (DLS(start, end, i))
        {
            return i;
        }
    }

    return -1;
}

/**
 * The DLS function in the Graph class checks if there is a path from a given start node to an end node
 * within a specified limit of depth.
 *
 * @param start The start parameter represents the starting node or vertex in the graph.
 * @param end The "end" parameter in the code represents the target node or vertex that we want to
 * reach in the graph.
 * @param limit The parameter "limit" represents the maximum depth or level of the depth-limited
 * search. It determines how deep the search algorithm will explore the graph before giving up.
 *
 * @return a boolean value.
 */
bool Graph::DLS(int start, int end, int limit)
{
    if (start == end)
    {
        return true;
    }
    if (limit <= 0)
    {
        return false;
    }

    for (size_t i = 0; i < map[start]->edges.size(); ++i)
    {
        if (DLS(map[start]->edges[i], end, limit - 1))
        {
            return true;
        }
    }
    return false;
}

/**
 * The function `PopulatePageRank` calculates the significance of each node in a graph based on the
 * number of times it is visited during a random walk.
 *
 * @param damping The damping parameter is a value between 0 and 100 that determines the probability of
 * skipping to a random node in the graph. If the randomly generated number is less than the damping
 * value, the algorithm will skip to a random node.
 * @param iterations The parameter "iterations" represents the number of iterations or steps to be
 * performed in the PageRank algorithm. It determines how many times the algorithm will randomly
 * traverse the graph and update the significance of each node based on the number of times it has been
 * visited.
 */
void Graph::PopulatePageRank(int damping, int iterations)
{
    // the key in SignificanceMap is the key for accessign Node and its int is the times it has been visited
    std::map<int, int> signficanceMap;
    int curr = 0;
    int count = iterations;

    while (iterations > 0)
    {
        bool skip = (rand() % 100) < damping;
        // if the random generated number between 0 to 99 is less than damping you skip to random node in graph
        if (skip || map[curr]->edges.empty())
        {
            curr = rand() % map.size();
            signficanceMap[curr] += 1;
        }
        else
        {
            // here you skip to a random node that is connected to the current node within the smae cluster
            int temp = rand() % map[curr]->edges.size();
            curr = map[curr]->edges[temp];
            signficanceMap[curr] += 1;
        }

        iterations--;
    }

    for (auto node : signficanceMap)
    {
        Node *&currNode = map[node.first];

        // this takes the total ties it was visited/ total iterations to get like the percent of times it was visited
        currNode->signficance = ((double)node.second / (double)count);
    }
}

/**
 * The function FindMostSignificantNode iterates through all nodes in a graph and returns the key of
 * the node with the highest significance value.
 *
 * @return the key of the most significant node in the graph.
 */
int Graph::FindMostSignificantNode()
{
    // The current best key
    int current_best_key = 0;
    // settign significance value to something low
    int greatest_significance = -1;
    for (auto iterate = map.begin(); iterate != map.end(); iterate++)
    {
        // iterates through every node in the graph
        if (iterate->second->signficance > greatest_significance)
        {
            // basically if there is a more significant node you change the current key to set it as the new node and change significance
            current_best_key = iterate->first;
            greatest_significance = iterate->second->signficance;
        }
    }

    return current_best_key;
}

/**
 * The function takes user input for starting and ending nodes in a graph and returns them as a vector
 * of integers.
 *
 * @return a vector of integers.
 */
std::vector<int> Graph::userNodeInput()
{
    std::string startingNode;
    std::string endingNode;
    std::vector<int> result;

    std::cout << "Starting Node: ";
    std::cin >> startingNode;

    std::cout << "Ending Node: ";
    std::cin >> endingNode;

    result.push_back(stoi(startingNode));
    result.push_back(stoi(endingNode));

    return result;
}

/**
 * The function `userPageRankInput` takes user inputs for the damping factor and number of iterations,
 * and returns them as a vector of integers.
 *
 * @return a vector of integers.
 */
std::vector<int> Graph::userPageRankInput()
{
    std::string damping;

    std::string iterations;
    std::vector<int> result;

    std::cout << "Damping Factor (0-100): ";
    std::cin >> damping;

    std::cout << "Number of Iterations: ";
    std::cin >> iterations;

    result.push_back(stoi(damping));
    result.push_back(stoi(iterations));

    return result;
}
