BEGIN { prev = 999999 }
{ if ($1 > prev) count++; prev = $1 }
END { print count }
