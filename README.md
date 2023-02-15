### Plancov ###

[Negami's conjecture](https://en.wikipedia.org/wiki/Planar_cover) states that if a 
finite graph has a finite planar cover, then the original graph itself embedds in the 
real projective plane (and therefore in fact has a degree 2 planar cover).  [This review 
article](https://www.fi.muni.cz/~hlineny/papers/plcover20-gc.pdf) gives an introduction
to the conjecture and an overview of some of the surrounding results.  

Just as [Kuratowski's theorem](https://en.wikipedia.org/wiki/Kuratowski%27s_theorem)
gives a characterization of planar graphs as graphs 
not containing two specific graphs as minors, there is a corresponding result of 
[Archdeacon](https://onlinelibrary.wiley.com/doi/10.1002/jgt.3190050305) gives a 
characterization of graphs that embed in the real projective plane in terms of a list 
of forbidden minors (in this case, there are 103 forbidden minors).  

With some trickery, Negami's conjecture can be reduced to checking that a single one of 
these forbidden minors (a specific graph with 7 vertices) has no planar covers.  When I
heard this, I decided to go out looking for some planar covers of this graph.

I also decided I wanted to write something nontrivial in C (this is my first time doing that
so you've been warned if the code reeks).  This is the resulting program.  

The program takes as input a graph and produces lots of random covers of the graph and checks
if they are planar (on my machine, this worked without issues for degree 5,000 or so covers).
I ran out of steam at the end and did not roll my own planarity test but rather used a bit of
C++ to use the [Boost library](https://www.boost.org/) for the implementation of the linear time
[Boyer-Myrvold planarity test](https://www.boost.org/doc/libs/1_44_0/libs/graph/doc/boyer_myrvold.html).

I did not find any counterexamples to Negami's conjecture -- maybe you will have better luck?

## setup ##

The program is  written in java and thus requires a java virtual machine to run. The program
can be compiled with the following command run from within the directory containing the java files

```
> javac . -d *.java
``` 


## usage ##



### further ideas ###
