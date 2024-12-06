const char *sample[] = {
    "....#.....", //
    ".........#", //
    "..........", //
    "..#.......", //
    ".......#..", //
    "..........", //
    ".#..^.....", //
    "........#.", //
    "#.........", //
    "......#...", //
};

const char *input[] = {
    ".......................#...................#....#..#......#..............."
    "..#.#..#........................#.#..............#.....#",
    "................#.#.......#..#.......#...................................."
    ".............................................#.##.......",
    "............#..............#......................#...#.....#...#........."
    ".##.........#.....#.....................................",
    "..#...#......................................#............................"
    "#..................#..........#..#......................",
    "....#........#.#....................#..........#.....#.............#..#..."
    ".........................#..................#......#....",
    "..........................................................#..............."
    ".#............................................#.........",
    "..#............................#.....#...........................#........"
    "...#........##...........................#..#...........",
    ".....................#...........................#.#..............#......."
    "...............................#.........#....#.....#...",
    ".#...#.#.................#....................#..........................."
    "....................................#.#..........#......",
    "....#....................................#................................"
    "...........#.....#..........#...........................",
    ".......................#..........#..............#......#....#.......#...."
    "....................................#.#.................",
    "......#...........................................................#...#..."
    ".........#.................#............................",
    ".......#.................#..#.....................#......................."
    "........................................................",
    "..............#....................#.#..........#........#......#........."
    ".......#.................#..........#...................",
    "#.#.......................................#.........................#....."
    "..............................#.........................",
    "...#......................................................................"
    "...................#................#..................#",
    "#.....#....#............................................................#."
    "........................#..................#.#..........",
    ".#.....#.#.......#.#..................#.#......................#.......#.."
    "...#..#..................##.....#.......#...#...........",
    "....#.........#.................................#..........#........#....."
    "..........#................#...................#....#...",
    ".................#...............#...#.................#.................."
    "...............................#........................",
    "....#...#...............................#................................."
    ".................#..........#................#.....#....",
    "...........#........#....#.......#...#..........#...............#.....#..."
    "..#.....#..........#....................................",
    "............#.........#.................#................#................"
    ".#.#..................................................#.",
    "............#......................................#......................"
    ".............................................#..........",
    "...........#....#........................................................."
    "............................#............#..........#...",
    "..........#........................................#.............#........"
    ".........#........................#..#.......#........#.",
    "......#.............................#.................##.................."
    "................#.....................#.................",
    ".#.................................#......................................"
    ".......#.................##.....#..............#......#.",
    ".........................#..............................#..........#......"
    ".....#....#................#......................#.....",
    ".......#...................#......##........................#.........#..."
    "........................................................",
    "......................................................................##.."
    ".........#................#.............................",
    "....#...................................##................................"
    "...............#........................................",
    "...##.....#..#........#.................#................................."
    ".............................#..........................",
    "........##......#....................#..............................#....."
    ".................#...................#..................",
    ".........................................................#................"
    ".......................................#.#..............",
    "..........#.............................#.........#...............#......."
    ".........#.#.........#..........................#.#.....",
    "....................#...................#..#.............................."
    ".........................#..........#...............#...",
    "...........................................................#.............."
    "..........#.........#........#..........................",
    ".......#..............#......#.................................#.........."
    ".........##...........................#.........#.......",
    "#...#....................................................................."
    "..........................................#.............",
    "................................#..#....#............#...........#........"
    "..........#.............................#...............",
    "....................#..............#.........#............................"
    ".....#.............#..##................................",
    "#...#....................................................................."
    ".............#.....#...........#........................",
    "........#...........#........#...#..................#.....#....#.........#"
    ".........................#...........................#..",
    ".............#...#........................................................"
    "...........#...........#................................",
    ".............#........................................#...#.............#."
    ".............................#..#.........#.............",
    "...#......................................................................"
    "...........#.............#..........................##..",
    "...#......................................................................"
    "........................................................",
    "................#.........#..................................#............"
    ".......#................................................",
    "...#................#...#.#.....................#...........#............."
    ".....................#........#....#......#.............",
    "..........................#.....................#..#......................"
    ".............##........................................#",
    "#........................#...............................................#"
    "........#..#..........#...........................#.....",
    ".#............#.#........................................................."
    ".....#...........#......................................",
    "......#..................................................................#"
    ".......#..............................#...#....#........",
    "........#........................#.........#.............#.....#.........."
    "........................................................",
    ".........................................................................."
    ".....#...........................................#......",
    "........................#..................................#.............."
    ".......................................#................",
    "............................................................#............."
    ".............#.................#.......................#",
    ".....................#..#.........................#..............#........"
    ".....................#........#..............##......#..",
    ".....................#.................................................#.."
    ".....#............#........................#.......#....",
    "......................#..................................................."
    "..#......#............................#.................",
    "................................................................#...#..##."
    ".#.....................................#...............#",
    "..............#..........................................................."
    "...................................#....................",
    "............................................#......#..........#..........."
    "....................................................#...",
    "....#.................................#..................................."
    "...............................#..........##..#.........",
    "............#.....#......................................................."
    ".........................#..........#.........#.........",
    ".....................#......................................#.........#..."
    ".................................................#....#.",
    ".........................#...............................#................"
    "...............#....................#...................",
    ".#.....................#.#.......................................#....#..."
    "........#.......................#.......................",
    ".....................................................#.#..#..............."
    ".......................................................#",
    "#..........#..........................#............................#......"
    ".......#..................#.............#...........#...",
    "........#................................................................."
    "........................................................",
    "..........#.............#.........................................#......."
    ".........................................#..............",
    "...........#................................#.................#..........."
    "................#.............................#.........",
    "..................#.........................................#.#..........."
    ".......#...#...........#.......#..#.....................",
    "........................................................#...#............."
    "..........................................#.............",
    ".........................................................................#"
    ".......#..#.....#.......................................",
    "............#............................................................."
    ".#.........#..............#.............#...............",
    "#...#..........................................#...........#.....#........"
    ".............................#...............#..........",
    "...........................#............#................................."
    "........................................................",
    "...#..........................................#..........................."
    "............................................#...........",
    "..............#......#.....#.....................#........................"
    "..#.....................................................",
    ".........................#....#...................#...#.......#..........."
    "...................#........................#...........",
    ".............................#............^.#............................."
    "...................#......#..#.#...........#............",
    ".........................................................................."
    "..........#...#.#...................................#...",
    ".......................#..............................##.................."
    "............................#...........................",
    "......................#..................................................."
    "#..........................................#............",
    "......#..................................................................."
    ".....#.....................................#............",
    ".......................#.............................#...................."
    "....#...........#...........#............#...........#..",
    "....#...............#..#......#....#..................#.............#....."
    "..#...............#.......................#.............",
    "............#...#..................#......................................"
    "........................................................",
    "....#.......#.................#..........................................."
    "............#..#......#.................................",
    ".........#......#..........#......................#.....................#."
    ".................#.#....................................",
    "...............##.......................................................#."
    "..#.............................#.......#...............",
    "........................................................##................"
    "...#...#............#......#............................",
    "...........#...#..............#..........................................."
    "..................#...................#............#....",
    "...............................................#.....#.....#.............."
    "........................................................",
    ".#....................#...#........#....................#.#.........#....."
    ".....#................................#................#",
    ".............#.....#..#....................................#.#...........#"
    ".................................................#..#.#.",
    "......#.....................................#............................."
    ".......................................#................",
    "............................................................##......#....."
    "................#.......#.....................#...#.....",
    ".#.......#......................#........................................."
    "........................................................",
    "................#....#......................#.........#..................."
    "#........#.......##.....#...............................",
    "..#....#....................#............................................."
    "...............#.#......#............#.....#.#....#.....",
    ".................................#........................................"
    ".........#.......#......................................",
    "..................#...........#....#.....................#......#........."
    "......#..................#....................##........",
    ".##...............................................#............#.........."
    ".................#......................................",
    ".............#...........#...........................#..#.......#...#....."
    ".....#......................#..........#................",
    ".......#...................................#.................#....#......."
    ".......................................................#",
    "........#....................................................#............"
    ".....#.....#.........#.#................................",
    "................#.................................#.....................#."
    "....#.....#............................##...............",
    "..............................................##.................#..##...."
    "....#...........#............#..........................",
    "....#......................................#.............................."
    ".................................................#......",
    "..#..............#.#................#..#..............#..................."
    "....................#.#.......#..............#......#..#",
    ".....#...................................................................."
    "..........................................#.......#.....",
    "..#.......#.#..........#.......#..................................#......."
    "...#.......#.................#...........#...........#..",
    "...............#.....#................#............#................#....."
    ".......#.....#.#........#...............................",
    "....#.....................#................#.............................."
    ".......#......................#.#.......#....#..........",
    "........#...............#...#............................................."
    "........#........#.........#.........#..................",
    "...#......#..........................#.....#..........................##.."
    ".....#....#.............................................",
    ".............#................................#..........................."
    ".#.....#.......#......#................................#",
    ".......................#............#..........................#.........."
    "........................................................",
    ".................................................#..............#...#....."
    "......................#.................................",
    "......#...................#..............................................."
    "...............................................#....#..#",
    "....................................#......#.....................#........"
    "......#.......#...................#.....................",
    "............#...................................#...........#........#...."
    "....#...........................................##......",
    "#...........#..........................#.................................."
    "..#.........#................................#..........",
    "......##..#..............................................................."
    "#...............................#.........#.............",
    ".......................#.....#.........................#...#.............."
    "...........#.....#..........#.#...#.....................",
    ".......................#..#.....#.....#..........................#........"
    ".#.....#....................#.....#....................#",
};
