open Base
open Core

let box_at_position (input_line : string) (n : int) =
  let index = 1 + 4 * n in
  if index > (String.length input_line - 1) || not (Char.is_alpha input_line.[index]) then
    None
  else
    Some input_line.[index]

let split_line_groups lst : string list list =
  let rec split_inner groups current_group lst =
    match lst with
    | [] -> List.rev ((List.rev current_group) :: groups)
    | "" :: tl -> split_inner ((List.rev current_group) :: groups) [] tl
    | hd :: tl -> split_inner groups (hd :: current_group) tl
  in
  split_inner [] [] lst

let parse_box_position_line line =
  let indices = List.init 9 ~f:Fn.id in
  List.map indices ~f:(fun i -> box_at_position line i)

let transpose_box_positions positions =
  let n_columns = List.length (List.hd_exn positions) in
  let n_rows = List.length positions in
  let array = Array.init n_columns ~f:(fun _ -> "") in
  begin
    for col = 0 to n_columns - 1 do
      for row = 0 to n_rows - 1 do
        let maybe_char = (List.nth_exn (List.nth_exn positions row) col) in
        match maybe_char with
        | None -> ()
        | Some char -> array.(col) <- array.(col) ^ (String.of_char char)
      done
    done;
    Array.to_list array
  end

let parse_box_positions lines =
  List.filter lines ~f:(fun str -> String.contains str '[')
    |> List.map ~f:parse_box_position_line
    |> transpose_box_positions

type move = {
  n_boxes: int;
  col_from: int;
  col_to: int;
}

let parse_moves lines =
  List.map lines ~f:(fun line ->
    let words = String.split line ~on:' ' in
    match words with
    | [_; n_boxes_str; _; col_from_str; _; col_to_str] ->
        let n_boxes = Int.of_string n_boxes_str in
        let col_from = Int.of_string col_from_str in
        let col_to = Int.of_string col_to_str in
        { n_boxes; col_from; col_to }
    | _ -> raise (Failure ("invalid move line " ^ line))
  )

let replace_nth n x lst =
  (List.take lst n) @ [x] @ (List.drop lst (n + 1))

let read_input filename =
  let lines = In_channel.read_lines filename in
  let line_groups = split_line_groups lines in
  match line_groups with
  | [first_block; second_block] ->
      (parse_box_positions first_block, parse_moves second_block)
  | _ -> raise (Failure "invalid input")

let rec execute_script positions moves =
  match moves with
  | [] -> positions
  | {n_boxes; col_from; col_to} :: moves_tail ->
      let col_from = col_from - 1 in  (* indices below are 0-based *)
      let col_to = col_to - 1 in
      let col_from_old_value = List.nth_exn positions col_from in
      let col_to_old_value = List.nth_exn positions col_to in
      let boxes_to_move = String.sub col_from_old_value ~pos:0 ~len:n_boxes in
      let col_to_new_value = (String.rev boxes_to_move) ^ col_to_old_value in
      let col_from_new_value = (String.drop_prefix col_from_old_value n_boxes) in
      let new_positions =
          replace_nth col_from col_from_new_value positions
          |> replace_nth col_to col_to_new_value
      in
      execute_script new_positions moves_tail

let () =
  let (box_positions, moves) = read_input "bin/d05/input.txt" in
  let final_positions = execute_script box_positions moves in
  begin
    List.iter final_positions ~f:(fun pos -> Printf.printf "%s\n" pos);
    let top_boxes = List.map final_positions ~f:(fun pos -> pos.[0]) in
    let part1_answer = String.of_list top_boxes in
    Printf.printf "Part 1: %s\n" part1_answer
  end
