# Getting started

This project makes use of [simple2d](https://github.com/simple2d/simple2d) library as a submodule.
Follow these steps to be able to build this project:

## On Windows

```bash
git clone https://github.com/AdlanSADOU/Sample_simple2d.git --recursive
```
 `--recursive` meaning it should clone this repository with it's submodules, and even the submodules of the submodules.

Now `cd` into deps/simple2d and run `nmake /f NMakefile all install`
It should build the `simple2d` lib and dll and will be located at /deps/simple2d/build

---

If you are running this as a worspace in `Visual Studio Code` you can simply press `F5` to build and run.