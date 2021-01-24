//
//  main.swift
//  Heap
//
//  Created by Simon Schöpke on 24.01.21.
//

import Foundation

struct Heap<Element: Comparable> {
    private var elements = ContiguousArray<Element>()

    mutating func insert(_ newElement: Element) {
        elements.append(newElement)
        swim(startIndex: elements.count - 1)
    }

    mutating func extractMin() -> Element? {
        defer {
            if let last = elements.last {
                elements[0] = last
                elements.removeLast()
                sink(startIndex: 0)
            }
        }

        return elements.first
    }
    
    private mutating func swim(startIndex: Int) {
        if startIndex == 0 { return }
        let parentIdx = parentIndex(forChildIndex: startIndex)
        if elements[startIndex] < elements[parentIdx] {
            elements.swapAt(startIndex, parentIdx)
            swim(startIndex: parentIdx)
        }
    }
    
    private mutating func sink(startIndex: Int) {
        guard !elements.isEmpty else { return }
        let parent = elements[startIndex]
        let leftChildIdx = leftChildIndex(forParentIndex: startIndex)
        let rightChildIdx = rightChildIndex(forParentIndex: startIndex)
        if rightChildIdx < elements.count {
            let leftChild = elements[leftChildIdx]
            let rightChild = elements[rightChildIdx]
            if leftChild < rightChild && leftChild < parent {
                elements.swapAt(leftChildIdx, startIndex)
                sink(startIndex: leftChildIdx)
            } else if rightChild < parent {
                elements.swapAt(rightChildIdx, startIndex)
                sink(startIndex: rightChildIdx)
            }
        } else if leftChildIdx < elements.count && elements[leftChildIdx] < parent {
            elements.swapAt(leftChildIdx, startIndex)
            sink(startIndex: leftChildIdx)
        }
    }
    
    private func leftChildIndex(forParentIndex parentIndex: Int) -> Int {
        return 2 * parentIndex + 1
    }
    
    private func rightChildIndex(forParentIndex parentIndex: Int) -> Int {
        return 2 * parentIndex + 2
    }
    
    private func parentIndex(forChildIndex childIndex: Int) -> Int {
        return (childIndex - 1) / 2
    }
}


let unsorted = Array("phnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdi")

var sorted = [Character]()
sorted.reserveCapacity(1000)

let begin = clock()
var heap = Heap<Character>()

unsorted.forEach { item in
    heap.insert(item)
}

while let element = heap.extractMin() {
    sorted.append(element)
}

let end = clock()

let timeSpent = end - begin

print(timeSpent)

//let compareCallback: HEAP_ELEM_COMP = {
//    let i1 = $0!.load(as: Character.self)
//      let i2 = $1!.load(as: Character.self)
//      if i1 < i2 {
//        return -1
//      }
//      if i1 > i2 {
//        return 1
//      }
//      return 0
//}
//
//let printCallback: HEAP_ELEM_PRINT = {
//    let i1 = $0!.load(as: Character.self)
//    print(i1)
//}
//
//var elements = Array("phnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdiphnjabcgdi")

//var result = Array<Character>()
//result.reserveCapacity(1000)
//
//let begin = clock()
//
//heap_init(compareCallback, printCallback)
//
//for i in 0..<elements.count {
//    heap_insert(&elements[i])
//}
//
//var min = UnsafeMutablePointer<UnsafeMutableRawPointer?>.allocate(capacity: 1)
//
//while (heap_extract_min(min)) {
//    result.append(min.pointee!.load(as: Character.self))
//}
//
//heap_destroy()
//
//let end = clock()
//
//let timeSpent = end - begin

//print(timeSpent)

//print(result)
