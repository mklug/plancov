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

You will need to have the boost library set up on hyour machine to run this program.  With that,
on my machine, complilation works by running 

```
> c++ -std=c++11 -I ~/coding/c++/boost/boost_1_80_0 planar.cpp -o planar
``` 
You will need to adjust the path to the boost library on your machine.  

## usage ##

To run the program, use the command

```
> ./planar [path to graph] [number of trials] [max degree] [number of trials degree fixed]
``` 
you will pick `[number of trials]` many degrees at random, bounded above by `[max degree]`
and then investigate the planarity of `[number of trials degree fixed]` many covers of 
the graph with adjacency matrix in `[path to graph]` of that degree.

By Just entering 

```
> ./planar
``` 
you can hunt around for some somewhat low degree planar covers of the aforementioned 7 vertex graph.


### further ideas ###

This could likely all be sped up considerably by using a sparse graph implementation throughout.  
I also wanted to investigate the likelyhood that some higher-genus analog of Negami's 
conjecture might hold, however, testing even if a graph is toral is in practice tough.  
