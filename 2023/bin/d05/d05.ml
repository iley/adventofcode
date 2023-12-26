open Core

type range_t = {
  dst_start: int;
  src_start: int;
  len: int;
}

type mapping_t = range_t list

type almanach_t = {
  seeds: int list;
  mappings: mapping_t list;
}

let read_input filename =
  In_channel.read_lines filename

let parse_seeds line =
  let line = String.drop_prefix line 7 in
  String.split line ~on:' ' |> List.map ~f:Int.of_string

let parse_mappings lines =
  let mappings = ref [] in
  let current_mapping = ref [] in
  begin
    List.iter lines ~f:(fun line ->
      if String.contains line ':' then (
        if not (List.is_empty !current_mapping) then (
          mappings := List.rev !current_mapping :: !mappings;
          current_mapping := []
        )
      )
      else if not (String.is_empty line) then (
          let parts = String.split line ~on:' ' in
          let dst_start = Int.of_string (List.nth_exn parts 0) in
          let src_start = Int.of_string (List.nth_exn parts 1) in
          let len = Int.of_string (List.nth_exn parts 2) in
          current_mapping := { dst_start; src_start; len } :: !current_mapping
      )
    );
    if not (List.is_empty !current_mapping) then
      mappings := List.rev !current_mapping :: !mappings;
    List.rev !mappings
  end

let parse_input lines : almanach_t =
  let seeds_line = List.hd_exn lines in
  let mappings_lines = List.drop lines 2 in
  {
    seeds = parse_seeds seeds_line;
    mappings = parse_mappings mappings_lines;
  }

let translate (mapping : mapping_t) value =
  let result = ref value in
  let found = ref false in
  begin
    List.iter mapping ~f:(fun range ->
      if not !found && (!result >= range.src_start && !result < range.src_start + range.len) then (
        result := range.dst_start + (!result - range.src_start);
        found := true
      )
    );
    !result
  end

let translate_back (mapping : mapping_t) value =
  let result = ref value in
  let found = ref false in
  begin
    List.iter mapping ~f:(fun range ->
      if not !found && (value >= range.dst_start && value < range.dst_start + range.len) then (
        let translated = range.src_start + (value - range.dst_start) in
        if (translate mapping translated) = value then (
          result := translated;
          found := true
        )
      )
    );
    !result
  end

let part1 almanach =
  let locations = List.map almanach.seeds ~f:(fun seed ->
    let result = ref seed in
    begin
      List.iter almanach.mappings ~f:(fun mapping ->
        result := translate mapping !result;
      );
      !result;
    end
  ) in
  List.min_elt locations ~compare:Int.compare |> Option.value_exn

let _ = part1

type seed_range_t = {
  start: int;
  len: int;
}

let seed_range_to_str range =
  sprintf "%d-%d" range.start (range.start + range.len)

let make_seed_ranges seeds =
  let rec aux seeds ranges =
    match seeds with
    | [] -> ranges
    | x :: y :: xs -> aux xs ({ start = x; len = y } :: ranges)
    | _ :: [] -> failwith "Unexpected end of list"
  in
  aux seeds []

let is_valid_seed seed ranges =
  List.exists ranges ~f:(fun range ->
    seed >= range.start && seed <= range.start + range.len
  )

let seed_from_location almanach location =
  let result = ref location in
  begin
    printf "%d -> " !result;
    List.iter almanach.mappings ~f:(fun mapping ->
      result := translate_back mapping !result;
      printf "%d -> " !result;
    );
    printf "\n";
    !result
  end

let part2 almanach =
  let loc = ref 1 in
  let found = ref false in
  let seed_ranges = make_seed_ranges almanach.seeds in
  let () = printf "Seed ranges: %s\n" (List.map seed_ranges ~f:seed_range_to_str |> String.concat ~sep:", ") in
  begin
    while not !found do
      if !loc % 1000 = 0 then (
        printf "loc: %d\n" !loc;
        Out_channel.flush stdout;
      );
      let seed = seed_from_location almanach !loc in
      if is_valid_seed seed seed_ranges then (
        printf "%d -> %d\n" !loc seed;
        Out_channel.flush stdout;
        found := true
      ) else
        loc := !loc + 1
    done;
    !loc
  end

let () =
  let input = read_input "bin/d05/input.txt" in
  let almanach = parse_input input in
  begin
    printf "Part 2: %d\n" (part2 almanach);
  end
