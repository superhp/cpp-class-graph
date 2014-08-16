#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QDir>

int main(int n, char *makes[])
{
    for(int i=1; i<n; i++)
    {
        //a program for dealing with 'make' and selecting source files
        QFile f(QDir::tempPath() + "/readMakeOut");
        f.open(QIODevice::Append | QIODevice::Text);
        QTextStream ts(&f);

        QString make = QString(makes[i]);
        if(make.contains(QRegExp("^.+\.(C|cc|cxx|c|cpp|c/+/+|h|hpp|H|hxx)$")))
        {
            ts << make << " ";
        }
    }
    return 0;
}
