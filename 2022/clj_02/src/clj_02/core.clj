(ns clj-02.core (:gen-class))
(require '[clojure.java.io :as io]
         '[clojure.string :as str])

(def shape-score {"X" 1, "Y" 2, "Z" 3})
(def winner-score
  {["A" "X"] 3, ["B" "Y"] 3, ["C" "Z"] 3,
   ["A" "Y"] 6, ["B" "Z"] 6, ["C" "X"] 6,
   ["A" "Z"] 0, ["B" "X"] 0, ["C" "Y"] 0})
(def part2-mapping
  {["A" "X"] "Z", ["B" "Y"] "Y", ["C" "Z"] "X",
   ["A" "Y"] "X", ["B" "Z"] "Z", ["C" "X"] "Y",
   ["A" "Z"] "Y", ["B" "X"] "X", ["C" "Y"] "Z"})

(defn part1 [input]
  (reduce + 0
          (map (fn [entry] (+ (get shape-score (get entry 1))
                              (get winner-score entry)))
               input)))

(defn part2 [input]
  (part1 (map (fn [entry] [(get entry 0) (get part2-mapping entry)]) input)))

(defn -main []
  (with-open [rdr (io/reader "input.txt")]
    (let [lines (line-seq rdr)
          input (filter (fn [s] (= (count s) 2))
                        (map (fn [line] (str/split line #" "))
                             lines))]
      (println (part1 input))
      (println (part2 input)))))
