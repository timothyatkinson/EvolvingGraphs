INCDIR=../PGP2/include
LIBDIR=../PGP2/lib
GP2_OBJECTS = cgp_init cgp_node_mutate cgp_edge_mutate
OBJECTS := *c ../common_functions.c ../evolutionary_algorithm.c ../generic_operators.c ../utils.c
CC=gcc

CFLAGS = -I$(INCDIR) -L $(LIBDIR) -O2 -lgp2 -lm -g

default:	$(OBJECTS)
		$(foreach var,$(GP2_OBJECTS),-rm -r $(var);	mkdir $(var);	../PGP2/bin/gp2 -l ../PGP2 -m $(var) -o $(var) $(var).gp2; )
		$(CC) $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(var)/*.c) $(CFLAGS) -o cgp

clean:
		rm cgp
		$(foreach var,$(GP2_OBJECTS),-rm -r $(var))
