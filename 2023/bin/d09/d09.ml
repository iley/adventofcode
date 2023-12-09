open Core

let read_input filename =
  In_channel.read_lines filename

let parse_input lines =
  List.map lines ~f:(fun line ->
    String.split line ~on:' ' |> List.map ~f:Int.of_string
  )

let all_zeroes numbers =
  List.for_all numbers ~f:(fun number -> number = 0)

let remove_last_element numbers =
  List.take numbers ((List.length numbers) - 1)

let diff numbers =
  List.map2_exn (remove_last_element numbers) (List.tl_exn numbers) ~f:(fun a b -> b - a)

let rec extrapolate numbers =
  if all_zeroes numbers then
    0
  else
    (List.last_exn numbers) + (extrapolate (diff numbers))

let rec extrapolate_back numbers =
  if all_zeroes numbers then
    0
  else
    (List.hd_exn numbers) - (extrapolate_back (diff numbers))

let part1 input =
  List.map input ~f:extrapolate |> List.fold ~init:0 ~f:(+)

let part2 input =
  List.map input ~f:extrapolate_back |> List.fold ~init:0 ~f:(+)

let () =
  let input = read_input "bin/d09/input.txt" in
  let parsed_input = parse_input input in
  begin
    printf "Part 1: %d\n" (part1 parsed_input);
    printf "Part 2: %d\n" (part2 parsed_input)
  end
