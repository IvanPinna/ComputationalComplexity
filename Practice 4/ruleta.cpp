#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct pareja{
    int father, mother;
};

vector<pareja> selectParents(vector<int> ciudades, int num_parejas){
    vector<pareja> parejas; //Aqui dentro va el coste de cada ciudad. 
    float *probabilidades = new float[ciudades.size()];
    
    //Calcular probabilidades de cada ciudad.
    float total = 0; 
    for(unsigned i = 0; i < ciudades.size(); ++i)
        total += ciudades.at(i);
    
    cout << "Coste total -> " << total << endl;  
    //Calcular la probabilidad de cada ciudad. 
    float suma = 0;
    for(unsigned i = 0; i < ciudades.size(); ++i)
    {
        probabilidades[i] = ciudades.at(i)/total;
        cout << "Probabilidad de " << i << " -> " << probabilidades[i] << endl;
        suma+=probabilidades[i];
    }   
    //cout << "Suma: " << suma << endl;
    //Generar numero aleatorio para seleccionar elemento
    int seleccionado = 0, elemento = 0;
    float dado, acumulado;
    bool bandera =false;
    for(int i = 0; i < num_parejas*2; ++i) //Cada pareja tiene dos elementos. 
    {
        //Generar numero aleatorio para seleccionar elemento
        dado = (float)rand()/RAND_MAX;///(RAND_MAX);
        elemento = 0;
        acumulado = probabilidades[elemento];
        bandera = false;
        while(!bandera)
        {
            if(dado < acumulado)
            {
                bandera = true;
                seleccionado = elemento;
                cout << "Dado -> " << dado << " seleccionado " << seleccionado << endl;
            }
            else
            {
                elemento++;
                acumulado+=probabilidades[elemento];
                
            }
        }
    }
    
    delete probabilidades;
    return parejas;    
}


int main(int argc, char *argv[]){
    vector<int> ciudades; 
    vector<pareja> parejas;
    
    ciudades.push_back(10);
    ciudades.push_back(25);
    ciudades.push_back(5);
    ciudades.push_back(30);
    ciudades.push_back(16);
    
    parejas = selectParents(ciudades, 3); //Para que devuelva tres parejas. 
}
