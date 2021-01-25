//
//  Heap.swift
//  Heap
//
//  Created by Simon Schöpke on 24.01.21.
//
import Foundation

struct Heap<Element: Comparable> {
    private var elements: UnsafeMutableBufferPointer<UnsafeMutablePointer<Element>>
    private(set) var count = 0
    private(set) var capacity: Int
    
    init(capacity: Int = 10000) {
        self.capacity = capacity
        elements = UnsafeMutableBufferPointer<UnsafeMutablePointer<Element>>.allocate(capacity: capacity)
    }

    mutating func insert(_ newElement: UnsafeMutablePointer<Element>) {
        elements[count] = newElement
        swim(startIndex: count)
        count += 1
    }

    private mutating func extractMin() -> UnsafeMutablePointer<Element>? {
        guard count > 0 else { return nil }
        defer {
            count -= 1
            elements[0] = elements[count]
            sink(startIndex: 0)
        }
        return elements[0]
    }
    
    private mutating func swim(startIndex: Int) {
        if startIndex == 0 { return }
        let parentIdx = (startIndex - 1) / 2
        if elements[startIndex].pointee < elements[parentIdx].pointee {
            elements.swapAt(startIndex, parentIdx)
            swim(startIndex: parentIdx)
        }
    }
    
    private mutating func sink(startIndex: Int) {
        let leftChildIdx = 2 * startIndex + 1
        let rightChildIdx = leftChildIdx + 1
        if rightChildIdx < count {
            let leftChild = elements[leftChildIdx].pointee
            let rightChild = elements[rightChildIdx].pointee
            if leftChild < rightChild && leftChild < elements[startIndex].pointee {
                elements.swapAt(leftChildIdx, startIndex)
                sink(startIndex: leftChildIdx)
            } else if rightChild < elements[startIndex].pointee {
                elements.swapAt(rightChildIdx, startIndex)
                sink(startIndex: rightChildIdx)
            }
        } else if leftChildIdx < count
                    && elements[leftChildIdx].pointee < elements[startIndex].pointee {
            elements.swapAt(leftChildIdx, startIndex)
            sink(startIndex: leftChildIdx)
        }
    }
    
    func `deinit`() {
        elements.deallocate()
    }
}


extension Heap: Sequence {
    func makeIterator() -> HeapIterator {
        return HeapIterator(self)
    }
}


extension Heap {
    struct HeapIterator: IteratorProtocol {
        private var heap: Heap
        
        init(_ heap: Heap) {
            self.heap = heap
        }
        
        mutating func next() -> UnsafeMutablePointer<Element>? {
            return heap.extractMin()
        }
    }
}