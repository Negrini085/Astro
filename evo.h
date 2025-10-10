#ifndef __evo__
#define __evo__

#include <iostream>
#include <cmath>

#include </home/filippo/Desktop/CODICINI/Astro/condin.h>

using namespace std;

// Funzione per calcolare la distanza fra due particelle
vector<vector<double>> GetD2(vector<Particella> conf){
    double x1, x2, y1, y2, dist2;
    vector<vector<double>> appo = vector<vector<double>>(conf.size(), vector<double>(conf.size(), 0.0));
    
    for(int i=0; i<conf.size()-1; i++){
        for(int j=i+1; j<conf.size(); j++){
            x1 = conf[i].GetR()*cos(conf[i].GetT());
            x2 = conf[j].GetR()*cos(conf[j].GetT());
            y1 = conf[i].GetR()*sin(conf[i].GetT());
            y2 = conf[j].GetR()*sin(conf[j].GetT());

            dist2 = pow((x2 - x1), 2) + pow((y2 - y1), 2);
            appo[i][j] = dist2;
        }
    }

    return appo;
}



class Sistema{
    public:
        Sistema(CondIn &condin){
            conf = condin.GetS();
            dist = GetD2(conf);
        }

        

    protected:
        vector<Particella> conf;
        vector<vector<double>> dist;

};

#endif