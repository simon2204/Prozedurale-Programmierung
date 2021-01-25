//
//  main.swift
//  Heap
//
//  Created by Simon Schöpke on 24.01.21.
//

import Foundation

var unsorted = [9, 8, 7, 6, 5, 4, 3, 2, 1]

var sorted = [Int]()
sorted.reserveCapacity(10000)

let begin = clock()

var heap = Heap<Int>(capacity: unsorted.count)

for i in 0..<unsorted.count {
    heap.insert(&unsorted[i])
}

for charPointer in heap {
    sorted.append(charPointer.pointee)
}

let end = clock()

let timeSpent = end - begin

print("Swift: \(timeSpent)")

print(sorted)

heap.deinit()

// MARK:- C code

let compareCallback: HEAP_ELEM_COMP = {
    let i1 = $0!.load(as: Int.self)
    let i2 = $1!.load(as: Int.self)
    return i1 == i2 ? 0 : i1 < i2 ? -1 : 1
}

let printCallback: HEAP_ELEM_PRINT = {
    let i1 = $0!.load(as: Int.self)
    print(i1)
}

var result = Array<Int>()
result.reserveCapacity(10000)

let begin2 = clock()

heap_init(compareCallback, printCallback)

for i in 0..<unsorted.count {
    heap_insert(&unsorted[i])
}

let min = UnsafeMutablePointer<UnsafeMutableRawPointer?>.allocate(capacity: 1)

while (heap_extract_min(min)) {
    result.append(min.pointee!.load(as: Int.self))
}

heap_destroy()

let end2 = clock()

let timeSpent2 = end2 - begin2

print("C: \(timeSpent2)")

print(result)
