#ifndef __evo__
#define __evo__

#include <iostream>
#include <cmath>

#include </home/filippo/Desktop/CODICINI/Astro/condin.h>

using namespace std;



// Funzione per calcolare la distanza fra due particelle
vector<vector<double>> GetD2(vector<double> x, vector<double> y){
    double dist2;
    vector<vector<double>> appo = vector<vector<double>>(x.size(), vector<double>(x.size(), 0.0));
    
    for(int i=0; i<x.size()-1; i++){
        for(int j=i+1; j<x.size(); j++){
            dist2 = pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2);
            appo[i][j] = dist2;
            appo[j][i] = dist2;
        }
    }

    return appo;
}


void GetD2(vector<vector<double>> &appo, vector<double> x, vector<double> y){
    double dist2;
    
    for(int i=0; i<x.size()-1; i++){
        for(int j=i+1; j<x.size(); j++){
            dist2 = pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2);
            appo[i][j] = dist2;
            appo[j][i] = dist2;
        }
    }
}


class Sistema{
    public:
        Sistema(CondIn &condin){
            vector<Particella> conf = condin.GetS();

            for(int i=0; i<conf.size(); i++){
                x.push_back(conf[i].GetR()*cos(conf[i].GetT()));
                y.push_back(conf[i].GetR()*sin(conf[i].GetT()));
                vx.push_back(conf[i].GetVr()*cos(conf[i].GetT()) - conf[i].GetVt()*sin(conf[i].GetT()));
                vy.push_back(conf[i].GetVr()*sin(conf[i].GetT()) + conf[i].GetVt()*cos(conf[i].GetT()));
            }
            dist = GetD2(x, y);
        }

        void evolvi(){
            vector<double> pos
        }
        





    protected:
        vector<double> x, xold, y, yold;
        vector<double> vx, vy;

        vector<vector<double>> dist, old;

};

#endif