CC := g++
OPT:= -O3
CFLAGS := -Wall -std=c++11
PROGRAM := pca
#LIB:= -I/Users/annsi118/Documents/Git_projects/PCA_private/include -L/Users/annsi118/Documents/Git_projects/PCA_private/build

all:
	@echo "Generating executable file..." $(PROGRAM)
	@$(CC) $(OPT) $(CFLAGS) main.cpp -o $(PROGRAM) -lpca $(LIB) -lm
clean:
	rm $(PROGRAM)