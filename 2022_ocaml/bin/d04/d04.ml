open Core

let parse_range range_str =
  let strings = String.split range_str ~on:'-' in
  match strings with
  | [first_number; second_number] -> (Int.of_string first_number, Int.of_string second_number)
  | _ -> raise (Failure ("invalid range " ^ range_str))

let parse_input_line line =
  let ranges = String.split line ~on:',' in
  match ranges with
  | [first_range; second_range] -> (parse_range first_range, parse_range second_range)
  | _ -> raise (Failure ("invalid input line " ^ line))

let read_input filename =
  let lines = In_channel.read_lines filename in
  List.map lines ~f:parse_input_line

let range_contains (outer_start, outer_end) (inner_start, inner_end) =
  outer_start <= inner_start && inner_end <= outer_end

let count_ranges input criteria =
  List.count input ~f:(fun (range_a, range_b) ->
    criteria range_a range_b
  )

let one_of_ranges_contains_other range_a range_b =
  (range_contains range_a range_b) || (range_contains range_b range_a)

let ranges_overlap range_a range_b =
  if one_of_ranges_contains_other range_a range_b then
    true
  else
    match (range_a, range_b) with
    | ((s1, e1), (s2, e2)) -> s1 <= s2 && s2 <= e1 || s1 <= e2 && e2 <= e1

let part1 input =
  count_ranges input one_of_ranges_contains_other

let part2 input =
  count_ranges input ranges_overlap

let () =
  let input = read_input "bin/d04/input.txt" in
  let part1_answer = part1 input in
  let part2_answer = part2 input in
  begin
    Printf.printf "Part 1: %d\n" part1_answer;
    Printf.printf "Part 2: %d\n" part2_answer;
  end
