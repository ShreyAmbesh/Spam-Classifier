#include <iostream>
#include <dirent.h>
#include <ctype.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "DocumentClass.h"
#include "Word.h"
#include "merge_sort.h"
#include <vector>
#include <string>

using namespace std;

vector<string> stopWords;
vector<DocumentClass> classes;
vector<Word> vocabulary;

void loadStopWords()
{
  FILE* inp;
  inp = fopen("stop_words.lykn","r");//filename of your data file
  if (inp==NULL)
  {
    printf("FILE MISSING stop_words.lykn NOT FOUND\n");
    exit(0);
  }
  int i = 0;
  while(1){
      char r = tolower((char)fgetc(inp));
      string temp;
      while(r!=' ' && !feof(inp)){
            //read till , or EOF

        temp.push_back(r);
              //store in array
        r = tolower((char)fgetc(inp));
      }

      temp.push_back('\0');//make last character of string null
      stopWords.push_back(temp);

      if(feof(inp)){    //check again for EOF
          break;
      }
      i++;
  }
  for(int j = 0;j<stopWords.size();j++){
      cout<<stopWords.at(j)<<endl; //print vector
  }
  fclose(inp);

}


void makeDocList()
{
  DIR *dirF;

  struct dirent *entF;
  for (int i = 0; i < classes.size(); ++i)
  {

    cout<<"\n\n\n"<<classes.at(i).getClassName()<<endl;
    if ((dirF = opendir(classes.at(i).getClassName().c_str())) != NULL) {
      int p=0;
    while ((entF = readdir(dirF)) != NULL) {


      if (entF->d_type == DT_REG ) {

        string temp;
        temp = classes.at(i).getClassName();
        temp.push_back('/');
        temp = temp + entF->d_name;
        classes.at(i).addDocument(temp);
        cout<<classes.at(i).getLastDocument()<<"  "<<classes.at(i).getClassId()<<endl;
        }
       }
    closedir(dirF);
  } else{
    cout<<"File Not Found "<<endl;
    exit(0);
  }
  }
}


void makeClassList()
{
  DIR *dir;
  int n=0;
  struct dirent *ent;

  if ((dir = opendir("./")) != NULL) {

    while ((ent = readdir(dir)) != NULL) {

      if((ent->d_type != DT_REG) && (!(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0 || strcmp(ent->d_name,".git") == 0)))
      {
        DocumentClass nm(n,ent->d_name);
        classes.push_back(nm);
        cout<<classes.back().getClassName()<<endl;
        n++;
      }

    }

    closedir(dir);
  } else{
    cout<<"ERROR"<<endl;
    return;
  }
}






void createVocabulary()
{   int p = 0;
    FILE* inp;
    FILE *meg;
  for(int i=0;i<classes.size();i++)
  {

        for(int j=0;j<classes.at(i).getDocumentListSize();j++)
        {
        cout<<classes.at(i).getDocument(j)<<endl;
        inp = fopen(classes.at(i).getDocument(j).c_str(),"r");//filename of your data file

        while(1){
            char r = tolower((char)fgetc(inp));
            int k = 0,z=0;
            string wrd;
            while(r!=' '  && !feof(inp)){

              if(r=='a' || r=='b' || r=='c' || r=='d' || r=='e' || r=='f' || r=='g' || r=='h' ||
                 r=='i' || r=='j' || r=='k' || r=='l' || r=='m' || r=='n' || r=='o' || r=='p' ||
                 r=='q' || r=='r' || r=='s' || r=='t' || r=='u' || r=='v' || r=='w' || r=='x' ||
                 r=='y' || r=='z')
                {
                  wrd.push_back(r);
                  z=1;
                }
              else if(r!='\'')
              {
                break;
              }

              r = tolower((char)fgetc(inp));


            }

            if (z==1)
          {
              wrd.push_back('\0');
              int check=0;
              for (int k = 0; k < stopWords.size(); ++k)
              {
                if(stopWords.at(k)==wrd)
                  {
                    check=1;
                    break;
                  }

              }

              for (int k = 0; k < vocabulary.size(); ++k)
              {
                if(vocabulary.at(k).getWord()==wrd)
                  {
                    vocabulary.at(k).incrementFrequency(i);
                    check=2;
                    break;
                  }

              }

              if(check==0)
              {
                Word newWord(wrd,i,classes.size());
                vocabulary.push_back(newWord);
                //printf("%s  %d\n", vocab[p],frequncy[vocabularySize-1][fileClass[j]]);

                p++;

              }

          }





                //make last character of string null
            if(feof(inp)){    //check again for EOF
                break;
            }


        }

        fclose(inp);
      }
  }
  cout<<"Sort Starting"<<endl;

  MergeSort sorter;
  sorter.sort(vocabulary);
  cout<<vocabulary.size()<<endl;
  for (int j = 0; j < vocabulary.size(); ++j)
  {
    vocabulary.at(j).calculateProbability(classes,vocabulary.size());
  }
  cout<<"Sort Starting 2"<<endl;
  meg=fopen("beast.lykn","w+");
  for(int j = 0;j<vocabulary.size();j++){

    //cout<<"Saving"<<endl;
    cout<<vocabulary.at(j).getWord(); //print array
      fprintf(meg,"%s", vocabulary.at(j).getWord().c_str());
    
    for (int i = 0; i < classes.size(); ++i)
    {
        cout<<" "<<vocabulary.at(j).getProbability(i); //print array
        fprintf(meg," %lf",vocabulary.at(j).getProbability(i));
    }
    cout<<endl; //print array
        fprintf(meg,"\n");

  }

  fclose(meg);


}

void storeInfo()
{
  FILE *fp=fopen("info.lykn","w+");
  double tsz=0.0;
  for (int j = 0; j < classes.size(); ++j)
    {
      tsz=tsz+classes.at(j).getDocumentListSize();
    }
  for (int i = 0; i < classes.size(); ++i)
  {
    double csz=classes.at(i).getDocumentListSize();
    double pClass=100*csz/tsz;
    classes.at(i).setClassProbability(pClass);
    fprintf(fp, "%s %lf\n",classes.at(i).getClassName().c_str(),pClass);
  }
  fclose(fp);

}

int main() {

  makeClassList();
  makeDocList();
  loadStopWords();
  createVocabulary();
  storeInfo();
  return 0;


}
