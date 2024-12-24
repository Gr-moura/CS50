from cs50 import get_float

change = None
while change is None or change < 0:
    change = get_float("Change: ")

coin_values: list[int] = [25, 10, 5, 1]

cents: int = round(change * 100)
coins = 0

for value in coin_values:
    coins += cents // value
    cents %= value

print(coins)