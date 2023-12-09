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

let is_start_node (node : string) : bool =
  Char.O.(node.[2] = 'A')

let is_end_node (node : string) : bool =
  Char.O.(node.[2] = 'Z')

let rec gcd a b =
  if b = 0 then a
  else gcd b (a mod b)

let lcm a b =
  if a = 0 || b = 0 then 0
  else (a * b) / (gcd a b)

let lcm_of_list numbers =
  match numbers with
  | [] -> 0 (* LCM is not defined for an empty list *)
  | x :: xs -> List.fold_left xs ~init:x ~f:lcm

let part2 (instructions : instructions_t) : int =
  let rec walk (current : string) (turns_left : turn_t list) (prev_steps : int) : int =
    let turns = match turns_left with
      | [] -> instructions.turns
      | x -> x
    in
    if is_end_node current then prev_steps
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
  let start_nodes = Hashtbl.keys instructions.network |> List.filter ~f:is_start_node in
  let cycles = List.map start_nodes ~f:(fun node ->
    walk node instructions.turns 0
  ) in
  List.iter cycles ~f:(fun x -> printf "%d\n" x);
  lcm_of_list cycles


let () =
  let lines = read_input "bin/d08/input.txt" in
  let instructions = parse_input lines in
  begin
    (* printf "Part 1: %d\n" (part1 instructions); *)
    let _ = part1 in
    printf "Part 2: %d\n" (part2 instructions);
  end
