INCDIR=../PGP2/include
LIBDIR=../PGP2/lib
GP2_OBJECTS =
OBJECTS := *c ../common_functions.c ../evolutionary_algorithm.c ../generic_operators.c ../utils.c
CC=gcc

CFLAGS = -I$(INCDIR) -L $(LIBDIR) -O2 -lpgp2 -lm -g

default:	$(OBJECTS)
		$(foreach var,$(GP2_OBJECTS),rm -r $(var);	mkdir $(var);	../PGP2/pgp2 -l ../PGP2 -m $(var) -o $(var) $(var).gp2; )
		$(CC) $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(var)/*.c) $(CFLAGS) -o graphception

clean:
		rm graphception
		$(foreach var,$(GP2_OBJECTS),-rm -r $(var))
