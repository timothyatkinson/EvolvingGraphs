#include "generic_operators.h"

//Loads a dataset for Genetic Programming.
GP_Dataset* load_data_set(char* file, int inputs, int rand_inputs, double rand_min, double rand_max, int outputs, int rows){
  GP_Dataset* dataset = malloc(sizeof(GP_Dataset));
  dataset->inputs = inputs + rand_inputs;
  dataset->outputs = outputs;
  dataset->rows = rows;
  dataset->data = malloc((rows * (inputs + rand_inputs + outputs)) * sizeof(double));
  for(int i = 0; i < rows; i++){
    dataset->data[i] = malloc((inputs + rand_inputs + outputs) * sizeof(double));
    for(int j = 0; j < inputs + outputs; j++){
      dataset->data[i][j] = -1.0;
    }
  }
  FILE* fp = fopen(file, "r");
  if(fp == NULL){
      printf("Error: file %s cannot be found.\n", file);
      exit(0);
  }

  for(int j = 0; j < rand_inputs; j++){
    double r = (((double)rand() / (double)RAND_MAX) * (rand_max - rand_min)) + rand_min;
    for (int i = 0; i < rows; i++){
      dataset->data[i][j] = r;
    }
  }
  for (int i = 0; i < rows; i++){
    for(int j = 0; j < (inputs + outputs); j++){
      int r = fscanf(fp," %lf %*c",&dataset->data[i][j + rand_inputs]);
      if(r != 1){
        printf("Error: file %s does not match the given row and columns dimensions.\n", file);
        exit(0);
      }
    }
  }
	printf("Rows: %d\n", rows);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < inputs + rand_inputs +  outputs; j++){
      printf("%lf, ", dataset->data[i][j]);
    }
    printf("\n");
  }
  return dataset;
}

//Evaluates a Genetic Programming individual.
double gp_evaluate(Graph* host_graph, GP_Dataset* dataset, Function_Set* fset){
  getNode(host_graph, 0);
	mark_active_blue(host_graph);

  int rows = dataset->rows;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int width = host_graph->nodes.size;
  double values[rows][width];
  int ready[width];
  double totalError = 0.0;
  //Find inputs and outputs
  int inputIndex[inputs];
  for(int i = 0; i<inputs; i++){
    inputIndex[i] = -1;
  }
  int outputIndex[outputs];
  for(int j = 0; j<outputs; j++){
    outputIndex[j] = -1;
  }

  for(int host_index = 0; host_index < host_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(host_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;

     HostLabel label = host_node->label;
     if(label.length != 2) break;

     HostListItem *item = label.list->first;
     HostListItem *item2 = item->next;
     if(item->atom.type != 'i') break;
     if(item2->atom.type != 's') break;
     if(strcmp(item2->atom.str, "IN") == 0){
       inputIndex[item->atom.num] = host_index;
     }
     if(strcmp(item2->atom.str, "OUT") == 0){
       outputIndex[item->atom.num] = host_index;
     }
  }

  int queue[host_graph->nodes.size];
  int head = 0;
  int tail = 0;

	for(int x = 0; x < width; x++){
      ready[x] = 0;
	}
  for(int r = 0; r < rows; r++){
    for(int x = 0; x < width; x++){
      values[r][x] = -1.0;
    }
	}
  for(int q = 0; q < width; q++){
    queue[q] = 0;
  }

  //Load inputs
  for(int i = 0; i < inputs; i++){
		for(int r = 0; r < rows; r++){
    	values[r][inputIndex[i]] = (dataset->data)[r][i];
		}
    ready[inputIndex[i]] = 1;
    Node *host_node = getNode(host_graph, inputIndex[i]);
    int counter;
    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
       if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
  }



  while(head < tail){
    int node_index = queue[head];
    head++;
    Node *host_node = getNode(host_graph, node_index);

    HostLabel label = host_node->label;
    HostListItem *item = label.list->last;
    char* function = item->atom.str;

    double in_values[rows][host_node->outdegree];
    int counter;
    for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthOutEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int target = host_edge->target;

			HostLabel label = host_edge->label;
			int vIndex = label.list->first->atom.num;
			for(int r = 0; r < rows; r++){
      	in_values[r][vIndex] = values[r][target];
			}
    }

    if(strcmp(function, "OUT") == 0){
	 	   //printf("OUT function\n");
  		 for(int r = 0; r < rows; r++){
          values[r][node_index] = in_values[r][0];
		// 		//printf("%d: %lf\n", node_index, values[r][node_index]);
	 	   }
     }
     else{
       Function* f = get_function(fset, function);
  		 for(int r = 0; r < rows; r++){
         values[r][node_index] = f->func(in_values[r]);
       }
     }

    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
      if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
  }

  for(int o = 0; o < outputs; o++){
		for(int r = 0; r < rows; r++){
			//printf("Expected %lf got %lf diff %lf\n", data[r][inputs + o], values[r][outputIndex[o]], fabs(values[r][outputIndex[o]] - data[r][inputs + o]));
    	totalError = totalError + fabs(values[r][outputIndex[o]] - dataset->data[r][inputs + o]);
		}
  }
	unmark_graph(host_graph);
  return totalError;
}
