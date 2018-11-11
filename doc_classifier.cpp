#include <iostream>
#include <dirent.h>
#include <ctype.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "DocumentClass.h"
#include "Word.h"
#include "TestWord.h"
#include "merge_sort.h"
#include <vector>
#include <string>
#include <cmath>

vector<string> stopWords;
vector<TestWord> test;
vector<DocumentClass> classes;
vector<Word> vocabulary;
vector<double> pTest;
int classesSize=0;


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
  /*for(int j = 0;j<stopWords.size();j++){
      cout<<stopWords.at(j)<<endl; //print vector
  }*/
  fclose(inp);

}


void createTestData()
{
	FILE* inp;
  	inp = fopen("test.txt","r");//filename of your data file
  	if (inp==NULL)
    {
    	printf("FILE MISSING test.txt NOT FOUND\n");
    	exit(0);
    }
  	int i = 0,p=0;
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
          //wrd.push_back('\0');
          int check=0;
          for (int k = 0; k < stopWords.size(); ++k)
          {
            if(stopWords.at(k)==wrd)
              {
                check=1;
                break;
              }

          }

          for (int k = 0; k < test.size(); ++k)
          {
            if(test.at(k).getWord()==wrd)
              {
                test.at(k).incrementFrequency();
                check=2;
                break;
              }

          }

          if(check==0)
          {
            TestWord newTestWord(wrd);
            test.push_back(newTestWord);



            p++;

          }


      }
      /*for(int x=0;x<test.size();x++)
      cout<<test.at(x).getWord()<<"-"<<test.at(x).getFrequency()<<endl;*/





            //make last character of string null
        if(feof(inp)){    //check again for EOF
            break;
        }


    }

    fclose(inp);


}

void loadModel()
{
	FILE *inp=fopen("info.lykn","r");
    if (inp==NULL)
    {
    	cout<<"FILE MISSING info.lykn NOT FOUND\n";
    	exit(0);
    }

	while(1)
	{	    char r = tolower((char)fgetc(inp));
      	int k = 0;
      	int chk=0;
      	string line = "";
      	while(r!='\n' && !feof(inp)){
            //read till , or EOF
        	line.push_back(r);
          r = tolower((char)fgetc(inp));

        	chk=1;
      	}
        line.push_back('\n');
        line.push_back('\0');

      	if(chk==1)
      	{
      			char *className = new char[100];
            double pClass;
      			sscanf(line.c_str(),"%s %lf",className,&pClass);
      			DocumentClass clss(classesSize,className,pClass);
            classes.push_back(clss);
          classesSize++;}
          //make last character of string null
      	if(feof(inp)){    //check again for EOF
          break;
      	}

    }
    fclose(inp);
    //printf("%d\n",classesSize );





    inp=fopen("beast.lykn","r");
    if (inp==NULL)
    {
    	printf("FILE MISSING beast.lykn NOT FOUND\n");
    	exit(0);
    }
	while(1)
	{
      	if(feof(inp)){
          break;
      	}
    char *wrd = new char[100];
    string swrd;
    double pWord;
		fscanf(inp,"%s",wrd);
    //cout<<wrd<<endl;
    swrd = wrd;
    Word clss(swrd);

		for (int i = 0; i < classesSize; ++i)
		{
			fscanf(inp,"%lf",&pWord);
      clss.pushProbability(pWord);
		}
    vocabulary.push_back(clss);
    char r = (char)fgetc(inp);
    //cout<<"Word = "<<clss.getWord()<<"-"<<clss.getProbability(0)<<" "<<clss.getProbability(1)<<" "<<clss.getProbability(2)<<endl;

    if(feof(inp)){
      break;
    }

    }
    fclose(inp);


}

int search(string srch)
{
	int dwn=0,up=vocabulary.size(),mid;

	while(dwn<up)
	{

		mid=(up+dwn)/2;
		if(srch.compare(vocabulary.at(mid).getWord())==0)
		{
			return mid;
		}
		else if(vocabulary.at(mid).getWord()>srch)
		{
			up=mid-1;
		}
		else
		{
			dwn=mid+1;
		}
	}
	return -1;
}



void predictClass()
{
	for (int i = 0; i < classes.size(); ++i)
	{
		pTest.push_back(classes.at(i).getClassProbability());
	}
	for (int i = 0; i < test.size(); ++i)
	{
		int pos=search(test.at(i).getWord());
		if (pos!=-1)
		{
			for (int j = 0; j < classes.size(); ++j)
			{
				pTest.at(j)=pTest.at(j)*pow(vocabulary.at(pos).getProbability(j),test.at(i).getFrequency());

      }
		}
	}
	int resultPos;
	long double pMax=-1;
	for (int i = 0; i < classes.size(); ++i)
	{
		if(pTest.at(i)>pMax)
		{

			pMax=pTest.at(i);
			resultPos=i;
		}
	}
  cout<<"The Document is of "<<classes.at(resultPos).getClassName()<<" Class\n";

}

int main()
{
	loadStopWords();
	createTestData();
	loadModel();
	predictClass();
  return 0;

}
