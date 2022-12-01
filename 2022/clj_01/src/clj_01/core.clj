(ns clj-01.core (:gen-class))

(defn parse-input [lines]
  (map
    (fn [lst]
      (map (fn [s] (Integer/parseInt s)) lst))
    (filter 
      (fn [lst] (not= lst '("")))
      (partition-by (fn [ln] (= ln "")) lines))))

(defn -main []
  (with-open [rdr (clojure.java.io/reader "input.txt")]
    (let [lines (line-seq rdr)
          groups (parse-input lines)
          sums (map (fn [grp] (reduce + 0 grp)) groups)]
      (println (reduce max sums))
      (println (reduce + 0 (take 3 (reverse (sort (vec sums)))))))))
