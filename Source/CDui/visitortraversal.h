#ifndef VISITORTRAVERSAL_H
#define VISITORTRAVERSAL_H

#include <rose.h>

class visitorTraversal : public AstSimpleProcessing
{
public:
    std::map< std::string, std::set<std::string> > ans;     //the result map
    virtual void visit(SgNode* n);                          //AST visitor:
                                                            //  visits class definitions and member function definitions
                                                            //  !! some intersection occurs (not affecting the results),
                                                            //  so it should be optimyzed for not visiting same function defs
private:
    void commonQueries(SgNode *n, std::string nm);          //queries for finding static vars, static funs and class types
                                                            // !! revisiting occurs (not affecting the results), so one inner
                                                            //visitor implementation would be more efficient than some queries
};

#endif // VISITORTRAVERSAL_H
