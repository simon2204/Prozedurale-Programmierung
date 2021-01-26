//
//  UnsafeHeap.swift
//  UnsafeHeap
//
//  Created by Simon Schöpke on 24.01.21.
//
import Foundation

struct UnsafeHeap<Element: Comparable> {
    private var elements: UnsafeMutablePointer<UnsafeMutablePointer<Element>>
    private(set) var count = 0
    private(set) var capacity: Int
    
    init(minimumCapacity: Int = 1) {
        self.capacity = minimumCapacity
        elements = UnsafeMutablePointer<UnsafeMutablePointer<Element>>.allocate(capacity: minimumCapacity)
    }

    mutating func insert(_ newElement: UnsafeMutablePointer<Element>) {
        if count == capacity { expand() }
        elements[count] = newElement
        swim(startIndex: count)
        count += 1
    }

    mutating func extractMin() -> UnsafeMutablePointer<Element>? {
        guard count > 0 else { return nil }
        defer {
            if (count == (capacity &>> 2)) { shrink() }
            count -= 1
            elements[0] = elements[count]
            sink(startIndex: 0)
        }
        return elements[0]
    }
    
    mutating func forEach(element: (UnsafeMutablePointer<Element>) -> Void) {
        while let pointer = extractMin() {
            element(pointer)
        }
    }
    
    private mutating func swim(startIndex: Int) {
        if startIndex == 0 { return }
        let parentIdx = (startIndex - 1) / 2
        if elements[startIndex].pointee < elements[parentIdx].pointee {
            swapAt(startIndex, parentIdx)
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
                swapAt(leftChildIdx, startIndex)
                sink(startIndex: leftChildIdx)
            } else if rightChild < elements[startIndex].pointee {
                swapAt(rightChildIdx, startIndex)
                sink(startIndex: rightChildIdx)
            }
        } else if leftChildIdx < count
                    && elements[leftChildIdx].pointee < elements[startIndex].pointee {
            swapAt(leftChildIdx, startIndex)
            sink(startIndex: leftChildIdx)
        }
    }
    
    private mutating func expand() {
        capacity &<<= 1
        let stride = MemoryLayout<UnsafeMutablePointer<UnsafeMutablePointer<Element>>>.stride
        let size = stride * capacity
        elements = unsafeBitCast(realloc(elements, size), to: UnsafeMutablePointer<UnsafeMutablePointer<Element>>.self)
    }
    
    private mutating func shrink() {
        capacity &>>= 1
        let stride = MemoryLayout<UnsafeMutablePointer<UnsafeMutablePointer<Element>>>.stride
        let size = stride * capacity
        elements = unsafeBitCast(realloc(elements, size), to: UnsafeMutablePointer<UnsafeMutablePointer<Element>>.self)
    }
    
    @inline(__always)
    private func swapAt(_ i1: Int, _ i2: Int)
    {
        let temp = elements[i1]
        elements[i1] = elements[i2]
        elements[i2] = temp
    }
    
    func `deinit`() {
        elements.deallocate()
    }
}
