#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct pareja{
    int x_, y_;
    
    pareja(int x, int y):x_(x), y_(y)
    {}
    
    pareja()
    {}
};

vector<pareja> selectParents(const vector<int>& ciudades, int num_parejas){
    vector<pareja> parejas; //Aqui dentro va el coste de cada ciudad. 
    vector<int> seleccionado;
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
    
    //Generar numero aleatorio para seleccionar elemento
    int elemento = 0;
    float dado, acumulado;
    bool bandera =false;
    for(int i = 0; i < num_parejas*2; ++i) //Cada pareja tiene dos elementos. 
    {
        //Generar numero aleatorio para seleccionar elemento
        dado = (float)rand()/RAND_MAX;
        elemento = 0;
        acumulado = probabilidades[elemento];
        bandera = false;
        while(!bandera)
        {
            if(dado < acumulado)
            {
                bandera = true;
                seleccionado.push_back(elemento);
                cout << "Dado -> " << dado << " seleccionado " << seleccionado.at(i) << endl;
                cout << RAND_MAX << endl;
            }
            else
            {
                elemento++;
                acumulado+=probabilidades[elemento];
                
            }
        }
    }
    
    //Agrupamos en parejas los elementos seleccionados.
    for(int i = 0; i < num_parejas*2; i+=2)
    {
        cout << "Pareja -> " << seleccionado[i] << "," << seleccionado[i+1] << endl;
        parejas.push_back(pareja(seleccionado[i], seleccionado[i+1]));
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
    
    parejas = selectParents(ciudades, ciudades.size()); //Para que devuelva tres parejas. 
}
