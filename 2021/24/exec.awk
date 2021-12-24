BEGIN { idx = 1 }
function eval(expr) { return expr ~ /^[a-z]$/ ? int(vars[expr]) : expr }
/inp/ { vars[$2] = substr(INPUT, idx, 1); idx++; print "---" }
/add/ { vars[$2] = eval($2) + eval($3) }
/mul/ { vars[$2] = eval($2) * eval($3) }
/div/ { vars[$2] = int(eval($2) / eval($3)) }
/mod/ { vars[$2] = eval($2) % eval($3) }
/eql/ { vars[$2] = eval($2) == eval($3) ? 1 : 0 }
{ printf("%-10s w=%-6s x=%-6s y=%-6s z=%-6s\n", $0, eval("w"), eval("x"), eval("y"), eval("z")) }
