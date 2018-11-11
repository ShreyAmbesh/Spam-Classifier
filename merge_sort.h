#ifndef MERGESORT_H
#define MERGESORT_H
#include <iostream>
#include "Word.h"
class MergeSort{
		vector<Word> *vocab;
	public:
		MergeSort()
		{

		}
		void merge(int a,int b,int c)
		{

			int n1=b-a+1,n2=c-b,i,j,k;
			vector<Word> ar1,ar2;
			for (i = 0; i <n1; ++i)
			{
				ar1.push_back(vocab->at(a+i));
			}

			for (j = 0; j <n2; ++j)
			{
				ar2.push_back(vocab->at(b+j+1));
			}

			i=0;
			j=0;
			for (k = a; i<n1 && j<n2; ++k)
			{

				if(ar1.at(i).getWord()>ar2.at(j).getWord())
				{
					vocab->at(k)=ar2.at(j);
					j++;
				}
				else
				{
					vocab->at(k)=ar1.at(i);
					i++;
				}
			}


		    while (i < n1)
		    {
						vocab->at(k)=ar1.at(i);
		        i++;
		        k++;
		    }


		    while (j < n2)
		    {

						vocab->at(k)=ar2.at(j);
		        j++;
		        k++;
		    }


		}


		void mergeSortVocabulary(int p,int r)
		{
			if (p<r)
			{
				int q=(p+r)/2;

				mergeSortVocabulary(p,q);
				mergeSortVocabulary(q+1,r);
				merge(p,q,r);
			}

		}

		void sort(vector<Word> &voc)
		{
			vocab = &voc;
			mergeSortVocabulary(0,voc.size()-1);
		}
};
#endif
