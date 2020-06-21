# BB_VEGAS
*Bare-Bones VEGAS* 

![](https://img.shields.io/badge/language-C++-black.svg)    ![](https://tokei.rs/b1/github/dkaramit/BB_VEGAS)

![](https://img.shields.io/github/repo-size/dkaramit/BB_VEGAS?color=blue)


A ```VEGAS``` Monte Carlo Integration project. As the name implies, it is just an implementation of the ```VEGAS``` algorithm introduced in [G. P. Lepage JOURNAL  OF COMPUTATIONAL A New Algorithm PHYSICS 27, 192-203 (1978)](https://www.sciencedirect.com/science/article/pii/0021999178900049?via%3Dihub).


The idea is similar to [*NaBBODES*](https://dkaramit.github.io/NaBBODES), *i.e.* have a simple implementation ready, and allow the user to easily hack and modify the code to meet their needs.

---
This project started in [*ASAP*](https://dkaramit.github.io/ASAP), which tries to make everything simple. Here we will be able to further develop ```VEGAS```. It would be useful to be able to  read the grid from a file, which would allow the user to define a custom  probability density function (pdf) and sample from it. This can be helpful since one can save the pdf from a previous evaluation of the integral.

---
## To-do :
- [X] Add subdivision phase.
- [ ] Read and write grid on file.
- [ ] Maybe better regularization of weights?

That's it for now.

Enjoy,

Dimitris