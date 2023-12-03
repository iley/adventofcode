open Core

let matrix_width = 140
let matrix_height = 140

type number_t = {
  value: int;
  coordinates: (int * int) list;
}

let is_symbol = function
  | '0' .. '9' -> false
  | '.' -> false
  | _ -> true

let is_digit = function
  | '0' .. '9' -> true
  | _ -> false

let is_gear = function
  | '*' -> true
  | _ -> false

let read_input filename =
  In_channel.read_lines filename

let make_matrix lines =
  let matrix = Array.make_matrix ~dimx:matrix_width ~dimy:matrix_height ' ' in
  begin
    List.iteri lines ~f:(fun y line ->
      String.iteri line ~f:(fun x c ->
        matrix.(x).(y) <- c
      )
    );
    matrix
  end

let digits_to_int digits =
  let rec aux digits acc =
    match digits with
    | [] -> acc
    | (d, _, _) :: digits -> aux digits (acc * 10 + Char.to_int d - Char.to_int '0')
  in
  aux (List.rev digits) 0

let find_numbers matrix =
  let numbers = ref [] in
  for x = 0 to matrix_width - 1 do
    for y = 0 to matrix_height - 1 do
      if is_digit matrix.(x).(y) && (x = 0 || not (is_digit matrix.(x-1).(y))) then
        let cooridnates = ref [] in
        let digits = ref [] in
        let x' = ref x in
        while !x' < matrix_width && is_digit matrix.(!x').(y) do
          digits := (matrix.(!x').(y), !x', y) :: !digits;
          cooridnates := (!x', y) :: !cooridnates;
          incr x'
        done;
        numbers := { value = digits_to_int !digits; coordinates = !cooridnates } :: !numbers
    done
  done;
  !numbers

let has_adjacent_symbol matrix x y =
  let dx = [-1; 0; 1] in
  let dy = [-1; 0; 1] in
  let adjacent = List.cartesian_product dx dy in
  List.exists adjacent ~f:(fun (dx, dy) ->
    let x' = x + dx in
    let y' = y + dy in
    if dx = 0 && dy = 0 then false
    else if x' < 0 || x' >= matrix_width then false
    else if y' < 0 || y' >= matrix_height then false
    else is_symbol matrix.(x').(y')
  )

let adjacent_numbers numbers x y =
  List.filter numbers ~f:(fun number ->
    List.exists number.coordinates ~f:(fun (x', y') ->
      abs (x - x') <= 1 && abs (y - y') <= 1
    )
  )

let part1 input =
  let matrix = make_matrix input in
  let numbers = find_numbers matrix in
  let filtered_numbers = 
    List.filter numbers ~f:(fun number ->
      List.exists number.coordinates ~f:(fun (x, y) ->
        has_adjacent_symbol matrix x y
      )
    )
  in
  List.map filtered_numbers ~f:(fun number -> number.value) |>
  List.fold ~init:0 ~f:(+)

let part2 input =
  let matrix = make_matrix input in
  let numbers = find_numbers matrix in
  let sum = ref 0 in
  begin
    for x = 0 to matrix_width - 1 do
      for y = 0 to matrix_height - 1 do
        if is_gear matrix.(x).(y) then
          let adjacent_numbers = adjacent_numbers numbers x y in
          if List.length adjacent_numbers = 2 then
            let gear_ratio = List.fold adjacent_numbers ~init:1 ~f:(fun acc number -> acc * number.value) in
            sum := !sum + gear_ratio
      done
    done;
    !sum
  end

let () =
  let input = read_input "bin/d03/input.txt" in
  begin
    printf "Part 1: %d\n" (part1 input);
    printf "Part 2: %d\n" (part2 input)
  end
