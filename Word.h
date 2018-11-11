#ifndef WORD_H
#define WORD_H
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class Word
{
    string word;
    vector<int>  frequency;
    vector<double> pWord;


  public:
    Word(string wrd,int classPosition,int totalClass)
    {
      int i = 0;
      word = wrd;
      while(i<totalClass)
      {
        frequency.push_back(0);
        i++;
      }
      frequency.at(classPosition)++;
    }

    Word(string wrd)
    {

      word = wrd;
    }

    string getWord()
    {
        return word;
    }

    int getFrequency(int classPosition)
    {
        return frequency.at(classPosition);
    }


    double getProbability(int classPosition)
    {
        return pWord.at(classPosition);
    }

    void incrementFrequency(int classPosition)
    {
      frequency.at(classPosition)++;
    }

    void calculateProbability(vector<DocumentClass> &classes,int vocabularySize)
    {

       for (int q = 0; q < frequency.size(); ++q)
        {
          pWord.push_back(1000*((double)(frequency.at(q)+1))/((double)(classes.at(q).getDocumentListSize()+vocabularySize)));
        }
    }

    void pushProbability(double prob)
    {
      pWord.push_back(prob);
    }




};
#endif
