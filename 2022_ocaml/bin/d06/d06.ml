open Core

let read_input filename =
  let lines = In_channel.read_lines filename in
  match lines with
  | [ line ] -> line
  | _ -> raise (Failure "one line expected")

let all_unique_characters (str: string) : bool =
  let n_unique_chars = String.to_list str |> Char.Set.of_list |> Set.length in
  String.length str = n_unique_chars


let rec marker_position (input : string) ~(len : int) : int =
  let first_n_chars = String.sub input ~pos:0 ~len:len in
  if all_unique_characters first_n_chars then
    len
  else
    1 + (marker_position (String.drop_prefix input 1) ~len:len)

let () =
  let input = read_input "bin/d06/input.txt" in
  let part1_answer = marker_position input ~len:4 in
  let part2_answer = marker_position input ~len:14 in
  begin
    Printf.printf "Part 1: %d\n" part1_answer;
    Printf.printf "Part 2: %d\n" part2_answer
  end
