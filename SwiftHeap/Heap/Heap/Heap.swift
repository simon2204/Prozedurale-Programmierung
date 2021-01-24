//
//  Heap.swift
//  Heap
//
//  Created by Simon Schöpke on 24.01.21.
//

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
