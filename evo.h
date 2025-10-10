#ifndef __evo__
#define __evo__

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include </home/filippo/Desktop/CODICINI/Astro/condin.h>

using namespace std;



// Funzione per calcolare la distanza fra due particelle
vector<vector<double>> GetD(vector<double> &x, vector<double> &y, double eps=1e-6){
    double dist2;
    vector<vector<double>> appo = vector<vector<double>>(x.size(), vector<double>(x.size(), 0.0));
    
    for(int i=0; i<x.size()-1; i++){
        for(int j=i+1; j<x.size(); j++){
            dist2 = pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2);
            appo[i][j] = sqrt(dist2 + eps);
            appo[j][i] = appo[i][j];
        }
    }

    return appo;
}


void GetD(vector<vector<double>> &appo, vector<double> &x, vector<double> &y, double eps=1e-6){
    double dist2;
    
    for(int i=0; i<x.size()-1; i++){
        for(int j=i+1; j<x.size(); j++){
            dist2 = pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2);
            appo[i][j] = sqrt(dist2 + eps);
            appo[j][i] = appo[i][j];
        }
    }
}


double forceX(vector<vector<double>> &appo, vector<double> &x, int ind){
    double force = 0;
    
    for(int i=0; i<x.size(); i++){ 
        if(i == ind){ continue; }
        force += (x[i] - x[ind])/(appo[ind][i]*appo[ind][i]*appo[ind][i]); 
    }

    return force;
}


double forceY(vector<vector<double>> &appo, vector<double> &y, int ind){
    double force = 0;
    
    for(int i=0; i<y.size(); i++){ 
        if(i == ind){ continue; }
        force += (y[i] - y[ind])/(appo[ind][i]*appo[ind][i]*appo[ind][i]); 
    }

    return force;
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
            dist = GetD(x, y);
        }

        void evolvi(double dt){
            xold = x;
            yold = y;
            for(int i=0; i<x.size(); i++){
                x[i] = xold[i] + vx[i] * dt + forceX(dist, xold, i) * pow(dt, 2)/2; 
                y[i] = yold[i] + vy[i] * dt + forceY(dist, yold, i) * pow(dt, 2)/2; 
            }
            
            oldist = dist;
            GetD(dist, x, y);
            for(int i=0; i<x.size(); i++){
                vx[i] += (forceX(dist, x, i) + forceX(oldist, xold, i)) * dt/2;
                vy[i] += (forceY(dist, y, i) + forceY(oldist, yold, i)) * dt/2;
            }
        }

        void simula(double dt, int nstep){
            for(int i=0; i<nstep; i++){
                cout << "Passo: " << i+1 << endl;
                evolvi(dt);
                energia();
                if(i%100 == 0 && i != 0){ stampaConf(i); }
            }

            stampaEne();
        }

        void energia(){
            double kin = 0;
            double pot = 0;

            for(int i=0; i<vx.size(); i++){
                kin += (vx[i]*vx[i] + vy[i]*vy[i])*0.5;
            }

            for(int i=0; i<vx.size(); i++){
                for(int j=i+1; j<vx.size(); j++){
                    pot -= 1/dist[i][j];
                }
            }
            
            enek.push_back(kin);
            enep.push_back(pot);
        }

        void stampaConf(int ind){
            ofstream fileout;

            fileout.open("conf" + to_string(ind) + ".conf");
            for(int i=0; i<x.size(); i++){
                fileout << x[i] << "  " << y[i] << "  " << vx[i] << "  " << vy[i] << endl;
            }
            fileout.close();
        }

        void stampaEne(){
            ofstream fileout;

            fileout.open("ene.dat");
            for(int i=0; i<enek.size(); i++){
                fileout << enek[i] << " " << enep[i] << endl;
            }
            fileout.close();
        }


    protected:
        vector<double> x, xold, y, yold;
        vector<double> vx, vy, enek, enep;

        vector<vector<double>> dist, oldist;

};

#endif