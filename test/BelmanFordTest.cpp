#include "../src/Graph.hpp"
#include "../src/BelmanFord.hpp"
#include "../src/Flags.hpp"
#include "testparty/catch.hpp"

#include <map>
#include <vector>

TEST_CASE("BelmanFord: Calculate ways")
{
    Graph correctGraph("test/graphs/correct_graph.txt");
    Graph cycleNegativeGraph("test/graphs/cycle_negative.txt");
    Graph cyclePositiveGraph("test/graphs/cycle_positive.txt");

    BelmanFord belmanFord(&correctGraph);

    belmanFord.RunAlgoritmMin("A");
    map<string, float> correctWeights = { {"A", 0}, {"B", 5}, {"C", 4}, {"D", 7}, {"E", 7} };
    CHECK((belmanFord.lengthWays == correctWeights && belmanFord.GetLastError() == ErrorFlag::NONE));

    belmanFord.Reset();
    belmanFord.SetGraph(&cycleNegativeGraph);
    belmanFord.RunAlgoritmMin("1");
    CHECK(belmanFord.GetLastError() == ErrorFlag::CYCLE_NEGATIVE_WEIGHT);
    
    belmanFord.Reset();
    belmanFord.SetGraph(&cyclePositiveGraph);
    belmanFord.RunAlgoritmMax("1");
    CHECK(belmanFord.GetLastError() == ErrorFlag::CYCLE_POSITIVE_WEIGHT);

}