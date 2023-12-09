open Core

let read_input filename =
  In_channel.read_lines filename

let parse_int_list line =
  let parts = String.split line ~on:' ' in
  List.filter_map parts ~f:(fun s ->
    match Or_error.try_with (fun () -> Int.of_string s) with
    | Ok i -> Some i
    | Error _ -> None
  )

let pow2 n =
  let rec pow2' n acc =
    if n = 0 then acc
    else pow2' (n - 1) (acc * 2)
  in
  pow2' n 1

let calculate_score n =
  if n = 0 then 0
  else pow2 (n - 1)

let parse_input lines =
  List.map lines ~f:(fun line ->
    let prefix_and_body = String.split line ~on:':' in
    let body = List.nth_exn prefix_and_body 1 in
    let parts = String.split body ~on:'|' in
    let winning_numbers = List.nth_exn parts 0 |> String.strip |> parse_int_list in
    let our_numbers = List.nth_exn parts 1 |> String.strip |> parse_int_list in
    (winning_numbers, our_numbers)
  )

let part1 cards =
  List.map cards ~f:(fun (winning, ours) ->
    let winning_set = Int.Set.of_list winning in
    let our_set = Int.Set.of_list ours in
    let intersection = Set.inter winning_set our_set in
    calculate_score (Set.length intersection)
  ) |> List.fold ~init:0 ~f:(+)

let part2 cards =
  let original_cards = List.mapi cards ~f:(fun i (winning, ours) ->
    (i, winning, ours)
  ) in
  let has_winning_cards = ref true in
  let cards = ref original_cards in
  let total_cards = ref (List.length original_cards) in
  begin
    while !has_winning_cards do
      let new_cards = ref [] in
      begin
        List.iter !cards ~f:(fun card ->
          let (current_card_number, winning, ours) = card in
          let winning_set = Int.Set.of_list winning in
          let our_set = Int.Set.of_list ours in
          let intersection = Set.inter winning_set our_set in
          let n = Set.length intersection in
          for i = current_card_number + 1 to (current_card_number + n) do
            let following_card = List.nth_exn original_cards i in
            new_cards := following_card :: !new_cards
          done
        );
        has_winning_cards := List.length !new_cards > 0;
        total_cards := !total_cards + List.length !new_cards;
        cards := !new_cards
      end
    done;
    !total_cards
  end

let () =
  let input = read_input "bin/d04/input.txt" in
  let cards = parse_input input in
  begin
    printf "Part 1: %d\n" (part1 cards);
    printf "Part 2: %d\n" (part2 cards)
  end
