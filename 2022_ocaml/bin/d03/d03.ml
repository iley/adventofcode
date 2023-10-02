open Core

let read_input filename =
  In_channel.read_lines filename

let split_halves input =
  List.map input ~f:(fun line ->
    let len = String.length line in
    let half_len = len / 2 in
    let first_half = String.sub line ~pos:0 ~len:half_len in
    let second_half = String.sub line ~pos:half_len ~len:half_len in
    (first_half, second_half)
  )

let character_set str =
  String.to_list str |> Char.Set.of_list

let string_intersection a b =
  let set_a = character_set a in
  let set_b = character_set b in
  let intersection = Set.inter set_a set_b in
  let inter_list = Set.to_list intersection in
  String.of_char_list inter_list

let offending_item first_half second_half =
  let inter = string_intersection first_half second_half in
  inter.[0]  (* there is always exactly one character *)

let calculate_item_score item =
  let code_a = Char.to_int 'a' in
  let code_z = Char.to_int 'z' in
  let code_A = Char.to_int 'A' in
  let item_code = Char.to_int item in
  if code_a <= item_code && item_code <= code_z then
    item_code - code_a + 1
  else
    item_code - code_A + 27

let part1 input =
  let offending_items = List.map input ~f:(
    fun (first_half, second_half) -> offending_item first_half second_half)
  in
  let item_scores = List.map offending_items ~f:calculate_item_score in
  let score_sum = List.fold item_scores ~init:0 ~f:(+) in
  Printf.printf "Part 1: %d\n" score_sum

let rec split_into_groups lst =
  match lst with
  | a :: b :: c :: rest -> (a, b, c) :: split_into_groups rest
  | _ -> []

let calculate_group_badge (a, b, c) =
  let inter = string_intersection a (string_intersection b c) in
  inter.[0]

let part2 input =
  let groups = split_into_groups input in
  let badges = List.map groups ~f:calculate_group_badge in
  let scores = List.map badges ~f:calculate_item_score in
  let score_sum = List.fold scores ~init:0 ~f:(+) in
  Printf.printf "Part 2: %d\n" score_sum

let () =
  let input = read_input "bin/d03/input.txt" in
  let halves = split_halves input in
  begin
    part1 halves;
    part2 input;
  end
