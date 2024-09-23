#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
struct PathLoss
{
    double A;
    double B;
    double C;
    double ca, di, ba, mo, ppl;
};

double PL(PathLoss P)
{
   
    P.B = ((1.1 * log10(P.ca) - 0.7) * P.mo) - (1.56 * log10(P.ca)) + 0.8;
    P.A = 69.55 + (26.16 * log10(P.ca)) - (13.82 * log10((int)P.ba)) - P.B;
    P.C = 44.9 - (6.55 * log10(P.ba));
    double pl = P.A + (P.C * log10(P.di));
    return pl;
}

int main()
{
    FILE* fp, * fp1 = NULL;
    char f[20] = {}, nf[20] = {};
    cout << "Please write the name of file:" << endl;
    cin >> f;
    if ((fp = fopen(f, "r")) == NULL)
    {
        printf("cannot open the file.\n"); exit(1);
    }
    else
    {
        printf("\nyes the file is here.\n\n");
        PathLoss *n = {};
      
        int flag = 0;
        double sum = 0, min = 100000, max = 0;
        cout << "please write the name of file where you want to save data: ";
        cin >> nf;
        fp1 = fopen(nf, "w");
        fprintf(fp1, "Carrier Freq\t Distance\t  \tBase Station    Mobile Station \tPath Loss\n");
        cout << "\nCarrier Freq\t" << "Distance\t" << "Base Station\t" << "Mobile Station\t" << "Path Loss";
        int z = 0;
        fscanf(fp, "%d\t", &z);
        n = new PathLoss[z];
        for (int i = 0;i < z;i++)
        {
            cout << "\n";
            for (int j = 0;j < 4;j++)
            {
                double nh[4];
                fscanf(fp, "%lf\t", &nh[j]);
                printf("%lf\t", nh[j]);
                fprintf(fp1, "%lf\t\t", nh[j]);
                n[i].ca = nh[0];
                n[i].di = nh[1];
                n[i].ba = nh[2];
                n[i].mo = nh[3];
                if (n[i].ca < 150 || n[i].ca >1500) flag = 1;
                else flag = 0;

            }
           n[i].ppl = PL(n[i]);
            if (n[i].ca < 150 || n[i].ca>1500) cout << "NOT VALID";
            else  cout << n[i].ppl;
          
            if (flag == 0)
            {
                if (max < n[i].ppl) max = n[i].ppl;

                if (min > n[i].ppl) min = n[i].ppl;
            }
            

            sum += n[i].ppl;
            if (flag == 1) fprintf(fp1, "NOT VALID\n");
            else fprintf(fp1, "%lf\n", n[i].ppl);
           
        }
        
        cout << "\n\nThe average PL = " << sum / z << " dB";
        fprintf(fp1, "\nThe average PL = %lf dB", sum / z);

        cout << "\n\nThe max PL = " << max << " dB";
        fprintf(fp1, "\nThe max PL = %lf dB", max);

        cout << "\n\nThe min PL = " << min << " dB";
        fprintf(fp1, "\nThe min PL = %lf dB", min);
    }
    printf("\n");
}
