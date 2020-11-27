#include "main.h"

using namespace std;


int main()
{
    int n=50; //dim of the generation
    float a=5;
    float b=-5;
    int n_generations=1000; //anzahl generations

    //init random number generator


    //create generation with random values.
    vector<Individual> gen;

    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    auto real_rand = std::bind(std::uniform_real_distribution<float>(a,b),
                               mt19937(seed));


    ofstream f;
    f.open("/Users/samuelruhl/predicting_crystal_structures/Data/genetic_data.txt");
    f<<"Generation"<<" "<<"x"<<" "<<"y"<<" "<<"f(x,y)"<<" "<<"fitness"<<"\n";
    for(int i=0;i<n;i++){
        float x = real_rand();
        float y = real_rand();
        gen.push_back(Individual({x,y},a,b));
        f<<0<<" "<<gen[i].genom[0]<<" "<<gen[i].genom[1]<<" "<<gen[i].phaenom<<" "<<gen[i].fitness<<'\n';
    }
    //perform evolution
    vector<vector<Individual>> Generations = {gen};
    for(int i = 0;i<n_generations;i++){
        vector<Individual> tmp_gen={};
        //elithismus: take the fittest into the new generation
        Generations[i] = sort_by_fitness(Generations[i]);
        tmp_gen.push_back(Generations[i][n-1]);
        for(int j = 0;j<n-1;j++){
            Individual kid = selection(Generations[i]);
            tmp_gen.push_back(kid);
            tmp_gen[j].generation=i+1;
            f<<i+1<<" "<<tmp_gen[j].genom[0]<<" "<<tmp_gen[j].genom[1]<<" "<<tmp_gen[j].phaenom<<" "<<tmp_gen[j].fitness<<'\n';
        }
        Generations.push_back(tmp_gen);
    }
    f.close();
    Generations[n_generations] = sort_by_fitness(Generations[n_generations]);
    Individual winner=Generations[n_generations][n-1];
    cout<<"x="<<winner.genom[0]<<" y="<<winner.genom[1]<<" bei "<<winner.phaenom<<" mit  DNA:";
    winner.print_dna();
    cout<<winner.fitness<<endl;
}