open Core

type card_t = Ace | King | Queen | Jocker | Ten | Nine | Eight | Seven | Six | Five | Four | Three | Two

let card_to_str card =
  match card with
  | Ace -> "A"
  | King -> "K"
  | Queen -> "Q"
  | Jocker -> "J"
  | Ten -> "T"
  | Nine -> "9"
  | Eight -> "8"
  | Seven -> "7"
  | Six -> "6"
  | Five -> "5"
  | Four -> "4"
  | Three -> "3"
  | Two -> "2"

let card_rank card =
  match card with
  | Ace -> 12
  | King -> 11
  | Queen -> 10
  | Ten -> 9
  | Nine -> 8
  | Eight -> 7
  | Seven -> 6
  | Six -> 5
  | Five -> 4
  | Four -> 3
  | Three -> 2
  | Two -> 1
  | Jocker -> 0

type hand_t = {
  cards: card_t list;
  bid: int;
}

type hand_type_t = FinveOfAKind | FourOfAKind | FullHouse | ThreeOfAKind | TwoPair | OnePair | HighCard

let hand_to_str hand =
  let cards_str = List.map hand.cards ~f:card_to_str |> String.concat in
  sprintf "%s (%d)" cards_str hand.bid

let hand_type_to_str hand_type =
  match hand_type with
  | FinveOfAKind -> "Five of a kind"
  | FourOfAKind -> "Four of a kind"
  | FullHouse -> "Full house"
  | ThreeOfAKind -> "Three of a kind"
  | TwoPair -> "Two pair"
  | OnePair -> "One pair"
  | HighCard -> "High card"

let _ = hand_type_to_str

let get_card_counts hand =
  let counts = Array.create ~len:((card_rank Ace) + 1) 0 in
  begin
    List.iter hand.cards ~f:(fun card ->
      match card with
      | Jocker -> ()
      | _ ->
        let rank = card_rank card in
        counts.(rank) <- counts.(rank) + 1
    );
    counts
  end

let get_hand_type' hand =
  let card_counts = get_card_counts hand in
  let has_rank rank = Array.find card_counts ~f:(fun c -> c = rank) |> Option.is_some in
  let is_five_of_a_kind = has_rank 5 in
  let is_four_of_a_kind = has_rank 4 in
  let is_full_house = has_rank 3 && has_rank 2 in
  let is_three_of_a_kind = has_rank 3 in
  let is_two_pair = Array.count card_counts ~f:(fun c -> c = 2) = 2 in
  let is_one_pair = has_rank 2 in
  if is_five_of_a_kind then
    FinveOfAKind
  else if is_four_of_a_kind then
    FourOfAKind
  else if is_full_house then
    FullHouse
  else if is_three_of_a_kind then
    ThreeOfAKind
  else if is_two_pair then
    TwoPair
  else if is_one_pair then
    OnePair
  else
    HighCard

let hand_type_rank hand_type =
  match hand_type with
  | FinveOfAKind -> 7
  | FourOfAKind -> 6
  | FullHouse -> 5
  | ThreeOfAKind -> 4
  | TwoPair -> 3
  | OnePair -> 2
  | HighCard -> 1

