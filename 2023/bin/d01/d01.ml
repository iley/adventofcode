open Core

let read_input filename =
  In_channel.read_lines filename

let is_digit = function '0' .. '9' -> true | _ -> false

let calibration_value_of_string str =
  let digits = (String.to_list str |> List.filter ~f:is_digit) in
  Int.of_string (
    String.of_char_list [(List.hd_exn digits); (List.last_exn digits)]
  )

let replace_spelled_out_numbers str =
  String.substr_replace_all str ~pattern:"one" ~with_:"o1e" |>
  String.substr_replace_all ~pattern:"two" ~with_:"t2o" |>
  String.substr_replace_all ~pattern:"three" ~with_:"t3e" |>
  String.substr_replace_all ~pattern:"four" ~with_:"f4r" |>
  String.substr_replace_all ~pattern:"five" ~with_:"f5e" |>
  String.substr_replace_all ~pattern:"six" ~with_:"s6x" |>
  String.substr_replace_all ~pattern:"seven" ~with_:"s7n" |>
  String.substr_replace_all ~pattern:"eight" ~with_:"e8t" |>
  String.substr_replace_all ~pattern:"nine" ~with_:"n9e"


let part_1 input =
  let values = List.map input ~f:calibration_value_of_string in
  let sum = List.fold values ~init:0 ~f:(+) in
  sum

let part_2 input =
  let preprocessed_input = List.map input ~f:replace_spelled_out_numbers in
  let values = List.map preprocessed_input ~f:calibration_value_of_string in
  let sum = List.fold values ~init:0 ~f:(+) in
  sum

let () =
  let input = read_input "bin/d01/input.txt" in
  let p1 = part_1 input in
  let p2 = part_2 input in
  begin
    printf "Part 1: %d\n" p1;
    printf "Part 1: %d\n" p2
  end
