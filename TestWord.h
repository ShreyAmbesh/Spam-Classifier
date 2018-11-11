#ifndef TESTWORD_H
#define TESTWORD_H
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class TestWord
{
    string word;
    int  frequency;
    double pWord;


  public:
    TestWord(string wrd)
    {
      word = wrd;
      frequency = 1;
    }

    string getWord()
    {
        return word;
    }

    int getFrequency()
    {
        return frequency;
    }


    double getProbability()
    {
        return pWord;
    }

    void incrementFrequency()
    {
      frequency++;
    }

    void setProbability(double prob)
    {
        pWord = prob;
    }



};
#endif
