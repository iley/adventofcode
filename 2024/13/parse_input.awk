BEGIN {
  print("typedef struct {");
  print("  int prize_x;");
  print("  int prize_y;");
  print("  int a_x;");
  print("  int a_y;");
  print("  int b_x;");
  print("  int b_y;");
  print("} machine_t;");
  print("");
  print("machine_t machines[] = {");
}

match($0, /Button A: X\+([0-9]+), Y\+([0-9]+)/, grp) {
  a_x = grp[1];
  a_y = grp[2];
}

match($0, /Button B: X\+([0-9]+), Y\+([0-9]+)/, grp) {
  b_x = grp[1];
  b_y = grp[2];
}


match($0, /Prize: X=([0-9]+), Y=([0-9]+)/, grp) {
  prize_x = grp[1];
  prize_y = grp[2];

  print("  { .prize_x =" prize_x ", .prize_y = " prize_y ", .a_x = " a_x ", .a_y = " a_y ", .b_x = " b_x ", .b_y = " b_y " },")
}

END {
  print("};");
}
