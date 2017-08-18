all: prim.out kruskal.out lcs.out

prim.out: prim.c
	gcc prim.c -o prim.out

kruskal.out: kruskal.c
	gcc kruskal.c -o kruskal.out

lcs.out: lcs.c
	gcc lcs.c -o lcs.out
  
clean:
	rm prim.out kruskal.out lcs.out
