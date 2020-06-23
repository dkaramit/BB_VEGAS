# BB_VEGAS
*Bare-Bones VEGAS* 

![](https://img.shields.io/badge/language-C++-black.svg)    ![](https://tokei.rs/b1/github/dkaramit/BB_VEGAS)

![](https://img.shields.io/github/repo-size/dkaramit/BB_VEGAS?color=blue)


A ```VEGAS``` Monte Carlo Integration project. As the name implies, it is just an implementation of the ```VEGAS``` algorithm introduced in [G. P. Lepage JOURNAL  OF COMPUTATIONAL A New Algorithm PHYSICS 27, 192-203 (1978)](https://www.sciencedirect.com/science/article/pii/0021999178900049?via%3Dihub), with an additional  initial (optional) phase where the bins with the maximum contribution are subdivided.


The idea is similar to [*NaBBODES*](https://dkaramit.github.io/NaBBODES), *i.e.*  a simple implementation where the user can easily hack and modify it to meet their needs.

---
This project started in [*ASAP*](https://dkaramit.github.io/ASAP), where everything is made simple. Here, however, we will be able to further develop ```VEGAS```, using a bit more involved code. 

---
## To-do :
- [X] Add subdivision phase.
- [ ] Read and write grid.
- [ ] Maybe better regularization of weights?

That's it for now.

Enjoy,

Dimitris
