Armok
=====

A C implementation of [Armok](https://github.com/Frib/Armok).


The World
---------

Armok simulates a cave, with any number of dwarves in it.

```
0123456789...
≈...▓▓▓▓▓▓▓▓▓
````

* `≈` is lava.
* `.` is empty space.
* `▓` is rock.


Instruction Set
---------------

```
+ Create a new dwarf
- Create a work order

> Move right
< Move left
m Mine
d Dump
w Work
```

Fun
---

* If a dwarf enters lava, they die.
* If a dwarf has no instructions they are striken by melancholy, and die.
* If a dwarf walks into rock, they die.
* If a dwarf fails to construct a workshop they go stark raving mad, and die.
* If a dwarf wants input from a trader, but they have none, they are murdered
  by backstabbing elves.

The program terminates once all dwarves are dead.
