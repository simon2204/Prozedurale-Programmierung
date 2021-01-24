//
//  Heap2.swift
//  Heap
//
//  Created by Simon Schöpke on 24.01.21.
//
import Foundation

struct Heap2<Element: Comparable> {
    private var elements: UnsafeMutableBufferPointer<UnsafeMutablePointer<Element>>
    private var count = 0
    private var capacity: Int
    
    init(capacity: Int = 2048) {
        self.capacity = capacity
        elements = UnsafeMutableBufferPointer<UnsafeMutablePointer<Element>>.allocate(capacity: capacity)
    }

    mutating func insert(_ newElement: UnsafeMutablePointer<Element>) {
        elements[count] = newElement
        swim(startIndex: count)
        count += 1
    }

    mutating func extractMin(_ minElement: inout UnsafeMutablePointer<Element>) -> Bool {
        let canExtractMin = count > 0
        
        if canExtractMin {
            minElement = elements[0]
            count -= 1
            elements[0] = elements[count]
            sink(startIndex: 0)
        }

        return canExtractMin
    }
    
    private mutating func swim(startIndex: Int) {
        if startIndex == 0 { return }
        let parentIdx = parentIndex(forChildIndex: startIndex)
        if elements[startIndex].pointee < elements[parentIdx].pointee {
            elements.swapAt(startIndex, parentIdx)
            swim(startIndex: parentIdx)
        }
    }
    
    private mutating func sink(startIndex: Int) {
        let parent = elements[startIndex].pointee
        let leftChildIdx = leftChildIndex(forParentIndex: startIndex)
        let rightChildIdx = rightChildIndex(forParentIndex: startIndex)
        if rightChildIdx < count {
            let leftChild = elements[leftChildIdx].pointee
            let rightChild = elements[rightChildIdx].pointee
            if leftChild < rightChild && leftChild < parent {
                elements.swapAt(leftChildIdx, startIndex)
                sink(startIndex: leftChildIdx)
            } else if rightChild < parent {
                elements.swapAt(rightChildIdx, startIndex)
                sink(startIndex: rightChildIdx)
            }
        } else if leftChildIdx < count && elements[leftChildIdx].pointee < parent {
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
    
    func dealloc() {
        elements.deallocate()
    }
}
