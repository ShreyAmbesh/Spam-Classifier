#ifndef DOCUMENTCLASS_H
#define DOCUMENTCLASS_H
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class DocumentClass
{
    int classId;
    string className;
    vector<string>  documentList;
    double classProbability;


  public:
    DocumentClass(int id,string name)
    {
      classId = id;
      className = name;
    }

    DocumentClass(int id,string name,double prob)
    {
      classId = id;
      className = name;
      classProbability = prob;
    }
    string getClassName()
    {
        return className;
    }

    int getClassId()
    {
        return classId;
    }

    void addDocument(string doc)
    {
      documentList.push_back(doc);
    }


    string getLastDocument()
    {
      return documentList.back();
    }

    string getDocument(int pos)
    {
      return documentList.at(pos);
    }

    int getDocumentListSize()
    {
        return documentList.size();
    }

    void setClassProbability(double prob)
    {
      classProbability = prob;
    }

    double getClassProbability()
    {
      return classProbability;
    }

};
#endif
