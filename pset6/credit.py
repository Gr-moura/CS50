import re

def main():
    # Get user input
    credit_card = input("Number: ")

    # Check if the credit card number is valid
    if not check_credit_card(credit_card):
        print("INVALID")
        return
    
    # Check the credit card type
    # AMEX uses 15-digit numbers starting with 34 or 37
    if re.match(r"^3[47]", credit_card) and len(credit_card) == 15:
        print("AMEX")

    # MASTERCARD uses 16-digit numbers starting with 51, 52, 53, 54, or 55
    elif re.match(r"^5[1-5]", credit_card) and len(credit_card) == 16:
        print("MASTERCARD")

    # VISA uses 13- and 16-digit numbers starting with 4
    elif re.match(r"^4", credit_card) and len(credit_card) in [13, 16]:
        print("VISA")

    else:
        print("INVALID")


def check_credit_card(credit_card):
    # Check if the length of the credit card number is valid
    if len(credit_card) not in [13, 15, 16]:
        return False

    # Check if the credit card number is valid using Luhn's algorithm
    total = 0

    for i in range(len(credit_card) - 1, -1, -1):
        digit = int(credit_card[i])
        
        if (len(credit_card) - i) % 2 == 0:
            digit *= 2
            digit = digit - 9 if digit > 9 else digit
            
        total += digit

    return total % 10 == 0


if __name__ == "__main__":
    main()