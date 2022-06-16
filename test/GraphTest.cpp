#include "../src/Graph.hpp"
#include "../src/Flags.hpp"
#include "testparty/catch.hpp"

TEST_CASE("Graph: Parce file with a graph")
{
    Graph testGraph("test/graphs/correct_graph.txt");
    CHECK(testGraph.GetLastError() == ErrorFlag::NONE);

    Graph testGraph_2("test/graphs/cycle_negative.txt");
    CHECK(testGraph_2.GetLastError() == ErrorFlag::NONE);

    Graph testGraph_3("test/graphs/111_graph.txt");
    CHECK(testGraph_3.GetLastError() == ErrorFlag::FILE_NOT_FOUND);

}