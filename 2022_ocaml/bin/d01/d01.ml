open Base
open Core

let split_line_groups lst : string list list =
  let rec split_inner groups current_group lst =
    match lst with
    | [] -> current_group :: groups
    | "" :: tl -> split_inner (current_group :: groups) [] tl
    | hd :: tl -> split_inner groups (hd :: current_group) tl
  in
  split_inner [] [] lst

let parse_elf_calories lst : int list list =
  let string_groups = split_line_groups lst in
  List.map string_groups ~f:(List.map ~f:int_of_string)

let read_input filename =
  let lines = In_channel.read_lines filename in
  parse_elf_calories lines

let () =
  let elf_calories = read_input "bin/d01/input.txt" in
  let per_elf_calorie_sums = List.map elf_calories ~f:(List.fold ~f:(+) ~init:0) in
  let calorie_max = (List.max_elt per_elf_calorie_sums ~compare:Int.compare |> Option.value_exn) in
  Printf.printf "Part 1: %d\n" calorie_max
