INCDIR=../../PGP2/include
LIBDIR=../../PGP2/lib
GP2_OBJECTS = eggp_dc_init add_depth eggp_dc_edge eggp_dc_node remove_depth
OBJECTS := *c ../../common_functions.c ../../evolutionary_algorithm.c ../../generic_operators.c ../../utils.c
CC=gcc

CFLAGS = -I$(INCDIR) -L $(LIBDIR) -O2 -lgp2 -lm -g

default:	$(OBJECTS)
		rm -f -r pgp2;	mkdir pgp2;
		$(foreach var,$(GP2_OBJECTS),mkdir pgp2/$(var);	echo '$(var) compile'; ../../PGP2/bin/gp2 -l ../PGP2 -m $(var) -o pgp2/$(var) $(var).gp2; )
		$(CC) $(OBJECTS) $(foreach var,$(GP2_OBJECTS), pgp2/$(var)/*.c) $(CFLAGS) -o eggp_depth_control

clean:
		rm eggp_depth_control
		$(foreach var,$(GP2_OBJECTS),-rm -r $(var))
