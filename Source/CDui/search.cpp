// read search.h

#include <search.hpp>
#include <QDir>

using namespace std;
using namespace boost;

void search::findDeps(string dest)
{
     vector<string> sources;
     sources.push_back("-");    //as in argv, the first element is not used

     //gets the source files to analyze
     QFile f(QDir::tempPath() + "/readMakeOut");
     f.open(QIODevice::ReadOnly | QIODevice::Text);
     QTextStream ts(&f);
     QString make;
     while(!ts.atEnd())
     {
        ts >> make;
        if(make.compare(""))
        {
            string tmp = dest + "/" + make.toStdString();
            sources.push_back(tmp);
        }
     }
     f.close();

     SgProject* project = frontend(sources);    //rose project
     ROSE_ASSERT (project != NULL);

     // Call the traversal starting at the project node of the AST
     et.traverseInputFiles(project,preorder);

     //writes the classes array
     int i = 0;
     this->C = new string[1000];
     for(std::map< std::string, std::set<std::string> >::iterator it = et.ans.begin(); it != et.ans.end(); ++it) {
         C[i] = it->first;
         i++;
     }

     this->n = i;
}

int search::getClassesNum()
{
    return this->n;
}

std::string * search::getClasses()
{
    return this->C;
}

void search::Manage(QList<string> mC, int level)
{
    used_by.clear();
    int i = 0;
    map<string,int> ind2;
    foreach (string ss, mC) {
        ind2[ss] = i++;
    }
    QList<string> tmp(mC);
    QList<string> add(mC);

    //the procedure to manage the graph (edges) for selected classes and depth only
    for(int l=0; l<level && (add.size()!=0 || l==0) || add.size()!=0 && level==-1; l++){
        mC.clear();
        mC = add;
        add.clear();
        for(std::map< std::string, std::set<std::string> >::iterator it = et.ans.begin(); it != et.ans.end(); ++it) {
            for(std::set<std::string>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2) {
                if(mC.contains(it->first))
                {
                    if(!tmp.contains(*it2))
                    {
                        tmp.push_back(*it2);
                        add.push_back(*it2);
                        ind2[*it2] = i++;
                    }
                    used_by.push_back(Edge( ind2[it->first], ind2[*it2] ));
                }
            }
        }
    }
    mCan = tmp.size();
    mCa = new std::string[mCan];                //and the selected classes (with found depth classes included)
    std::copy(tmp.begin(), tmp.end(), mCa);
}

void search::showGraph()
{
    typedef adjacency_list< vecS, vecS, directedS,      property< vertex_color_t, default_color_type >,      property< edge_weight_t, int >    > Graph;
    Graph g(used_by.begin(), used_by.end(), mCan);

    string dot = QDir::tempPath().toStdString() + "/tmp.dot";
    ofstream tmp(dot.c_str());
    write_graphviz(tmp, g, make_label_writer(mCa));
    tmp.close();

    // !!!!!!!!!!!!!! this should be in the same dir
    string qr = "java -Xmx1024M -Xms512M -jar " + QDir::currentPath().toStdString() + "/zgrviewer/zgrviewer-0.9.0.jar " + QDir::tempPath().toStdString() + "/tmp.dot";

    system(qr.c_str());
}
