#include "unit.h"
#include "syntax.h"
#include "../src/syntax.h"

void reset() {
  _syn_dwarf = 0;
  _syn_sub = 0;
  _syn_comment = 0;
}

void correct_tokens() {
  reset();
  assert(syntactically_correct(DWARF), "'+' is a valid token");
  assert(_syn_dwarf == 1, "'+' should have created 1 dwarf");
  assert(_syn_sub == 0, "'+' should have created 0 subs");

  reset();
  assert(syntactically_correct(SUB), "'-' is a valid token");
  assert(_syn_dwarf == 0, "'-' should have created 0 dwarves");
  assert(_syn_sub == 1, "'-' should have created 1 sub");
  
  reset();
  assert(syntactically_correct(COMMENT), "'!' is a valid token");
  assert(syntactically_correct(COMMENT), "'!' following a '!' is a valid token");
  assert(_syn_dwarf == 0, "'!!' should have created 0 dwarves");
  assert(_syn_sub == 0, "'!!' should have created 0 subs");
  assert(_syn_comment, "''!!' should have toggelled comment");

  reset();
  _syn_comment = 1;
  assert(syntactically_correct('t'), "'t' is a valid token in comment");
  assert(syntactically_correct(DWARF), "'+' is a valid token in comment");
  assert(_syn_dwarf == 0, "Comments should not create dwaves");
  assert(_syn_sub == 0, "Comments should not create subs");
  assert(_syn_comment, "Comment should not toggle due to 't' or '+'");

  assert(syntactically_correct('!'), "'!' is a valid token in comment");
  assert(_syn_comment, "Comment should not toggle after a single '!'");

  assert(syntactically_correct('a'), "'a' is a valid token in comment");
  assert(_syn_comment, "Comment should not toggle after '!a'");

  assert(syntactically_correct('!'), "'!' is a valid token in comment");
  assert(syntactically_correct('!'), "'!' is a valid token in comment");
  assert(!_syn_comment, "'!!' should toggle comment");

  reset();
  _syn_dwarf = 1;
  assert(syntactically_correct(MINE), "'m' is a valid token with a dwarf");
  assert(syntactically_correct(WORK), "'w' is a valid token with a dwarf");
  assert(syntactically_correct(DUMP), "'d' is a valid token with a dwarf");
  assert(syntactically_correct(LEFT), "'>' is a valid token with a dwarf");
  assert(syntactically_correct(RIGHT), "'<' is a valid token with a dwarf");

  reset();
  _syn_sub = 1;
  assert(syntactically_correct(MINE), "'m' is a valid token with a sub");
  assert(syntactically_correct(WORK), "'w' is a valid token with a sub");
  assert(syntactically_correct(DUMP), "'d' is a valid token with a sub");
  assert(syntactically_correct(LEFT), "'>' is a valid token with a sub");
  assert(syntactically_correct(RIGHT), "'<' is a valid token with a sub");
}

void incorrect_tokens() {
  reset();
  assert(!syntactically_correct(MINE), "'m' is a not valid token with no dwarf or sub");
  assert(!syntactically_correct(WORK), "'w' is a not valid token with no dwarf or sub");
  assert(!syntactically_correct(DUMP), "'d' is a not valid token with no dwarf or sub");
  assert(!syntactically_correct(LEFT), "'>' is a not valid token with no dwarf or sub");
  assert(!syntactically_correct(RIGHT), "'<' is a not valid token with no dwarf or sub");

  // Automare a-z
  for(int i = 'a'; i <= 'z'; i++) {
    char message[26] = "' ' is not a valid token.";
    switch(i) {
      case DWARF:
      case SUB:
      case MINE:
      case WORK:
      case DUMP:
      case LEFT:
      case RIGHT:
        break;
      default:
        message[1] = i;
        reset();
        assert(!syntactically_correct(i), message);
    }
  }    

  reset();
  syntactically_correct('!');
  assert(!syntactically_correct('a'), "'!a' is not syntactically correct");
}

void correct_syntax() {
  reset();

  assert(syntax_check("+"), "'+' is syntactically correct.");
  assert(_syn_dwarf == 1, "'+' should have created 1 dwarf.");
  assert(_syn_sub == 0, "'+' should have created 0 subs.");

  assert(syntax_check("+mmmm"), "'+mmmm' is syntactically correct.");
  assert(_syn_dwarf == 1, "'+mmmm' should have created 1 dwarf."); 
  assert(_syn_sub == 0, "'+mmmm' should have created 0 subs.");

  assert(syntax_check("-m+"), "'-m+' is syntactically correct.");
  assert(_syn_dwarf == 1, "'-m+' should have created 1 dwarf."); 
  assert(_syn_sub == 1, "'-m+' should have created 1 subs.");

  assert(syntax_check("+!!comment!!m"), "'+!!comment!!m' is syntactically correct.");
  assert(_syn_dwarf == 1, "'+!!comment!!m' should have created 1 dwarf."); 
  assert(_syn_sub == 0, "'+!!comment!!m' should have created 0 subs.");

  assert(syntax_check("++<+w+>>mmww"), "'++<+w+>>mmww' is syntactically correct.");
  assert(_syn_dwarf == 4, "'++<+w+>>mmww' should have created 4 dwarves."); 
  assert(_syn_sub == 0, "'++<+w+>>mmww' should have created 0 subs.");
}

void incorrect_syntax() {
  reset();

  assert(!syntax_check(""), "'' is not syntactically correct");
  assert(!syntax_check("m"), "'m' is not syntactically correct");
  assert(!syntax_check("-m"), "'-m' is not syntactically correct");
  assert(!syntax_check("+l"), "'+l' is not syntactically correct");
  assert(!syntax_check("!!comment!!"), "'!!comment!!' is not syntactically correct");
  assert(!syntax_check("!!+!!mmm"), "'!!+!!mmm' is not syntactically correct");
  assert(!syntax_check("m+"), "'m+' is not syntactically correct.");
}

int  syntax_tests() {
  correct_tokens();
  incorrect_tokens();

  correct_syntax();
  incorrect_syntax();

  return report("Syntax");
}

