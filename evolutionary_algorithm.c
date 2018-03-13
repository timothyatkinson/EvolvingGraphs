#include "evolutionary_algorithm.h"

Result* run_EA(EAArgs* args){
  Graph* population = args->initialisation(args->init_env_pointer);
  double* scores = args->evaluate(population, args->evaluation_env_pointer);
  int generation = 0;
  while(generation < args->generations && !args->termination(population, scores, args->termination_env_pointer)){
    population = args->select_repopulate(population, scores, args->select_repopulate_env_pointer);
    scores = args->evaluate(population, args->evaluation_env_pointer);
    if(args->update > 0 && args->update % generation == 0){
      int popsize = sizeof(scores) / sizeof(double);
      double bestScore = 99999999999999.9;
      if(args->maximise){
        bestScore = bestScore * -1.0;
      }
      int winner = -1;
      for(int i = 0; i < popsize; i++){
        if(args->maximise){
          if(scores[i] > bestScore){
            bestScore = scores[i];
            winner = i;
          }
        }
        else{
          if(scores[i] < bestScore){
            bestScore = scores[i];
            winner = i;
          }
        }
      }
      printf("Generation %d: winner %d has score %lf out of %d individuals\n", generation, winner, bestScore, popsize);
    }
  }
  Result* res = malloc(sizeof(Result));

  int popsize = sizeof(scores) / sizeof(double);
  double bestScore = 99999999999999.9;
  if(args->maximise){
    bestScore = bestScore * -1.0;
  }
  int winner = -1;
  for(int i = 0; i < popsize; i++){
    if(args->maximise){
      if(scores[i] > bestScore){
        bestScore = scores[i];
        winner = i;
      }
    }
    else{
      if(scores[i] < bestScore){
        bestScore = scores[i];
        winner = i;
      }
    }
  }
  res->winning_graph = population[winner];
  res->winnerScore = bestScore;
  res->generation = generation;
  res->terminated = generation == args->generation;
  if(args->update > 0){
    printf("Generation %d TERMINATED with score %lf\n", generation, res->winnerScore);
  }
}
