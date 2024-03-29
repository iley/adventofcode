(ns clj-01.core (:gen-class))
(require '[clojure.java.io :as io])

(defn parse-input [lines]
  (map
    (fn [lst]
      (map (fn [s] (Integer/parseInt s)) lst))
    (filter 
      (fn [lst] (not= lst '("")))
      (partition-by (fn [ln] (= ln "")) lines))))

(defn -main []
  (with-open [rdr (io/reader "input.txt")]
    (let [lines (line-seq rdr)
          groups (parse-input lines)
          sums (map (fn [grp] (reduce + grp)) groups)]
      (println (reduce max sums))
      (println (reduce + (take 3 (reverse (sort (vec sums)))))))))
