#include<iostream>
#include<fstream>
#include <sstream>
#include <string>
#include <vector>
#include<stdlib.h>
#include<stdio.h>



using namespace std;

int main(){
    cout.setf(ios::fixed,ios::floatfield);  //Using integer to output rather than using powers
    cout.precision(0);  //All data are given in integer so 0 decimal places
    ifstream csvInput("input.csv");   //Import data
    string oneline;


    int data[4];
    int row=0;
    vector<int> T,  Q, P;  //TimeStamp, Quantity, Price
    vector<string> S;  //Symbol


    string _partOfstr;


    while(getline(csvInput,oneline)){  //This while let us put all data into 4 vectors
        istringstream _Readstr(oneline);


        for(int i = 0; i < 4; i++)
	    {

		getline(_Readstr, _partOfstr, ',');
		if(i!=1){
            data[i] = atoi(_partOfstr.c_str());

	    }
	    else
        {
            S.push_back(_partOfstr);

        }



        }
        T.push_back(data[0]);
        Q.push_back(data[2]);
        P.push_back(data[3]);


        row++;



    }





    vector<string> C;  //class of different Symbols
    vector<int> Mtg, Tvt, Twp, Mtp;   //Maximum time gap, Total volume traded, Total Weighted price, Max trade price
    vector<int> LT;  //last trade time of some instruments



    for(int j=0; j< row; j++)
    {
        int a=0;  //judge whether there already exists this symbol
        int k=0;
        for(int d=0;d < C.size();d++)
        {
            if(S[j]==C[d])
            {
                a=1;
                k=d;
                break;
            }
            else
            {
                ;
            }

        }
        if(a==0)//A new type of instrument
        {
                // Add one more element in each vector
                C.push_back(S[j]);
                Mtg.push_back(0);//Initialize the maximum time gap as 0. If there is only one trade record then it is exactly 0 as question asks to do so
                Tvt.push_back(Q[j]);
                Twp.push_back(Q[j]*P[j]);
                Mtp.push_back(P[j]);
                LT.push_back(T[j]);
        }
        else//A seen instrument
        {
            if(T[j]-LT[k]>=Mtg[k])
            {
                Mtg[k]=T[j]-LT[k];
            }
            else
            {
                ;
            }

            Tvt[k]=Tvt[k]+Q[j];

            Twp[k]=Twp[k]+Q[j]*P[j];

            if (Mtp[k]>=P[j])
            {
                ;
            }
            else
            {
                Mtp[k]=P[j];
            }

            LT[k]=T[j];
        }


    }

    int n=C.size();

    vector<float> Wap(n);//Weighted average price
    for(int z=0;z<n;z++)
    {
        Wap[z]=Twp[z]/Tvt[z];//dot division

    }

    for(int l=0;l<n;l++)//Using BubbleSort to sort the symbols, we could also using other sort method if the number of different symbols is large
    {

        for(int r=0;r<n-l-1;r++)
        {
            if (bool(C[l] > C[l + 1]))
			{
				swap(C[l],C[l+1]);
				swap(Mtg[l],Mtg[l+1]);
				swap(Tvt[l],Tvt[l+1]);
				swap(Wap[l],Wap[l+1]);
				swap(Mtp[l],Mtp[l+1]);
			}

        }
    }






    for(int z=0;z<n;z++)//print
    {
        std::cout<<C[z]<<","<<Mtg[z]<<","<<Tvt[z]<<","<<Wap[z]<<","<<Mtp[z]<<endl;
    }

    ofstream p;
    p.open("output.csv",ios::out|ios::trunc);                //Create or open the output file
    for(int z=0;z<n;z++)//print
    {
        p<<C[z]<<","<<Mtg[z]<<","<<Tvt[z]<<","<<Wap[z]<<","<<Mtp[z]<<endl;
    }
    p.close();



    return 0;

}


