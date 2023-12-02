open Core

type round_t = {
  red: int;
  green: int;
  blue: int;
}

type game_t = round_t list

let read_input filename =
  In_channel.read_lines filename

let find_color (color_name : string) (tuples : (string * int) list) : int =
  match (List.find tuples ~f:(fun (color, _) -> String.equal color color_name)) with
  Some (_, count) -> count
  | None -> 0

let parse_input input : game_t list =
  List.map input ~f:(fun line ->
    let parts = String.split line ~on:':' in
    let game = String.strip (List.nth_exn parts 1) in
    let rounds = String.split game ~on:';' in
    List.map rounds ~f:(fun round_str ->
      let pulls = (String.split round_str ~on:',' |> List.map ~f:String.strip) in
      let tuples = 
        List.map pulls ~f:(fun pull ->
          let parts = String.split pull ~on:' ' in
          let count = List.nth_exn parts 0 |> Int.of_string in
          let color = List.nth_exn parts 1 in
          begin
            (color, count)
          end
        )
      in
      let red = find_color "red" tuples in
      let green = find_color "green" tuples in
      let blue = find_color "blue" tuples in
      { red; green; blue }
    )
  )

let is_game_possible (game : game_t) : bool =
  List.for_all game ~f:(fun round ->
    round.red <= 12 && round.green <= 13 && round.blue <= 14
  )

let enumerate_games lst =
  let indices = List.range 1 ((List.length lst) + 1) in
  List.zip_exn indices lst

let part1 (games : game_t list) : int =
  let possible_games =
    enumerate_games games |>
    List.filter ~f:(fun (_, game) -> is_game_possible game) |>
    List.map ~f:(fun (i, _) -> i)
  in
  List.fold possible_games ~init:0 ~f:(fun acc i -> acc + i)

let minimum_possible_colors (game : game_t) : (int * int * int) =
  let red = game |> List.map ~f:(fun round -> round.red) |> List.max_elt ~compare:Int.compare in
  let green = game |> List.map ~f:(fun round -> round.green) |> List.max_elt ~compare:Int.compare in
  let blue = game |> List.map ~f:(fun round -> round.blue) |> List.max_elt ~compare:Int.compare in
  match (red, green, blue) with
  | (Some r, Some g, Some b) -> (r, g, b)
  | _ -> raise (Failure "Impossible")

let part2 (games : game_t list) : int =
  List.map games ~f:minimum_possible_colors |>
  List.map ~f:(fun (r, g, b) -> r * g * b) |>
  List.fold ~init:0 ~f:(+)

let () =
  let input = read_input "bin/d02/input.txt" in
  let games = parse_input input in
  let p1 = part1 games in
  let p2 = part2 games in
  begin
    printf "Part 1: %d\n" p1;
    printf "Part 2: %d\n" p2
  end
