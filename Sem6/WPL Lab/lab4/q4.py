class SubsetGenerator:
    def __init__(self, nums):
        self.nums = nums

    def subsets(self):
        result = []
        self._generate_subsets(0, [], result)
        return result

    def _generate_subsets(self, index, current, result):
        result.append(current)
        for i in range(index, len(self.nums)):
            self._generate_subsets(i + 1, current + [self.nums[i]], result)

generator = SubsetGenerator([4, 5, 6])
print(generator.subsets())

