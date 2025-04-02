#Practical 1: HashTable with Linear Probings
class HashTableSeparateChaining:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]  # List of lists (chains)
    
    def hash_function(self, key):
        return key % self.size

    def insert(self, key, phone_number):
        index = self.hash_function(key)
        self.table[index].append(phone_number)

    def search(self, key, phone_number):
        index = self.hash_function(key)
        comparisons = 0
        for phone in self.table[index]:
            comparisons += 1
            if phone == phone_number:
                return True, comparisons
        return False, comparisons

    def __str__(self):
        return str(self.table)


class HashTableLinearProbing:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size  # None represents an empty slot

    def hash_function(self, key):
        return key % self.size

    def insert(self, key, phone_number):
        index = self.hash_function(key)
        comparisons = 0
        while self.table[index] is not None:
            comparisons += 1
            index = (index + 1) % self.size  # Linear probing
        self.table[index] = phone_number
        return comparisons

    def search(self, key, phone_number):
        index = self.hash_function(key)
        comparisons = 0
        while self.table[index] is not None:
            comparisons += 1
            if self.table[index] == phone_number:
                return True, comparisons
            index = (index + 1) % self.size
        return False, comparisons

    def __str__(self):
        return str(self.table)


def menu():
    print("\n------------------Telephone Book Database--------------------")
    print("1. Initialize Separate Chaining Table")
    print("2. Initialize Linear Probing Table")
    print("3. Insert Phone Number into Separate Chaining Table")
    print("4. Insert Phone Number into Linear Probing Table")
    print("5. Search Phone Number in Separate Chaining Table")
    print("6. Search Phone Number in Linear Probing Table")
    print("7. Display Separate Chaining Table")
    print("8. Display Linear Probing Table")
    print("9. Exit")


def main():
    separate_chaining_ht = None
    linear_probing_ht = None

    while True:
        menu()
        choice = input("Enter your choice: ").strip()

        if choice == '1':
            size = int(input("Enter table size for Separate Chaining: "))
            separate_chaining_ht = HashTableSeparateChaining(size)
            print("Separate Chaining table initialized.")

        elif choice == '2':
            size = int(input("Enter table size for Linear Probing: "))
            linear_probing_ht = HashTableLinearProbing(size)
            print("Linear Probing table initialized.")

        elif choice == '3':
            if separate_chaining_ht is None:
                print("Separate Chaining table not initialized!")
                continue
            key = int(input("Enter client ID (key): "))
            phone_number = input("Enter phone number: ")
            separate_chaining_ht.insert(key, phone_number)
            print(f"Phone number {phone_number} inserted into Separate Chaining table.")

        elif choice == '4':
            if linear_probing_ht is None:
                print("Linear Probing table not initialized!")
                continue
            key = int(input("Enter client ID (key): "))
            phone_number = input("Enter phone number: ")
            comparisons = linear_probing_ht.insert(key, phone_number)
            print(f"Phone number {phone_number} inserted into Linear Probing table with {comparisons} comparisons.")

        elif choice == '5':
            if separate_chaining_ht is None:
                print("Separate Chaining table not initialized!")
                continue
            key = int(input("Enter client ID (key): "))
            phone_number = input("Enter phone number: ")
            found, comparisons = separate_chaining_ht.search(key, phone_number)
            print(f"Found: {found}, Comparisons: {comparisons}")

        elif choice == '6':
            if linear_probing_ht is None:
                print("Linear Probing table not initialized!")
                continue
            key = int(input("Enter client ID (key): "))
            phone_number = input("Enter phone number: ")
            found, comparisons = linear_probing_ht.search(key, phone_number)
            print(f"Found: {found}, Comparisons: {comparisons}")

        elif choice == '7':
            if separate_chaining_ht is None:
                print("Separate Chaining table not initialized!")
                continue
            print("Separate Chaining Table:", separate_chaining_ht)

        elif choice == '8':
            if linear_probing_ht is None:
                print("Linear Probing table not initialized!")
                continue
            print("Linear Probing Table:", linear_probing_ht)

        elif choice == '9':
            print("Exiting the program.")
            break

        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()

