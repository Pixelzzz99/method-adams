#include <stdio.h>
#include <math.h>

double state_deriv(double Vc, double I, double OCV1, double C, double Rct)
{
    double newVc = (OCV1 - Vc) / (C * Rct) - (I / C);
    return newVc;
}

double predict(double Vc, double Vc_[], double dt, 
        double I_[], double OCV1_[], double C_[], double Rct_[])
{
    double fn[4];
    fn[0] = state_deriv(Vc_[0], I_[0], OCV1_[0], C_[0], Rct_[0]);
    fn[1] = state_deriv(Vc_[1], I_[1], OCV1_[1], C_[1], Rct_[1]);
    fn[2] = state_deriv(Vc_[2], I_[2], OCV1_[2], C_[2], Rct_[2]);
    fn[3] = state_deriv(Vc_[2], I_[3], OCV1_[3], C_[3], Rct_[3]);

    double yip = Vc_[3] + (dt/24) * (55 * fn[3] - 59 * fn[2] + 37 * fn[1] - 9 * fn[0]);
    return yip;
}

double corrector(double Vc, double Vc_[], double Vc1, 
        double dt, double I_[], double OCV1_[], 
        double C_[], double Rct_[])
{
    double e = 0.000001; //Prediction 
    double Vc1c = Vc1;

    double fn[4];

    fn[1] = state_deriv(Vc_[1], I_[1], OCV1_[1], C_[1], Rct_[1]);
    fn[2] = state_deriv(Vc_[2], I_[2], OCV1_[2], C_[2], Rct_[2]);
    fn[3] = state_deriv(Vc_[3], I_[3], OCV1_[3], C_[3], Rct_[3]);

    do
    {
        Vc1 = Vc1c;
        fn[4] = state_deriv(Vc_[4], I_[4], OCV1_[4], C_[4], Rct_[4]);

        Vc1c = Vc_[3] + (dt/24) * (9 * fn[4] + 19 * fn[3] - 5*fn[2] + fn[1]);
    }
    while(fabs(Vc1c - Vc1) > e);

    return Vc1c;
}

double predictor_corrector(double Vc, double dt, 
        double I[], double* OCV1, 
        double* C, double* Rct)
{

}

int main()
{
    return 0;
}
