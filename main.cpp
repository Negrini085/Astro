#include <iostream>

#include </home/filippo/Desktop/CODICINI/Astro/evo.h>
#include </home/filippo/Desktop/CODICINI/Astro/condin.h>

using namespace std;

int main(){

    CondIn condin = CondIn(1000);
    condin.stampaSis();

    Sistema sist = Sistema(condin);
    sist.simula(1e-3, 4000);

    return 0;
}
