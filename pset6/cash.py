from cs50 import get_float

change = get_float("Change owed: ")

while change < 0:
    change = get_float("Change owed: ")

coin_values = [25, 10, 5, 1]

cents = round(change * 100)
coins = 0

for value in coin_values:
    coins += cents // value
    cents %= value

print(coins)