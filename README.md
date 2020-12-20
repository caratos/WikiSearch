# WikiSearch

This project searches words in wikipedia by using models extracted from a minimization of automata. It searchs for the first appeareance of a specific term in **O(m)** time. The preprocessing works in linear time because of the minimization of automata algorithm.

The algorithm for minimization is the presented in  "Incremental Construction of Minimal Acyclic Finite-State Automata". Computational Linguistics Vol.26, Num. 1, 2000. and kazennikov's implementation is here: https://github.com/kzn/fsa

The project has three parts:
## 1. Preprocessing
- It contains some scripts to preprocess the data downloaded from https://es.wikipedia.org/wiki/Wikipedia:Descargas
- Also contains the results of preprocessing in the folder **Reports**
- The code is in python and c++.
  - Python was choose because of its facility to deal with extend ascii characters.
  - C++ was choose because of its speed to process documents.
- At the end of the preprocessing, only 1607931 files where choosen ( 12GB of data ).

## 2. stringlate 
- This is a java eclipse project extracted from the kazennikov's git repository.
- We did some modifications to the original code for the minimization of the wikipedia.

## 3. WikiSearch
- This is a C++ console program that helps the user to search data in wikipedia
- The necessary modeels that are available here: https://drive.google.com/drive/folders/1HofVwruV-r3choIf5xkKhbE0uPClZmwK?usp=sharing 

## Strategy of search
- We insert word by word to the fsa (finite state automate) minimization algorithm but also we put the file where we found that word, for example: **weather/0000001.txt** and that meant that **weather** was found in the file **0000001.txt** (the correct name of the file is in *list-of-names.txt* in the folder *Preprocessing*)
- We modified the kazennikov's code to avoid repeat entries in *O(m)* time where *m* is the lenght of the entry. For example for **weather/0000027.txt** it was discarded because *weather* was already in the fsa.
- At the end it generates an **.dot** file that can be seen in graphviz (only for short cases).
- With the help of WikiSearch we load the minimized fsa models and each search takes time *O(m)* which is super fast! But we have problems because of the memory. The unary (one word) model needs 3GB of available ram, the binary (two words) model needs 5GB of ram and the trinary (three words) needs 10GB of ram (estimated because we couldn't test it).

## Conclusions
- The minimization of fsa is a good choise for searching an specific term, if we solve the problem of ram memory, it could make any query instantly. 
- If we would like to find all the documents that contains a specific term, minimization of fsa is not a good choise, at least as it was proposed because it would need to append a vector of strings to each end state of the automata. We see some problems with this but a smart implementation could fixt it.
- Our search mechanism supports similar queries for example if we try to find "abb" it would suggest other words as "abba" or "abbi", etc. But it doesn't search for other terms as synonims or suffix, works only with prefix.

