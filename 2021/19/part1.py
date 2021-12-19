#!/usr/bin/env python3
from collections import namedtuple
from itertools import product
import sys

Vector = namedtuple("Vector", ["x", "y", "z"])
Scanner = namedtuple("Scanner", ["id", "scans"])

MIN_MATCHES = 12

TRANSFORMATIONS = [
    lambda v: Vector(v.x, v.y, v.z),
    lambda v: Vector(v.x, -v.z, v.y),
    lambda v: Vector(v.x, -v.y, -v.z),
    lambda v: Vector(v.x, v.z, -v.y),

    lambda v: Vector(v.y, v.z, v.x),
    lambda v: Vector(v.z, -v.y, v.x),
    lambda v: Vector(-v.y, -v.z, v.x),
    lambda v: Vector(-v.z, v.y, v.x),

    lambda v: Vector(v.z, v.x, v.y),
    lambda v: Vector(v.y, v.x, -v.z),
    lambda v: Vector(-v.z, v.x, -v.y),
    lambda v: Vector(-v.y, v.x, v.z),

    lambda v: Vector(v.y, -v.x, v.z),
    lambda v: Vector(v.z, -v.x, -v.y),
    lambda v: Vector(-v.y, -v.x, -v.z),
    lambda v: Vector(-v.z, -v.x, v.y),

    lambda v: Vector(-v.x, -v.y, v.z),
    lambda v: Vector(-v.x, -v.z, -v.y),
    lambda v: Vector(-v.x, v.y, -v.z),
    lambda v: Vector(-v.x, v.z, v.y),

    lambda v: Vector(v.z, v.y, -v.x),
    lambda v: Vector(-v.y, v.z, -v.x),
    lambda v: Vector(-v.z, -v.y, -v.x),
    lambda v: Vector(v.y, -v.z, -v.x),
]

def read_input(filename):
    with open(filename) as inp:
        scanners = []
        scanner = None
        scanner_id = 0
        for line in inp:
            if line.startswith("---"):
                if scanner is not None:
                    scanners.append(scanner)
                scanner = Scanner(id=scanner_id, scans=[])
                scanner_id += 1
                continue
            coords = line.split(",")
            if len(coords) < 3:
                continue
            scanner.scans.append(Vector(int(coords[0]), int(coords[1]), int(coords[2])))
        if scanner is not None:
            scanners.append(scanner)
        return scanners


def vector_add(vec1, vec2):
    return Vector(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z)


def vector_sub(vec1, vec2):
    return Vector(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z)


def find_match(reference, target):
    print("matching %d against %d" % (reference.id, target.id))
    for transform in TRANSFORMATIONS:
        sample_size = len(target.scans) - MIN_MATCHES + 1
        for s1, s2 in product(reference.scans[:sample_size], target.scans[:sample_size]):
            shift = vector_sub(s1, transform(s2))
            matching_scans = set(reference.scans) & set(vector_add(transform(s), shift) for s in target.scans)
            if len(matching_scans) >= MIN_MATCHES:
                print("found match between scanners %d and %d" % (reference.id, target.id))
                return transform, shift
    return None


def locate_beacons(scanners):
    processed_scanners = [scanners[0]]
    remaining_scanners = scanners[1:]

    while len(remaining_scanners) > 0:
        for next_scanner in remaining_scanners:
            for reference in processed_scanners:
                match = find_match(reference, next_scanner)
                if match is None:
                    continue
                transform, shift = match
                remaining_scanners = [s for s in remaining_scanners if s.id != next_scanner.id]
                processed_scanners.append(Scanner(
                    id=next_scanner.id,
                    scans=[ vector_add(transform(s), shift) for s in next_scanner.scans ]))
                break
            else:
                continue
            break
        else:
            raise RuntimeError("NO MATCHES FOUND!!!")

    beacons = set()
    for scanner in processed_scanners:
        beacons |= set(scanner.scans)
    return beacons


def main():
    if len(sys.argv) < 2:
        print("usage: solve.py file.txt", file=sys.stderr)
        sys.exit(1)
    scanners = read_input(sys.argv[1])
    beacons = locate_beacons(scanners)
    print(len(beacons))


if __name__ == "__main__":
    main()
