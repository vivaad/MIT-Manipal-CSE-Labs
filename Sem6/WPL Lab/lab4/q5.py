class PairFinder:
    def __init__(self, numbers):
        self.numbers = numbers

    def find_pair(self, target):
        num_dict = {}
        for index, num in enumerate(self.numbers):
            complement = target - num
            if complement in num_dict:
                return num_dict[complement], index
            num_dict[num] = index
        return None

finder = PairFinder([10, 20, 10, 40, 50, 60, 70])
print(finder.find_pair(50))

