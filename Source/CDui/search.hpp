#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <QList>
#include <map>
#include <set>
#include <vector>
#include <QVector>
#include <QFile>
#include <QTextStream>

#include <boost/graph/graphviz.hpp>

#include "visitortraversal.h"

typedef std::pair<int,int> Edge;                    //an edge in a graph

class search {
private:
    int n;                                          //number of classes
    std::vector<Edge> used_by;                      //edges: class to class vector
    visitorTraversal et;                            //object for map
    std::string *C;                                 //distinct classes
    int mCan;                                       //number of selected classes
    std::string *mCa;                               //selected classes
public:
    void findDeps(std::string dest);                //creates a graph
    int getClassesNum();
    std::string * getClasses();
    void Manage(QList<std::string> mC, int level);  //creates a subgraph of selected classes
    void showGraph();
};


#endif // SEARCH_HPP
