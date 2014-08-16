// read visitortraversal.h

#include "visitortraversal.h"

void visitorTraversal::commonQueries(SgNode *n, std::string nm) {
    //finds static variable calls
    Rose_STL_Container<SgNode*> svr = NodeQuery::querySubTree (n,V_SgVarRefExp);
    for (Rose_STL_Container<SgNode*>::iterator i = svr.begin(); i != svr.end(); i++) {
        SgVarRefExp *Exp = isSgVarRefExp(*i);
        SgClassDefinition *scp = isSgClassDefinition(Exp->get_symbol()->get_declaration()->get_scope());
        if(scp != NULL) {
            this->ans[nm].insert( scp->get_mangled_name().getString() );
        }
    }

    //finds static funtion calls
    Rose_STL_Container<SgNode*> sfn = NodeQuery::querySubTree (n,V_SgMemberFunctionRefExp);
    for (Rose_STL_Container<SgNode*>::iterator i = sfn.begin(); i != sfn.end(); i++) {
        SgMemberFunctionRefExp *Exp = isSgMemberFunctionRefExp(*i);
        this->ans[nm].insert( Exp->getAssociatedMemberFunctionDeclaration()->get_associatedClassDeclaration()->get_name().getString() );
    }

    //finds class types
    Rose_STL_Container<SgNode*> ctp = NodeQuery::querySubTree (n,V_SgClassType);
    for (Rose_STL_Container<SgNode*>::iterator i = ctp.begin(); i != ctp.end(); i++) {
        SgClassType *classDefinition = isSgClassType(*i);
        this->ans[nm].insert(classDefinition->get_name().getString());
        this->ans[classDefinition->get_name().getString()];
    }
}

void visitorTraversal::visit(SgNode *n)
   {
    //finds a class definition
    if (isSgClassDefinition(n) != NULL) {
        SgClassDefinition *cd = isSgClassDefinition(n);
        std::string nm = cd->get_mangled_name().getString();
        this->ans[nm];

        //finds parents
        Rose_STL_Container<SgBaseClass*> parents = cd->get_inheritances();
        for (Rose_STL_Container<SgBaseClass*>::iterator i = parents.begin(); i != parents.end(); i++) {
            this->ans[nm].insert( (*i)->get_base_class()->get_name().getString() );
        }

        this->commonQueries(n, nm);
    }
    //finds a memberfunction declaration and search in its definition
    if(isSgMemberFunctionDeclaration(n) != NULL) {
        SgMemberFunctionDeclaration *mfd = isSgMemberFunctionDeclaration(n);
        SgClassDeclaration *scd;
        if((scd = mfd->get_associatedClassDeclaration()) != NULL) {
            std::string nm = scd->get_mangled_name().getString();
            this->ans[nm];

            this->commonQueries(n, nm);
        }
    }
}
