open Core

type shape = Rock | Paper | Scissors

(*
let string_of_shape mv =
  match mv with
  | Rock -> "rock"
  | Paper -> "paper"
  | Scissors -> "scissors"
*)

let parse_input_lines lines =
  List.map lines ~f:(fun line ->
    let first_char = line.[0] in
    let second_char = line.[2] in  (* skip the whitespace *)
    let their_shape =
      match first_char with
      | 'A' -> Rock
      | 'B' -> Paper
      | 'C' -> Scissors
      | _ -> raise (Failure ("invalid input: " ^ line))
    in
    let our_shape =
      match second_char with
      | 'X' -> Rock
      | 'Y' -> Paper
      | 'Z' -> Scissors
      | _ -> raise (Failure ("invalid input " ^ line))
    in
    (their_shape, our_shape)
  )

let read_input filename =
  let lines = In_channel.read_lines filename in
  parse_input_lines lines

let calculate_shape_score shp =
  match shp with
  | Rock -> 1
  | Paper -> 2
  | Scissors -> 3

let calculate_win_score their_shape our_shape =
  match (their_shape, our_shape) with
  | (Rock, Rock) -> 3
  | (Rock, Paper) -> 6
  | (Rock, Scissors) -> 0
  | (Paper, Paper) -> 3
  | (Paper, Rock) -> 0
  | (Paper, Scissors) -> 6
  | (Scissors, Scissors) -> 3
  | (Scissors, Paper) -> 0
  | (Scissors, Rock) -> 6

let round_score (their_shape, our_shape) =
  let shape_score = calculate_shape_score our_shape in
  let win_score = calculate_win_score their_shape our_shape in
  shape_score + win_score

let calculate_score input =
  List.map input ~f:round_score |> List.fold ~init:0 ~f:(+)

let () =
  let input = read_input "bin/d02/input.txt" in
  let score = calculate_score input in
  Printf.printf "Part 1: %d\n" score
