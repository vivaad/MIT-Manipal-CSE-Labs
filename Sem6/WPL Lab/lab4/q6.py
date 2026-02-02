class PowerCalculator:
    def pow(self, x, n):
        if n < 0:
            return 1 / self._pow_helper(x, -n)
        return self._pow_helper(x, n)

    def _pow_helper(self, x, n):
        if n == 0:
            return 1
        half = self._pow_helper(x, n // 2)
        if n % 2 == 0:
            return half * half
        return half * half * x

calculator = PowerCalculator()
print(calculator.pow(2, 10))