let replace_jocker (hand : hand_t) (replacement : card_t) =
  let rec replace_jocker' cards =
    match cards with
    | [] -> []
    | Jocker::t -> replacement::t
    | h::t -> h::(replace_jocker' t)
  in
  { hand with cards = replace_jocker' hand.cards }

let get_hand_type hand =
  let jocker_replacements = [Ace; King; Queen; Ten; Nine; Eight; Seven; Six; Five; Four; Three; Two] in
  let rec get_possible_types hand =
    if List.find hand.cards ~f:(fun card -> match card with | Jocker -> true | _ -> false) |> Option.is_none then
      [get_hand_type' hand]
    else
      let possible_hands = List.map jocker_replacements ~f:(fun replacement ->
        let new_hand = replace_jocker hand replacement in
        get_possible_types new_hand
      ) in
      List.concat possible_hands
  in
  let possible_types = get_possible_types hand in
  List.max_elt possible_types ~compare:(fun t1 t2 -> (hand_type_rank t1) - (hand_type_rank t2)) |> Option.value_exn

let hand_rank hand =
  hand_type_rank (get_hand_type hand)

let rec compare_cards hand_a hand_b =
  match hand_a.cards, hand_b.cards with
  | [], [] -> 0
  | [], _ -> -1
  | _, [] -> 1
  | a::at, b::bt ->
    let a_rank = card_rank a in
    let b_rank = card_rank b in
    if a_rank > b_rank then
      1
    else if a_rank < b_rank then
      -1
    else
      compare_cards { hand_a with cards = at } { hand_b with cards = bt }

let compare_hands hand_a hand_b =
  let hand_a_rank = hand_rank hand_a in
  let hand_b_rank = hand_rank hand_b in
  if hand_a_rank > hand_b_rank then
    1
  else if hand_a_rank < hand_b_rank then
    -1
  else
    compare_cards hand_a hand_b

let read_input filename =
  In_channel.read_lines filename

let parse_hand line : hand_t =
  let parts = String.split line ~on:' ' in
  let bid = List.nth_exn parts 1 |> Int.of_string in
  let cards = List.hd_exn parts |> String.to_list |> List.map ~f:(fun card ->
    match card with
    | 'A' -> Ace
    | 'K' -> King
    | 'Q' -> Queen
    | 'J' -> Jocker
    | 'T' -> Ten
    | '9' -> Nine
    | '8' -> Eight
    | '7' -> Seven
    | '6' -> Six
    | '5' -> Five
    | '4' -> Four
    | '3' -> Three
    | '2' -> Two
    | _ -> failwith "Invalid card"
  ) in
  { cards; bid }

let part2 hands =
  let sorted_hands = List.sort hands ~compare:compare_hands in
  let () = List.iter sorted_hands ~f:(fun hand -> printf "%s : %s\n" (hand_to_str hand) (hand_type_to_str (get_hand_type hand))) in
  let hand_winds = List.mapi sorted_hands ~f:(fun i hand -> (i + 1) * hand.bid) in
  List.fold hand_winds ~init:0 ~f:(+)

let () =
  let lines = read_input "bin/d07/input.txt" in
  let hands = List.map lines ~f:parse_hand in
  begin
    printf "Part 2: %d\n" (part2 hands);
  end;

(* part 1 below *)

(*


type card_t = Ace | King | Queen | Jack | Ten | Nine | Eight | Seven | Six | Five | Four | Three | Two

let card_to_str card =
  match card with
  | Ace -> "A"
  | King -> "K"
  | Queen -> "Q"
  | Jack -> "J"
  | Ten -> "T"
  | Nine -> "9"
  | Eight -> "8"
  | Seven -> "7"
  | Six -> "6"
  | Five -> "5"
  | Four -> "4"
  | Three -> "3"
  | Two -> "2"

let card_rank card =
  match card with
  | Ace -> 13
  | King -> 12
  | Queen -> 11
  | Jack -> 10
  | Ten -> 9
  | Nine -> 8
  | Eight -> 7
  | Seven -> 6
  | Six -> 5
  | Five -> 4
  | Four -> 3
  | Three -> 2
  | Two -> 1

type hand_t = {
  cards: card_t list;
  bid: int;
}

type hand_type_t = FinveOfAKind | FourOfAKind | FullHouse | ThreeOfAKind | TwoPair | OnePair | HighCard

let hand_to_str hand =
  let cards_str = List.map hand.cards ~f:card_to_str |> String.concat in
  sprintf "%s (%d)" cards_str hand.bid

let hand_type_to_str hand_type =
  match hand_type with
  | FinveOfAKind -> "Five of a kind"
  | FourOfAKind -> "Four of a kind"
  | FullHouse -> "Full house"
  | ThreeOfAKind -> "Three of a kind"
  | TwoPair -> "Two pair"
  | OnePair -> "One pair"
  | HighCard -> "High card"

let _ = hand_type_to_str

let get_card_counts hand =
  let counts = Array.create ~len:((card_rank Ace) + 1) 0 in
  let () = List.iter hand.cards ~f:(fun card ->
    let rank = card_rank card in
    counts.(rank) <- counts.(rank) + 1
  ) in
  counts

let get_hand_type hand =
  let card_counts = get_card_counts hand in
  let has_rank rank = Array.find card_counts ~f:(fun c -> c = rank) |> Option.is_some in
  let is_five_of_a_kind = has_rank 5 in
  let is_four_of_a_kind = has_rank 4 in
  let is_full_house = has_rank 3 && has_rank 2 in
  let is_three_of_a_kind = has_rank 3 in
  let is_two_pair = Array.count card_counts ~f:(fun c -> c = 2) = 2 in
  let is_one_pair = has_rank 2 in
  if is_five_of_a_kind then
    FinveOfAKind
  else if is_four_of_a_kind then
    FourOfAKind
  else if is_full_house then
    FullHouse
  else if is_three_of_a_kind then
    ThreeOfAKind
  else if is_two_pair then
    TwoPair
  else if is_one_pair then
    OnePair
  else
    HighCard

let hand_rank hand =
  let hand_type = get_hand_type hand in
  match hand_type with
  | FinveOfAKind -> 7
  | FourOfAKind -> 6
  | FullHouse -> 5
  | ThreeOfAKind -> 4
  | TwoPair -> 3
  | OnePair -> 2
  | HighCard -> 1

let rec compare_cards hand_a hand_b =
  match hand_a.cards, hand_b.cards with
  | [], [] -> 0
  | [], _ -> -1
  | _, [] -> 1
  | a::at, b::bt ->
    let a_rank = card_rank a in
    let b_rank = card_rank b in
    if a_rank > b_rank then
      1
    else if a_rank < b_rank then
      -1
    else
      compare_cards { hand_a with cards = at } { hand_b with cards = bt }

let compare_hands hand_a hand_b =
  let hand_a_rank = hand_rank hand_a in
  let hand_b_rank = hand_rank hand_b in
  if hand_a_rank > hand_b_rank then
    1
  else if hand_a_rank < hand_b_rank then
    -1
  else
    compare_cards hand_a hand_b

let read_input filename =
  In_channel.read_lines filename

let parse_hand line : hand_t =
  let parts = String.split line ~on:' ' in
  let bid = List.nth_exn parts 1 |> Int.of_string in
  let cards = List.hd_exn parts |> String.to_list |> List.map ~f:(fun card ->
    match card with
    | 'A' -> Ace
    | 'K' -> King
    | 'Q' -> Queen
    | 'J' -> Jack
    | 'T' -> Ten
    | '9' -> Nine
    | '8' -> Eight
    | '7' -> Seven
    | '6' -> Six
    | '5' -> Five
    | '4' -> Four
    | '3' -> Three
    | '2' -> Two
    | _ -> failwith "Invalid card"
  ) in
  { cards; bid }

let part1 hands =
  let sorted_hands = List.sort hands ~compare:compare_hands in
  let () = List.iter sorted_hands ~f:(fun hand -> printf "%s : %s\n" (hand_to_str hand) (hand_type_to_str (get_hand_type hand))) in
  let hand_winds = List.mapi sorted_hands ~f:(fun i hand -> (i + 1) * hand.bid) in
  List.fold hand_winds ~init:0 ~f:(+)

let () =
  let lines = read_input "bin/d07/input.txt" in
  let hands = List.map lines ~f:parse_hand in
  begin
    printf "Part 1: %d\n" (part1 hands);
  end;
*)
