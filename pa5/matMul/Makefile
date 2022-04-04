OUTPUT=matMul
CFLAGS=-Wall -Werror -m64
# -fsanitize=address

%: %.c %.h
	gcc $(CFLAGS) -O3 -o $@ $<

%: %.c
	gcc $(CFLAGS) -O3 -o $@ $<

all: $(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)
