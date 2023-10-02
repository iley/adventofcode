open Core

let read_input filename =
  let lines = In_channel.read_lines filename in
  List.map lines ~f:(fun line ->
    let len = String.length line in
    let half_len = len / 2 in
    let first_half = String.sub line ~pos:0 ~len:half_len in
    let second_half = String.sub line ~pos:half_len ~len:half_len in
    (first_half, second_half)
  )

let character_set str =
  String.to_list str |> Char.Set.of_list

let offending_item first_half second_half =
  let first_set = character_set first_half in
  let second_set = character_set second_half in
  let intersection = Set.inter first_set second_set in
  let inter_list = Set.to_list intersection in
  match inter_list with
  | [x] -> x
  | _ -> raise (Failure "expected one item")


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

let () =
  let input = read_input "bin/d03/input.txt" in
  part1 input
