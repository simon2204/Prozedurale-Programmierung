//
//  main.swift
//  Heap
//
//  Created by Simon Schöpke on 24.01.21.
//

import Foundation

final class Heap<Element: Comparable> {
    var elements = ContiguousArray<Element>()
    
    func insert(_ newElement: Element) {
        elements.append(newElement)
        swim(startIndex: elements.count - 1)
    }
    
    func extractMin() -> Element? {
        defer {
            if let last = elements.last {
                elements[0] = last
                elements.removeLast()
                sink(startIndex: 0)
            }
        }
        
        return elements.first
    }
    
    private func swim(startIndex: Int) {
        if startIndex == 0 { return }
        let parentIdx = parentIndex(forChildIndex: startIndex)
        if elements[startIndex] < elements[parentIdx] {
            elements.swapAt(startIndex, parentIdx)
            swim(startIndex: parentIdx)
        }
    }
    
    private func sink(startIndex: Int) {
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


let unsorted = ["l", "f", "d", "a", "c", "z", "s", "r"]

let heap = Heap<String>()

unsorted.forEach(heap.insert)

while let element = heap.extractMin() {
    print(element)
}


