# Armok

> Programming is fun!<hr />

More formally this is a C implementation of [Armok](https://github.com/Frib/Armok).

## Table of Contents

* [The Language](#lang)
  * [The World](#lang-world)
  * [Instructions](#lang-inst)
    * [Create Dwarf](#lang-inst-dwarf)
    * [Create Work Order](#lang-inst-sub)
    * [Move Right](#lang-inst-right)
    * [Move Left](#lang-inst-left)
    * [Mine](#lang-inst-mine)
    * [Dump](#lang-inst-dump)
    * [Work](#lang-inst-work)
    * [Build](#lang-inst-build)
    * [Comment](#lang-inst-comment)
  * [Workshops](#lang-work)
    * [Trade Depo](#lang-work-trader)
    * [Manager's Office](#lang-work-manager)
    * [Appraiser](#lang-work-appraiser)
  * [Constructs](#lang-build)
    * [Stairs](#lang-build-stairs)
  * [Fun](#lang-fun)
  * [Character Encoding](#lang-encoding)
  * [Quick Reference](#lang-quick-ref)
* [Installing](#install)
* [Running](#running)
* [Example Programs](#examples)

## <a name="lang" />The Language

Armok has simple, powerful and, most of all, fun syntax.

Each dwarf performs its instructions at the same time as the other dwarves. Allowing a degree of panellisation.

When all dwarves are dead, the program terminates.

### <a name="lang-world" />The World

Armok simulates a cave, with any number of dwarves in it.

```
≈...▓▓▓
```

<!-- ` -->

* `≈` is lava.
* `.` is empty space.
* `▓` is rock. wall

The cave is 256 blocks long at current. All positions from 4 onwards are rock.

With the addition of stairs, there are also 256 layers of cave. Dwarves start in the middle of these layers (layer 128) to allow for better conditional support.


### <a name="lang-inst" />Instruction Set

There are 7 instructions in Armok, 6 to control dwarves. The other 2 handle the creation of dwarfs and work orders.

There is also support for comments in the style: `!! Fun Comment !!`

#### <a name="lang-inst-dwarf" /> `+` Create Dwarf

Creates a new dwarf.

The following instructions which are not a `+` or `-` are that dwarf's work orders.

A dwarf will continue to perform its work orders until it is dead.


#### <a name="lang-inst-sub" /> `-` Create Work Order (Subroutine)

Creates a new work order.

The following instructions which are not a `+` or `-` are the instructions for that work order.

Work orders may be issued to a dwarf through the [Manager's Office](#lang-work-managers)


#### <a name="lang-inst-right" /> `>` Move Right

The dwarf move right one position.

[Fun](#lang-fun) occurs if it moves into a rock wall.


#### <a name="lang-inst-left" /> `<` Move Left

The dwarf moves left one position.

[Fun](#lang-fun) occurs if it moves into lava.


#### <a name="lang-inst-mine" /> `m` Mine

The dwarf mines the tile to the right of it. If it is a rock wall then it is changed into free space with a pile of 64 rocks. The dwarf also picks up a single rock from the tile to the right, if there is enough.


#### <a name="lang-inst-dump" /> `d` Dump

If the dwarf has any, it will dump a rock onto the tile on its left.


#### <a name="lang-inst-work" /> `w` Work

The dwarf will construct a workshop or work at an existing one on the current tile.

See the [Workshop](#lang-work) page for more information.

[Fun](#lang-fun) occurs if the dwarf tries to construct a workshop with no rocks in its inventory.


#### <a name="lang-inst-build" /> `b` Build

The dwarf will build a construction at the current tile.

See the [Constructs](#lang-constructs) page for more information.


#### <a name="lang-inst-comment" /> `!!` Comment

Does nothing other than to help the poor soul writing armok understand after a few barrels of beer.

Comments are wrapped in `!!`. Example: `+ !! Create a new Dwarf !!`.

The contents of comments will, naturally, not be interpreted.


### <a name="lang-work" />Workshops

There are three workshops in armok:

1. [Trade Depo](#lang-work-trader)
2. [Manager's Office](#lang-work-manager)
3. [Appraiser](#lang-work-appraiser)

When building a new workshop the number of rocks a dwarf is carrying corresponds to the workshop built (e.g. a dwarf with one rock builds a Trade Depo).

#### <a name="lang-work-trader" />Trade Depo

A dwarf which works at a Trade Depo with one or more rocks will output the [character](#lang-encoding) corresponding to the number of rocks it is carrying to the standard output.

A dwarf which works at a Trade Depo with no rocks will receive a number of rocks equal to the next [character](#lang-encoding) from the program's input.

If there is no input left, [fun](#lang-fun) happens.


#### <a name="lang-work-manager" />Manager's Office

A dwarf which works at the Manager's Office will start performing a work order equal to the number of rocks dumped in the office.

**Note:** work orders and dwarves are both instruction sets, so the order in which they are defined in a program file dictates the number assigned to the instruction set, starting at 1.

If you create a dwarf, it will have subroutine number 1. If you then create another subroutine, it will have number 2. Another dwarf? number 3. And so on.

Working at a office with 0 rocks destroys the office.

It is [fun](#lang-fun) to try to call a work order which doesn't exist.


#### <a name="lang-work-appraiser" />Appraiser

Working at an appraiser will cause dwarves to compare the number of rocks they carry to the number of rocks on the floor. If they are carrying more then they will dump one to the left, otherwise nothing happens.


### <a name="lang-build" />Constructions

Constructions are tiles which automatically affect a dwarf passing over it (sometimes with a condition) and perform an action on that dwarf. For example a set of stairs will move a dwarf up or down a layer if the dwarf has more than the number of rocks dumped on it.

Constructions, as with workshops, are built depending on the number of rocks a dwarf is carrying.

1. [Stairs Up](#lang-build-stairs-up)
2. [Stairs Down](#lang-build-stairs-down)

#### <a name="#lang-build-stairs-up" /> Stairs Up

Stairs Up move a Dwarf up one layer if it is carrying more than the number of rocks dumped at the stair.


#### <a name="#lang-build-stairs-up" /> Stairs Down

Stairs Down move a Dwarf down one layer if it is carrying more than the number of rocks dumped at the stair.


### <a name="lang-encoding" />Character Encoding

Because using ASCII wouldn't be enough fun, the character set is based off of the Dwarf Fortress [character set](http://dwarffortresswiki.org/index.php/Character_table).


### <a name="lang-fun" />Fun

* If a dwarf enters lava, they die.
* If a dwarf has no instructions they are stricken by melancholy, and die.
* If a dwarf walks into rock, they die.
* If a dwarf fails to construct a workshop they go stark raving mad, and die.
* If a dwarf wants input from a trader, but they have none, they are murdered
  by backstabbing elves.
* If a dwarf tries to get a non-existent work order, they break the manager's mandate and are executed.


### <a name="lang-quick-ref" />Quick Reference

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
* [FUN](examples/FUN.df) - Having [fun](#lang-fun)
