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
};

double PL(PathLoss P, double ca, double di, double ba, double mo)
{
    P.B = ((1.1 * log10(ca)- 0.7) * mo ) - ( 1.56 * log10(ca)) + 0.8;
    P.A = 69.55 + (26.16 * log10(ca)) - ( 13.82 * log10((int)ba)) -  P.B;
    P.C = 44.9 - (6.55 * log10(ba));
    double pl = P.A + (P.C * log10(di));
    if (ca < 150 || ca>1500) cout << "NOT VALID";
    
    else  cout << pl;
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
        double n[4] = {};
        double q;
        

        int flag = 0;
        double sum = 0, min = 100000, max = 0;
        cout << "please write the name of file where you want to save data: ";
        cin >> nf;
        fp1 = fopen(nf, "w");
        fprintf(fp1, "Carrier Frequency\t Distance\t  \tBase Station    Mobile Station \tPath Loss\n");
        cout << "\nCarrier Freq\t" << "Distance\t" << "Base Station\t" << "Mobile Station\t" << "Path Loss";
        fscanf(fp, "%lf\t", &n[0]);
        const  float z = n[0];
        for (int i = 0;i < z;i++)
        {
            cout << "\n";
            for (int j = 0;j < 4;j++)
            {
                fscanf(fp, "%lf\t", &n[j]);
                printf("%lf\t", n[j]);
                fprintf(fp1, "%lf\t\t", n[j]);
                if (n[0] < 150 || n[0] >1500) flag = 1;
                else flag = 0;
            }
            PathLoss PP{};
            q = PL(PP, n[0], n[1], n[2], n[3]);
            
            if (flag == 0)
            {
                if (max < q) max = q;
               
                if (min > q) min = q;
            }
            
            sum += q;
            if (flag == 1) fprintf(fp1, "NOT VALID\n");
            else fprintf(fp1, "%lf\n", q);
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


