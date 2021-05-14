TITLE=pam_pwlog

LIBSRC = $(TITLE).c
LIBOBJ = $(TITLE).o
LDLIBS = -lpam -lpam_misc
LIBSHARED = $(TITLE).so

all: $(LIBSHARED)

$(LIBSHARED): $(LIBOBJ)
		ld --shared -o $@ $(LIBOBJ) $(LDLIBS)

clean:
	rm -f $(LIBOBJ) $(LIBSHARED) core *~

extraclean: clean
	rm -f *.o *.so

.c.o:
	$(CC) $(CFLAGS) -Wall -c $< -o $@
