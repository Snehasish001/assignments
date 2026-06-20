class PriorityQueue:
    def __init__(self):
        self.queue = []

    def push(self, item, priority):
        self.queue.append((priority, item))
        self.queue.sort(reverse=True)  # Highest priority first

    def pop(self):
        if self.is_empty():
            raise Exception("Priority Queue is empty")

        priority, item = self.queue.pop(0)
        return item

    def peek(self):
        if self.is_empty():
            raise Exception("Priority Queue is empty")

        return self.queue[0][1]

    def is_empty(self):
        return len(self.queue) == 0

    def display(self):
        print(self.queue)


# Driver Code
pq = PriorityQueue()

pq.push("Task A", 2)
pq.push("Task B", 5)
pq.push("Task C", 1)
pq.push("Task D", 4)

print("Queue:")
pq.display()

print("\nPop Operations:")
while not pq.is_empty():
    print(pq.pop())