# Armok

> Programming is fun!<hr />

[![Build Status](https://travis-ci.org/SoftlySplinter/c-armok.png?branch=fort/v0.4)](https://travis-ci.org/SoftlySplinter/c-armok)

More formally this is a C implementation of [Armok](https://github.com/Frib/Armok).

## Table of Contents

* [The Language](#language)
  * [The World](#language-world)
  * [Instructions](#language-instructions)
    * [Create Dwarf](#language-instructions-dwarf)
    * [Create Work Order](#language-instructions-sub)
    * [Move Right](#language-instructions-right)
    * [Move Left](#language-instructions-left)
    * [Mine](#language-instructions-mine)
    * [Dump](#language-instructions-dump)
    * [Work](#language-instructions-work)
  * [Workshops](#language-workshops)
    * [Trade Depo](#language-workshops-trader)
    * [Manager's Office](#language-workshops-manager)
    * [Appraiser](#language-workshops-appraiser)
  * [Fun](#language-fun)
  * [Character Encoding](#language-encoding)
  * [Quick Reference](#language-quick-ref)
* [Installing](#install)
* [Running](#running)
* [Example Programs](#examples)

## <a name="language" />The Language

Armok has simple, powerul and, most of all, fun syntax.

Each dwarf performs its instructions at the same time as the other dwarves. Allowing a degree of parellisation.

When all dwarves are dead, the program terminates.

### <a name="language-world" />The World

Armok simulates a cave, with any number of dwarves in it.

`≈...▓▓▓`

* `≈` is lava.
* `.` is empty space.
* `▓` is rock. wall

The cave is 256 blocks long at current. All positions from 4 onwards are rock.


### <a name="language-instructions" />Instruction Set

There are 7 instructions in Armok, 5 to control dwarves. The other 2 handle the creation of dwarfs and work orders.

There is also support for comments in the style: `!! Fun Comment !!`

#### <a name="language-instructions-dwarf" /> `+` Create Dwarf

Creates a new dwarf.

The following instructions which are not a `+` or `-` are that dwarf's work orders.

A dwarf will continue to perform its work orders until it is dead.


#### <a name="language-instructions-sub" /> `-` Create Work Order (Subroutine)

Creates a new work order.

The following instructions which are not a `+` or `-` are the instructions for that work order.

Work orders may be issued to a dwarf through the [Manager's Office](#language-workshops-managers)


#### <a name="language-instructions-right" /> `>` Move Right

The dwarf move right one position.

[Fun](#language-fun) occurs if it moves into a rock wall.


#### <a name="language-instructions-left" /> `<` Move Left

The dwarf moves left one position.

[Fun](#language-fun) occurs if it moves into lava.


#### <a name="language-instructions-mine" /> `m` Mine

The dwarf mines the tile to the right of it. If it is a rock wall then it is changed into free space with a pile of 64 rocks. The dwarf also picks up a single rock from the tile to the right, if there is enough.


#### <a name="language-instructions-dump" /> `d` Dump

If the dwarf has any, it will dump a rock onto the tile on its left.


#### <a name="language-instructions-work" /> `w` Work

The dwarf will construct a workshop or work at an existing one on the current tile.

See the [Workshop](#language-workshops) page for more information.

[Fun](#language-fun) occurs if the dwarf tries to construct a workshop with no rocks in its inventory.

#### <a name="language-instructions-comment" /> `!!` Comment

Does nothing other than to help the poor soul writing armok understand after a few barrels of beer.

Comments are wrapped in `!!`. Example: `+ !! Create a new Dwarf !!`.

The contents of comments will, naturally, not be interpreted.


### <a name="language-workshops" />Workshops

There are three workshops in armok:

1. [Trade Depo](#language-workshops-trader)
2. [Manager's Office](#language-workshops-manager)
3. [Appraiser](#language-workshops-appraiser)

When building a new workshop the number of rocks a dwarf is carrying corresponds to the workshop built (e.g. a dwarf with one rock builds a Trade Depo).

#### <a name="language-workshops-trader" />Trade Depo

A dwarf which works at a Trade Depo with one or more rocks will output the [character](#language-encoding) correcsponding to the number of rocks it is carrying to the standard output.

A dwarf which works at a Trade Depo with no rocks will recieve a number of rocks equal to the next [character](#language-encoding) from the program's input.

If there is no input left, [fun](#language-fun) happens.


#### <a name="language-workshops-manager" />Manager's Office

A dwarf which works at the Manager's Office will start performing a work order equal to the number of rocks dumped in the office.

**Note:** work orders and dwarves are both instruction sets, so the order in which they are defined in a program file dictates the number assigned to the instruction set, starting at 1.

If you create a dwarf, it will have subroutine number 1. If you then create another subroutine, it will have number 2. Another dwarf? number 3. And so on.

Working at a office with 0 rocks destroys the office.

It is [fun](#language-fun) to try to call a work order which doesn't exist.


#### <a name="language-workshops-appraiser" />Appraiser

Working at an appraiser will cause dwarves to compair the number of rocks they carry to the number of rocks on the floor. If they are carrying more then they will dump one to the left, otherwise nothing happens.


### <a name="language-encoding" />Character Encoding

Becuase using ASCII wouldn't be enough fun, the character set is based off of the Dwarf Fortress [character set](http://dwarffortresswiki.org/index.php/Character_table).


### <a name="language-fun" />Fun

* If a dwarf enters lava, they die.
* If a dwarf has no instructions they are striken by melancholy, and die.
* If a dwarf walks into rock, they die.
* If a dwarf fails to construct a workshop they go stark raving mad, and die.
* If a dwarf wants input from a trader, but they have none, they are murdered
  by backstabbing elves.
* If a dwarf tries to get a non-existant work order, they break the manager's mandate and are executed.


### <a name="language-quick-ref" />Quick Reference

```
+ Create a dwarf
- Create a subroutine

> Move right
< Move left
m Mine
d Dump
w Work
```


## <a name="installation" />Installation

Armok is supplied with a standard C makefile.


## <a name="running" />Running

To run Armok simple call the binary with a filename of your program and any input (surrounded in quotes (`"`)).


## <a name="examples" />Example Programs

Because Armok is such fun, a few examples have been provided to help the uninitiated.

* [HELL](example/HELL.df) - Basic Hello World, or it would be if it wasn't so boring without the use of managers.
* [COPYCAT](example/COPY.df) - Echos the input, up to a point.
* [MANAGER](example/MANAGER.df) - Echos all input back.
* [HELLO](example/HELLO.df) - Proper Hello World.
* [FUN](examples/FUN.df) - Having [fun](#language-fun)
