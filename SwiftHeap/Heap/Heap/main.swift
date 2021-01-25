//
//  main.swift
//  Heap
//
//  Created by Simon Schöpke on 24.01.21.
//

import Foundation

var unsorted = "phnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdi".cString(using: .utf8)!

var sorted = [CChar]()
sorted.reserveCapacity(10000)

let begin = clock()

var heap = Heap<CChar>(minimumCapacity: 10000)

for i in 0..<unsorted.count {
    heap.insert(&unsorted[i])
}

heap.forEach { (pointer) in
    sorted.append(pointer.pointee)
}

let end = clock()

let timeSpent = end - begin

print("Swift: \(timeSpent)")

//print(sorted)


// MARK:- C code

let compareCallback: HEAP_ELEM_COMP = {
    let i1 = $0!.load(as: CChar.self)
    let i2 = $1!.load(as: CChar.self)
    return i1 == i2 ? 0 : i1 < i2 ? -1 : 1
}

let printCallback: HEAP_ELEM_PRINT = {
    let i1 = $0!.load(as: CChar.self)
    print(i1)
}

var result = Array<CChar>()
result.reserveCapacity(10000)

let begin2 = clock()

heap_init(compareCallback, printCallback)

for i in 0..<unsorted.count {
    heap_insert(&unsorted[i])
}

let min = UnsafeMutablePointer<UnsafeMutableRawPointer?>.allocate(capacity: 1)

while (heap_extract_min(min)) {
    result.append(min.pointee!.load(as: CChar.self))
}

heap_destroy()

let end2 = clock()

let timeSpent2 = end2 - begin2

print("C: \(timeSpent2)")

print(result == sorted)
print(result.count == sorted.count)
