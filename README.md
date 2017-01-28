# Abstract Voronoi Diagram
Implementation of abstract Voronoi diagram based on [this](http://www.sciencedirect.com/science/article/pii/0925772193900333?np=y) article.

## Description
This is my Implementation of finding Voronoi diagram for a given set of sites in abstract setting.
This repository consists of a library that implements said algorithm which is the main part of the project. There is also a small application for visualizing the algorithm and a few tests.

## Usage
To use this algorithm one must implement `BasicOperationProvider` Interface. Interface is defined as follows:
```C++
class BasicOperationProvider
{
public:
    virtual BasicOperationOutput basic_operation(int p,int r,int q,int t,int s) = 0;
    virtual int number_of_sites() = 0;
};

```
Sites are denoted by numbers from `0` to `n` with `0` being `infinity` (desctibed in Abstract Voronoi Diagrams section) site.
`basic_operation` method is described in the article (I recommend reading that section of the article).

`BasicOperationOutput` is an enum representing the return value of `basic_operation`.
```C++
enum BasicOperationOutput{
    intersection_empty,  // 1
    whole_edge,          // 2a
    segment_prq,         // 2b
    segment_qtp,         // 2c
    segment_interior,    // 2d
    two_components       // 3
};
```
`AbstractVoronoiDiagram` class is the main interface with the algorithm. In order to work it needs an instance of `BasicOperationProvider`. Important methods of `AbstractVoronoiDiagram` class are:
```C++
PlanarGraph& getDiagram();
void proces_next_site();
void process_all_sites();
```

`PlanarGraph` is a representation of Voronoi diagram in abstract setting. It is similar to GCLC structure with edges described with four sites and vertices described by 3 sites. Interpretation of edges and vertices is left to concrete application.

## Abstract Voronoi Diagrams
Abstract Voronoi Diagrams are a generalization of Voronoi diagrams where any set of sites separated by nice enough curves. For two sites `p` and `q` a curve separating them is denoted by `J(p,q)`. Region belonging to `p` is denoted `D(p,q)` and `q`s region is `D(q,p)`. Region that "belongs" to `p` is defined as intersection of all `D(p,q)` for all `q`s.

An important concept is introduced. `Infinity` site. It is a site that has the same `J` with all the sites, and `J(Infinity,q)` is a closed curve that contains all points of interest.

Important thing to note it that sites do not need to have geometric representation.

I recommend reading about abstract Voronoi diagrams in the [article](http://www.sciencedirect.com/science/article/pii/0925772193900333?np=y) to get more familiar with them.

## Algorithm
Algorithm is fully described in the [article](http://www.sciencedirect.com/science/article/pii/0925772193900333?np=y) but main ideas are as follow.

It is an incremental algorithm adding one site at the time. During the algorithm two structures are maintained. Diagram itself (`PlanarGraph` in my Implementation) and history graph (`HistoryGraph`).

Starting structures are always the same. Namely region not belonging to `infinity` divided by two sites.

`HistoryGraph` is a tree with nodes being edges of Voronoi diagram. It is used to find edges in current diagram that are affected by adding new site. Set of all foud edges is denoted E<sub>s</sub> in the article. Using E<sub>s</sub> new diagram and history graph are calculated.

Order of sites being added is important for time complexity. By taking sites at random expected runtime of the algorithm is `O(n*log(n))`.

## App

There is a simple application that serves as an example for how one can use this algorithm. It implements basic_operation for regular Voronoi diagrams in a plane and draws them on the screen. Sites are identifiable by the numbers in the position of a site.

Incremental nature of the algorithm can be observed by adding sites one by one and seeing Voronoi diagrams of certain subsets of sites.

Importing a diagram from a file is also possible. The format is just space separated numbers.

Example file:
```
180 200
140 200
160 50
170 150
```

## Notes
My implementation assumes general position of sites (all vertices are defined by exactly 3 sites). If sites are not in general position edges are not uniquely defined by four edges and structures called "descriptors" are defines. I did implement the descriptor structure but I did not use it during the algorithm.

Library is Qt independent, but does use some C++11 features.
