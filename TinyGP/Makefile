INCDIR=../PGP2/include
LIBDIR=../PGP2/lib
GP2_OBJECTS = tiny_gp_init tiny_gp_const_mutate tiny_gp_node_mutate tiny_gp_crossover
OBJECTS := *c ../common_functions.c ../evolutionary_algorithm.c ../generic_operators.c ../utils.c
CC=gcc

CFLAGS = -I$(INCDIR) -L $(LIBDIR) -O2 -lgp2 -lm -g

default:	$(OBJECTS)
		$(foreach var,$(GP2_OBJECTS),-rm -r $(var);	mkdir $(var);	../PGP2/bin/gp2 -l ../PGP2 -m $(var) -o $(var) $(var).gp2; )
		$(CC) $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(var)/*.c) $(CFLAGS) -o tiny_gp

clean:
		rm tiny_gp
		$(foreach var,$(GP2_OBJECTS),-rm -r $(var))
