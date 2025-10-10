#ifndef __condin__
#define __condin__

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

class Particella{
    public:
    Particella(double mass, double posr, double post, double vr, double vt){
        par = {mass, posr, post, vr, vt};
    }

    // Metodi Set/Get
    double GetM(){ return par[0]; }
    double GetR(){ return par[1]; }
    double GetT(){ return par[2]; }
    double GetVr(){ return par[3]; }
    double GetVt(){ return par[4]; }
    void SetM(double mass){ par[0] = mass; }
    void SetR(double posr){ par[1] = posr; }
    void SetT(double post){ par[2] = post; }
    void SetVr(double vrad){ par[3] = vrad; }
    void SetVt(double vazim){ par[4] = vazim; }

    protected:
        vector<double> par;
};



class CondIn{
    public:
    CondIn(int npart){
        double r, appo;

        // Creo engine per estrarre numeri casuali
        mt19937 rng(std::random_device{}());
        uniform_real_distribution<double> unif(0.0, 1.0);
        normal_distribution<double> gauss(0.0, 0.1);

        // Ciclo per inizializzazione delle posizioni
        // Devo rispettare la distribuzione adeguata
        for(int i=0; i<npart; i++){

            do{
                r = 10 * unif(rng);
                appo = unif(rng); 
            }while(r > 0.5 && appo > (r+1-0.5)*exp(-(r - 0.5)));

            if(r<0.5){ appo = sqrt(M_PI*r); }
            else{ appo = sqrt(M_PI*(8.25-(2*r*r + 5*r + 5)*exp(-(r-0.5)))/r); }
            
            sistema.push_back(Particella(1, r, 2*M_PI*unif(rng), 3*gauss(rng), appo*(1+0.3*gauss(rng))));
        }
    }

    // Metodo per stampare a file
    void stampaSis(){
        ofstream fileout;
        fileout.open("condin.conf");

        for(int i=0; i<sistema.size(); i++){
            fileout << sistema[i].GetM() << "   " << sistema[i].GetR() << "   " << sistema[i].GetT() << "   " << sistema[i].GetVr() << "   " << sistema[i].GetVt() << endl;
        }
        fileout.close();
    }

    // Metodo per estrarre sistema
    vector<Particella> GetS(){ return sistema; }


    protected:
        vector<Particella> sistema;
};

#endif