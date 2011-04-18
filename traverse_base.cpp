#include <boost/foreach.hpp>
#include "pugixml.hpp"
#include "foreach.hpp"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
string process_node(T &node) {
    string result;
    string name = node.name();

    if(name == "BBCostCalculator") {
        cout << "creating a BBCostCalculator" << endl;
        result = "BBCostCalculator"; 
    } else if(name == "TimingCalculator") {
        cout << "creating a TimingCalculator" << endl;
        result = "TimingCalculator";
    } else if(name == "CostAggregator") {
        result = "(";
        BOOST_FOREACH(pugi::xml_node &child, node) {
            result += process_node(child) + ",";
        }
        result += ")";
        cout << "creating a " << name << ": " << result << endl;
    } else {
        cout << "unrecognized node type: " << name << endl;
    }
    return result;
}

int main() {
    vector<int> level_count;
    pugi::xml_document doc;
    if (!doc.load_file("test.xml")) return -1;


    //[code_traverse_base_basic
    pugi::xml_node root = doc.first_child();
    cout << process_node(root) << endl;
    //]
    return 0;
}

// vim:et
