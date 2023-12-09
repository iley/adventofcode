open Core

type turn_t = Left | Right

type instructions_t = {
  turns: turn_t list;
  network: (string, string * string) Hashtbl.t;
}

let read_input filename =
  In_channel.read_lines filename

let parse_turns line : turn_t list =
  String.to_list line |>
    List.map ~f:(function
      | 'L' -> Left
      | 'R' -> Right
      | x -> failwith ("invalid turn " ^ (String.of_char x))
    )

let parse_network lines : (string, string * string) Hashtbl.t =
  let network = Hashtbl.create (module String) in
  List.iter lines ~f:(fun line ->
    let src = String.sub line ~pos:0 ~len:3 in
    let left_turn = String.sub line ~pos:7 ~len:3 in
    let right_turn = String.sub line ~pos:12 ~len:3 in
    Hashtbl.add_exn network ~key:src ~data:(left_turn, right_turn)
  );
  network

let parse_input lines : instructions_t =
  let turns = parse_turns (List.hd_exn lines) in
  let network = parse_network (List.drop lines 2) in
  { turns; network }

let part1 (instructions : instructions_t) : int =
  let rec walk (current : string) (turns_left : turn_t list) (prev_steps : int) : int =
    let turns = match turns_left with
      | [] -> instructions.turns
      | x -> x
    in
    if String.equal current "ZZZ" then prev_steps
    else
      let left_turn, right_turn = Hashtbl.find_exn instructions.network current in
      let dir = List.hd_exn turns in
      let next = match dir with
        | Left -> left_turn
        | Right -> right_turn
      in
      begin
        walk next (List.tl_exn turns) (prev_steps + 1)
      end
  in
  walk "AAA" instructions.turns 0

let () =
  let lines = read_input "bin/d08/input.txt" in
  let instructions = parse_input lines in
  begin
    printf "Part 1: %d\n" (part1 instructions);
  end
