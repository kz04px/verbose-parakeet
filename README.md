# __Verbose Parakeet__
Yet another chess engine of mine. Destined to replace the Swizzles repo one day. C++17.

---

## __Build__
```
git clone --recurse-submodules https://github.com/kz04px/verbose-parakeet
mkdir verbose-parakeet/build
cd verbose-parakeet/build
cmake ..
make swizzles
```

---

## __Tests__
Tests are available using Catch2
```
make swizzles-test
```

---

## __Players__
Multiple search types can be selected from:
```
Classic
Regular alphabeta search

Greedy
Tries to maximise material while also being aware of checkmates and draws

Random
Plays random moves
```

---

## __Credits__
- [Catch2](https://github.com/catchorg/Catch2) - A modern, C++-native, header-only, test framework for unit-tests, TDD and BDD - using C++11, C++14, C++17 and later (or C++03 on the Catch1.x branch)
