#include "data-parser.h"

/**
 * The function `PopulateGraph` reads data from a file, parses it line by line, and creates nodes in a
 * graph based on the parsed data.
 *
 * @param graph The `graph` parameter is a reference to an object of type `Graph`. It is the graph that
 * we want to populate with data from the input file.
 * @param filename The `filename` parameter is a string that represents the name of the file that
 * contains the data to be parsed and used to populate the graph.
 */
void DataParser::PopulateGraph(Graph &graph, const std::string filename)
{
    std::ifstream inputFile;
    inputFile.open(filename);
    std::string line;

    // parsing input file line by line
    while (getline(inputFile, line))
    {
        int id;
        std::string title;
        std::string tempString;
        std::stringstream inputString(line);

        getline(inputString, tempString, ',');
        id = atoi(tempString.c_str());
        getline(inputString, title, ',');

        // checking data corrrectedness + making node & populating graph
        if (!title.empty() && id >= 0)
        {
            Graph::Node *node = new Graph::Node;
            node->title = title;
            graph.map[id] = node;
        }

        line = "";
    }
}

/**
 * The function `PopulateEdgeRelationships` reads data from a file, parses each line to extract start
 * and end values, and populates the edge vector of a graph object with the extracted values if they
 * are within a certain range.
 *
 * @param graph The "graph" parameter is an object of the Graph class. It represents a graph data
 * structure that contains nodes and edges.
 * @param filename The `filename` parameter is a string that represents the name of the input file that
 * contains the edge relationships data.
 */
void DataParser::PopulateEdgeRelationships(Graph &graph, const std::string filename)
{
    std::ifstream inputFile;
    inputFile.open(filename);
    std::string line;

    // parsing input file line by line
    while (getline(inputFile, line))
    {
        int start;
        std::string tempStringStart;
        int end;
        std::string tempStringEnd;
        std::stringstream inputString(line);

        getline(inputString, tempStringStart, ' ');
        start = atoi(tempStringStart.c_str());
        getline(inputString, tempStringEnd, ' ');
        end = atoi(tempStringEnd.c_str());

        // checking data corrrectedness + populating edge vector
        if ((start >= 0 && start <= 4206784) && (end >= 0 && end <= 4206784))
        {
            graph.map[start]->edges.push_back(end);
        }

        line = "";
    }
};