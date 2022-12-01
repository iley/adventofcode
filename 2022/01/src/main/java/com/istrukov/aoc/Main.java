package com.istrukov.aoc;

import com.google.common.collect.ImmutableList;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Optional;
import java.util.Scanner;

public class Main {
    private static ImmutableList<String> getInputLines() {
        var listBuilder = ImmutableList.<String>builder();
        try {
            var scanner = new Scanner(new File("input.txt"), StandardCharsets.UTF_8);
            while (scanner.hasNextLine()) {
                listBuilder.add(scanner.nextLine());
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return listBuilder.build();
    }

    private static Optional<Integer> parseInt(String s) {
        try {
            var n = Integer.parseInt(s);
            return Optional.of(n);
        } catch (NumberFormatException e) {
            return Optional.empty();
        }
    }

    private static int part1(ImmutableList<String> lines) {
        int max = 0;
        int sum = 0;
        for (var line : lines) {
            var maybeN = parseInt(line);
            if (maybeN.isPresent()) {
                sum += maybeN.get();
            } else {
                if (sum > max) {
                    max = sum;
                }
                sum = 0;
            }
        }
        return max;
    }

    private static int part2(ImmutableList<String> lines) {
        int sum = 0;
        var sums = new ArrayList<Integer>();
        for (var line : lines) {
            var maybeN = parseInt(line);
            if (maybeN.isPresent()) {
                sum += maybeN.get();
            } else {
                if (sum > 0) {
                    sums.add(sum);
                }
                sum = 0;
            }
        }
        Collections.sort(sums);
        Collections.reverse(sums);
        return sums.get(0) + sums.get(1) + sums.get(2);
    }

    public static void main(String[] args) throws FileNotFoundException {
        var lines = getInputLines();
        System.out.println(part1(lines));
        System.out.println(part2(lines));
    }
}
