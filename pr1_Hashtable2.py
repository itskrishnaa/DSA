#Pratical 1: Hashtable with Quadratic Probing and Double Hashing
class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size  # Initialize the table with None values

    def hash(self, key):
        """Primary hash function: sum the ASCII values of characters and mod by table size"""
        return sum(ord(char) for char in key) % self.size


class QuadraticProbingHashTable(HashTable):
    def __init__(self, size):
        super().__init__(size)

    def insert(self, key, value):
        index = self.hash(key)
        i = 0
        comparisons = 0
        while self.table[(index + i * i) % self.size] is not None:
            comparisons += 1
            i += 1
            if i == self.size:
                raise Exception("Hash table is full")
        
        self.table[(index + i * i) % self.size] = (key, value)
        return comparisons

    def find(self, key):
        index = self.hash(key)
        i = 0
        comparisons = 0
        while self.table[(index + i * i) % self.size] is not None:
            comparisons += 1
            if self.table[(index + i * i) % self.size][0] == key:
                return self.table[(index + i * i) % self.size][1], comparisons
            i += 1
            if i == self.size:
                break

        return None, comparisons

    def display(self):
        for i in range(self.size):
            if self.table[i] is not None:
                print(f"Index {i}: {self.table[i]}")
            else:
                print(f"Index {i}: Empty")


class DoubleHashingHashTable(HashTable):
    def __init__(self, size):
        super().__init__(size)

    def hash2(self, key):
        """Secondary hash function"""
        return 7 - (sum(ord(char) for char in key) % 7)

    def insert(self, key, value):
        index = self.hash(key)
        step = self.hash2(key)
        comparisons = 0
        while self.table[(index + comparisons * step) % self.size] is not None:
            comparisons += 1
            if comparisons == self.size:
                raise Exception("Hash table is full")

        self.table[(index + comparisons * step) % self.size] = (key, value)
        return comparisons

    def find(self, key):
        index = self.hash(key)
        step = self.hash2(key)
        comparisons = 0
        while self.table[(index + comparisons * step) % self.size] is not None:
            comparisons += 1
            if self.table[(index + comparisons * step) % self.size][0] == key:
                return self.table[(index + comparisons * step) % self.size][1], comparisons
            if comparisons == self.size:
                break
        return None, comparisons

    def display(self):
        for i in range(self.size):
            if self.table[i] is not None:
                print(f"Index {i}: {self.table[i]}")
            else:
                print(f"Index {i}: Empty")


def menu():
    print("\n----------------------Telephone Book Database----------------------------")
    print("1. Initialize Quadratic Probing Table")
    print("2. Initialize Double Hashing Table")
    print("3. Insert Phone Number into Quadratic Probing Table")
    print("4. Insert Phone Number into Double Hashing Table")
    print("5. Search Phone Number in Quadratic Probing Table")
    print("6. Search Phone Number in Double Hashing Table")
    print("7. Display Quadratic Probing Table")
    print("8. Display Double Hashing Table")
    print("9. Exit")
    return int(input("Choose an option: "))


def get_client_data():
    clients = []
    n = int(input("Enter number of clients: "))
    for _ in range(n):
        name = input("Enter client's name: ")
        phone = input("Enter client's phone number: ")
        clients.append((name, phone))
    return clients


def main():
    quadratic_table = None
    double_hashing_table = None

    while True:
        choice = menu()
        
        if choice == 1:
            size = int(input("\nEnter size for Quadratic Probing table: "))
            quadratic_table = QuadraticProbingHashTable(size)
            print(f"Quadratic Probing table initialized with size {size}.")
        
        elif choice == 2:
            size = int(input("\nEnter size for Double Hashing table: "))
            double_hashing_table = DoubleHashingHashTable(size)
            print(f"Double Hashing table initialized with size {size}.")
        
        elif choice == 3:
            if quadratic_table is None:
                print("Quadratic Probing table is not initialized!")
                continue
            clients = get_client_data()
            print("\nInserting clients into Quadratic Probing table...")
            for client in clients:
                comparisons = quadratic_table.insert(client[0], client[1])
                print(f"Inserted {client[0]} with {comparisons} comparisons.")
        
        elif choice == 4:
            if double_hashing_table is None:
                print("Double Hashing table is not initialized!")
                continue
            clients = get_client_data()
            print("\nInserting clients into Double Hashing table...")
            for client in clients:
                comparisons = double_hashing_table.insert(client[0], client[1])
                print(f"Inserted {client[0]} with {comparisons} comparisons.")
        
        elif choice == 5:
            if quadratic_table is None:
                print("Quadratic Probing table is not initialized!")
                continue
            name = input("Enter the client's name to search: ")
            phone, comparisons = quadratic_table.find(name)
            if phone:
                print(f"Found {name}: {phone} with {comparisons} comparisons.")
            else:
                print(f"{name} not found with {comparisons} comparisons.")
        
        elif choice == 6:
            if double_hashing_table is None:
                print("Double Hashing table is not initialized!")
                continue
            name = input("Enter the client's name to search: ")
            phone, comparisons = double_hashing_table.find(name)
            if phone:
                print(f"Found {name}: {phone} with {comparisons} comparisons.")
            else:
                print(f"{name} not found with {comparisons} comparisons.")
        
        elif choice == 7:
            if quadratic_table is None:
                print("Quadratic Probing table is not initialized!")
                continue
            print("\nDisplaying Quadratic Probing Table:")
            quadratic_table.display()
        
        elif choice == 8:
            if double_hashing_table is None:
                print("Double Hashing table is not initialized!")
                continue
            print("\nDisplaying Double Hashing Table:")
            double_hashing_table.display()
        
        elif choice == 9:
            print("Exiting program.")
            break
        
        else:
            print("Invalid option. Please try again.")

if __name__ == "__main__":
    main()

