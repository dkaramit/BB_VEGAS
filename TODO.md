Things to do for v2.0:

- Clean the code. There is a mix of C and C++ styles. Moving to C++ means basically to replace C-style arrays with std::vectors.
- Use std::vector to remove the template arguments. The overhead will be negligible in general.
- Allow for Grid as an input. You may have information on the integrand. This will be a good way to express it in VEGAS language. 
- Run 1D VEGAS recursively for multiple dimensions like [LAInt](https://github.com/dkaramit/LAInt/tree/master). This is just an experiment to see how much VEGAS improves or not.
- Replace the subdivision phase with a much more robust subdivision of the N-dimensional cube. This can slow down VEGAS, but it makes it unbeatable. The data structure is the same as in [ASAP/kd-tree](https://github.com/dkaramit/ASAP/blob/master/kd-tree/KD-tree-Points.ipynb), where I perform N-dimensional subdivision based on number of points in an area. It is in `python`, but the logic is the same.