#include "evolutionary_algorithm.h"
#include "utils.h"

Result** run_multi(EAArgs** args, int runs){
  Result** results = malloc(runs * sizeof(Result*));
  for(int i = 0; i < runs; i++){
    Result* r = run_EA(args[i]);
    results[i] = r;
    printf("%d, %lf                                                                                                                                     \n", r->generation, r->winning_score);
    free(args[i]);
  }
  free(args);
  return results;
}

Result* run_EA(EAArgs* args){
  Graph** population = args->initialisation(args->init_env_pointer);
  double* scores = args->evaluate(population, args->evaluation_env_pointer);
  int generation = 0;
  while(generation < args->generations && !args->termination(population, scores, args->termination_env_pointer)){
    population = args->select_repopulate(population, scores, args->select_repopulate_env_pointer);
    scores = args->evaluate(population, args->evaluation_env_pointer);
    if(args->update > 0 && generation % args->update == 0){
      int popsize = args->pop_size(population, args->pop_size_env_pointer);
      double bestScore = 999999999.9;
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
      printf("Generation %d: winner %d has score %lf out of %d individuals\r", generation, winner, bestScore, popsize);
    }
    generation = generation + 1;
  }
  Result* res = malloc(sizeof(Result));

  int popsize = args->pop_size(population, args->pop_size_env_pointer);
  double bestScore = 9999999999.9;
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
  res->winning_score = bestScore;
  res->generation = generation;
  res->terminated = generation == args->generations;
  if(args->update > 0){
    printf("Generation %d TERMINATED with score %lf\r", generation, res->winning_score);
  }
  free_graph_array(population, args->pop_size(population, args->pop_size_env_pointer));
  free(scores);
  return res;
}
