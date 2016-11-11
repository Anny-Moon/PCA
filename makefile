CC := g++
OPT:= -O3
CFLAGS := -Wall -std=c++11
PROGRAM := pca

all:
	@echo "Generating executable file..." $(PROGRAM)
	@$(CC) $(OPT) $(CFLAGS) main.cpp -o $(PROGRAM) -I./PCA_lib/include  -L./PCA_lib/build  -lpca -lm

clean:
	rm $(PROGRAM)