#ifndef RTVTFILTERCONTROLLER_H
#define RTVTFILTERCONTROLLER_H

class RTVTFilterController
{
public:
    RTVTFilterController();

	void decimate(int from, int to);
};

/*
filteredData[i] =
Convolution(i,input,BCoefficients)-Convolution(i,filteredData,ACoefficients);

//answer = conv(signal, filtercoefficients)

double Convolution(int iIndex, vec& iData, vec& iCoefficients)
{
     double answer = 0;
     for(int l=0; l<iCoefficients.size();l++)
     {
         if((iIndex-l-1)>=0)
         {
             answer+= iData(iIndex-l-1)*iCoefficients(l);
         }
         else
         {
             answer+=0.0;
         }
     }
     return answer;
}
*/

#endif // RTVTFILTERCONTROLLER_H
