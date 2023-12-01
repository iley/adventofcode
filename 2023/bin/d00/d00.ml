open Core

let read_input filename =
  In_channel.read_lines filename

let () =
  let input = read_input "bin/d00/input.txt" in
  List.iter input ~f:(fun line ->
    Printf.printf "%s\n" line
  )
